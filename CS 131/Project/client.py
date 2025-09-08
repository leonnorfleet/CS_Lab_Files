import asyncio
import time
import argparse
import sys

# servers = {'Bailey': 12618, 'Bona': 12649, 'Campbell': 12680, 'Clark': 12711, 'Jaquez': 12742}
servers = {'Bailey': 10000, 'Bona': 10001, 'Campbell': 10002, 'Clark': 10003, 'Jaquez': 10004}
					
def parse_args():
    parser = argparse.ArgumentParser(description='Start the server with a given name')
    parser.add_argument('server_name', type=str, help='The name of the server')
    args = parser.parse_args()

    if args.server_name not in servers:
        print(f"Error: \'{args.server_name}\' is not a valid server name.")
        print(f"Valid server names are: {', '.join(servers.keys())}")
        sys.exit(1)
    
    return args

async def tcp_client(message, host='127.0.0.1', port=12618):
    reader, writer = await asyncio.open_connection(host, port)

    print(f'Sending: {message}')
    writer.write(message.encode())
    await writer.drain()

    data = b''
    
    while True:
        chunk = await reader.read(4096)
        if not chunk:
            break

        data += chunk

    data = data.decode('utf-8')

    print(f'Received: {data}')

    # print('Closing connection')
    writer.close()
    await writer.wait_closed()

if __name__ == '__main__':
    args = parse_args()
    server_name = args.server_name
    port = servers[server_name]
    cmd = 'IAMAT'
    client_ID = 'nahidwin.cs.ucla.edu'
    lat = '+33.812100'
    long = '-117.919000'
    when = time.time()
    radius = 50
    max_info = 20

    asyncio.run(tcp_client(f'ngl ts imo icl', port=port))
    asyncio.run(tcp_client(f'{cmd} {client_ID} {lat}{long} {when}', port=port))
    cmd = 'WHATSAT'
    asyncio.run(tcp_client(f'{cmd} {client_ID} {radius} {max_info}', port=port))
