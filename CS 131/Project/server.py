import asyncio
import aiohttp
import argparse
import json
import re
import sys
import time

API_KEY = ''
REQUEST_URL = 'https://places.googleapis.com/v1/places:searchNearby?key=' + API_KEY
HOP_COUNT = 2

# servers = {'Bailey': 12618, 'Bona': 12649, 'Campbell': 12680, 'Clark': 12711, 'Jaquez': 12742}
servers = {'Bailey': 10000, 'Bona': 10001, 'Campbell': 10002, 'Clark': 10003, 'Jaquez': 10004}

server_connections = {
    'Bailey':['Bona', 'Campbell'], 
    'Bona':['Bailey', 'Campbell', 'Clark'], 
    'Campbell':['Bailey', 'Bona', 'Jaquez'], 
    'Clark':['Bona', 'Jaquez'], 
    'Jaquez':['Campbell', 'Clark']
}

id_list = dict()
# time_diff, client id, location time

active_servers = set()

def parse_args():
    parser = argparse.ArgumentParser(description='Start the server with a given name')
    parser.add_argument('server_name', type=str, help='The name of the server')
    args = parser.parse_args()

    if args.server_name not in servers:
        print(f'Error: \'{args.server_name}\' is not a valid server name.')
        print(f'Valid server names are: {", ".join(servers.keys())}')
        sys.exit(1)
    
    return args

def split_lat_long(coord):
    if coord[0] in "+-":
        second_sign_index = coord[1:].find('+') + 1 or coord[1:].find('-') + 1

    lat = coord[:second_sign_index]
    long = coord[second_sign_index:]
    return lat, long


def write_to_logs(msg):
    with open(log_name, 'a', encoding='utf-8') as file:
        file.write(msg)
        file.write('\n')


async def tell_server(data, port, host='127.0.0.1'):
    try:
        reader, writer = await asyncio.open_connection(host, port)
        writer.write(data.encode())
        await writer.drain()
        writer.close()
        await writer.wait_closed()

    except Exception as e:
        pass


async def tell_neighbors(data, excluded=set()):
    tasks = []
    others = server_connections[SERVER_NAME]

    for s in [x for x in others if x not in excluded]:
        tasks.append(asyncio.create_task(tell_server(data, servers[s])))

    await asyncio.gather(*tasks)


async def send_response(writer, response):
    writer.write(response.encode())
    await writer.drain()
    writer.close()
    await writer.wait_closed()


async def handler(reader, writer):
    data = await reader.read(1024)

    server_time = time.time()

    message = data.decode()
    msg_parts = message.split(' ')
    n = len(msg_parts)
    msg_type = msg_parts[0]

    if n == 4:
        try:
            if msg_type == 'IAMAT':
                # IAMAT ID Location Time
                client_time = float(msg_parts[3])
                time_diff = server_time - client_time
                info = msg_parts[1:]

                # respond to sender
                response = f'AT {SERVER_NAME} {time_diff:+.9f} {" ".join(msg_parts[1:])}\n'
                await send_response(writer, response)

                # log event
                log_msg = f'{SERVER_NAME} received {msg_type} from {msg_parts[1]}'
                write_to_logs(log_msg)

                # update user location
                id_list[msg_parts[1]] = [f'{time_diff:+.9f}'] + info

                # tell other servers
                server_msg = f'AT {SERVER_NAME} {time_diff:+.9f} {" ".join(info)} {SERVER_NAME} {HOP_COUNT}\n'
                await tell_neighbors(server_msg)

            elif msg_type == 'WHATSAT' and msg_parts[1] in id_list:
                    radius = float(msg_parts[2])
                    max_info = int(msg_parts[3])

                    # bound parameters
                    radius = min(radius, 50)
                    max_info = min(max_info, 20)

                    id = msg_parts[1]
                    lat, long = split_lat_long(id_list[id][2])

                    headers = {
                        'Content-Type': 'application/json',
                        'X-Goog-Api-Key': API_KEY,
                        'X-Goog-FieldMask': '*'
                    }

                    request_body = {
                        'maxResultCount': max_info,
                        'locationRestriction': {
                            'circle': {
                                'center': {
                                    'latitude': lat,
                                    'longitude': long
                                },
                                'radius': (radius * 1000)
                            }
                        }
                    }

                    async with aiohttp.ClientSession() as session:
                        async with session.post(REQUEST_URL, json=request_body, headers=headers) as res:  
                            place_data = await res.json()

                    place_data = json.dumps(place_data, indent=2)
                    place_data = re.sub(r'\n+', '\n', place_data)

                    # respond to sender
                    response = f'AT {SERVER_NAME} {" ".join(id_list[id])}\n{place_data}\n\n'
                    await send_response(writer, response)

                    # log event
                    log_msg = f'{SERVER_NAME} received {msg_type} from {id}'
                    write_to_logs(log_msg)

            else:
                # respond to sender
                response = f'? {message}\n'
                await send_response(writer, response)

                # log event
                log_msg = f'{SERVER_NAME} received ? from CLIENT'
                write_to_logs(log_msg)

        except Exception as e:
                # respond to sender
                response = f'? {message}\n'
                await send_response(writer, response)

                # log event
                log_msg = f'{SERVER_NAME} received ? from CLIENT'
                write_to_logs(log_msg)

    elif msg_type == 'AT':
        # AT SERVER_NAME time_diff ID Location Time SENDER HOP_COUNT

        # respond to sender
        response = 'AT received'
        await send_response(writer, response)

        progenitor = msg_parts[1]
        id = msg_parts[3]
        msg_contents = msg_parts[2:6]
        log_msg = f'{SERVER_NAME} received {msg_type} from {progenitor}'

        if id not in id_list:
            id_list[id] = msg_contents

            # log event
            write_to_logs(log_msg)

        else:
            if float(msg_contents[-1]) > float(id_list[id][-1]):
                id_list[id] = msg_contents
                
                # log event
                write_to_logs(log_msg)

        sender = msg_parts[6]
        hops_left = int(msg_parts[7])

        if hops_left > 0:
            server_msg = f'AT {" ".join(msg_parts[1:6])} {id} {hops_left - 1}'
            await tell_neighbors(server_msg, excluded=set([progenitor, SERVER_NAME, sender]))

    elif msg_type == 'OPEN':
        # OPEN SERVER_NAME SENDER HOP_COUNT *

        # respond to sender
        response = f'OPEN received'
        await send_response(writer, response)

        progenitor = msg_parts[1]
        sender = msg_parts[2]

        if progenitor in server_connections[SERVER_NAME]:
            log_msg = f'{progenitor} has opened a connection. Hello {progenitor}.'
        else:
            log_msg = f'{progenitor} has opened a connection. Who asked?.'

        if progenitor not in active_servers:
            active_servers.add(progenitor)

            # log event
            write_to_logs(log_msg)

        hops_left = int(msg_parts[3])

        if hops_left > 0:
            server_msg = f'{" ".join(msg_parts[0:2])} {SERVER_NAME} {hops_left - 1} *'
            await tell_neighbors(server_msg, excluded=set([progenitor, SERVER_NAME, sender]))

    elif msg_type == 'DROP':
        # DROP SERVER_NAME SENDER HOP_COUNT *

        # respond to sender
        response = f'DROP received'
        await send_response(writer, response)

        progenitor = msg_parts[1]
        sender = msg_parts[2]

        if progenitor in server_connections[SERVER_NAME]:
            log_msg = f'{progenitor} has dropped their connection. Bye {progenitor}.'
        else:
            log_msg = f'{progenitor} has dropped their connection. GET OU-'

        if progenitor not in active_servers:
            active_servers.add(progenitor)

            # log event
            write_to_logs(log_msg)

        hops_left = int(msg_parts[3])

        if hops_left > 0:
            server_msg = f'{" ".join(msg_parts[0:2])} {SERVER_NAME} {hops_left - 1} *'
            await tell_neighbors(server_msg, excluded=set([progenitor, SERVER_NAME, sender]))

    else:
        # respond to sender
        response = f'? {message}\n'
        await send_response(writer, response)

        # log event
        log_msg = f'{SERVER_NAME} received ? from CLIENT'
        write_to_logs(log_msg)
        


async def main():
    args = parse_args()

    global SERVER_NAME
    SERVER_NAME = args.server_name
    
    start_msg = f'Starting server: {SERVER_NAME}...'
    server = await asyncio.start_server(handler, host='0.0.0.0', port=servers[SERVER_NAME])
    start_time = time.time()

    print(start_msg)
    print(f'Server listening on {servers[SERVER_NAME]}.')

    m_d_y = time.strftime('%m_%d_%Y', time.localtime(start_time))

    global log_name
    log_name = f'log_{SERVER_NAME}_{m_d_y}'

    # log event
    write_to_logs(start_msg[0:-3])

    server_msg = f'OPEN {SERVER_NAME} {SERVER_NAME} {HOP_COUNT} *'
    await tell_neighbors(server_msg)

    try:
        await server.serve_forever()
    except (asyncio.CancelledError, KeyboardInterrupt) as e:
        pass
    finally:
        print('Closing server...')

        server_msg = f'DROP {SERVER_NAME} {SERVER_NAME} {HOP_COUNT} *'
        await tell_neighbors(server_msg)

        server.close()
        await server.wait_closed()

        # log event
        close_msg = 'Server closed'
        write_to_logs(close_msg)

        print(close_msg)
        # print(id_list)
    

if __name__ == '__main__':
    asyncio.run(main())
