import random, sys, argparse, string

class shuf:
    def __init__(self, infile):
        if infile == '-':
            self.lines = sys.stdin.readlines()
            
        else:
            f = open(infile, 'r')
            self.lines = f.readlines()
            f.close()

            
def valid_hcount(hcount, r, parser):
    try: # read in the argument as a string to catch cases like -0
        n = int(hcount)
    except:
        parser.error(f'invalid line count: {hcount}')

    if '-' in hcount: # negative numbers are bad
        parser.error(f'invalid line count: {hcount}')

    if n < len(r): # making sure there is no invalid acces/index errors
        size = n
    else:
        size = len(r)

    return r, size


def arg_repeat(hcount, parser, r): # irange is for -i only, numbers are appended with \n
    try:
        if hcount:
            for i in range(0, int(hcount)):
                a = random.choice(r)
                sys.stdout.write(a + ('' if a[-1:] == '\n' else '\n'))
        else:
            while True:
                a = random.choice(r)
                sys.stdout.write(a + ('' if a[-1:] == '\n' else '\n'))
    except KeyboardInterrupt: # to stop the infinite repeats
        pass
    except IndexError: # for blank files/inputs
        parser.error('no lines to repeat')

def main():
    
    parser = argparse.ArgumentParser(
        prog='shuf',
        description='Write a random permutation of the input lines to standard output.'
        )

    parser.add_argument('FILE', nargs='?') # argument for input file

    group = parser.add_mutually_exclusive_group()
    
    group.add_argument('-e', '--echo', action='store_true', help='treat each ARG as an input line')

    group.add_argument('-i', '--input-range', dest='irange', metavar='LO-HI',\
                       type=str, help='treat each number LO through HI as an input line')

    parser.add_argument('-n', '--head-count', dest='hcount', metavar='COUNT', \
                       help='output at most COUNT lines')

    parser.add_argument('-r', '--repeat', help='output lines can be repeated', action='store_true')

    args, extras = parser.parse_known_args() # extra arguments for -e, -i

    for arg in extras: # checking for false arguments like -1 or -a
        if arg[0] == '-' and len(arg) > 1:
            parser.error(f'invalid option -- {arg[1]}')

    if args.echo: # echo flag indicated
        echo_args = [x for x in sys.argv[1:] if x not in ('-e', '--echo')]
        r = random.sample(echo_args, len(echo_args))

        try: # check for and remove the argument(looking for which name user chose) so it is not output
            r.remove('--head-count')
        except ValueError:
            pass
            
        try: # same as above ^
            r.remove('-n')
        except ValueError:
            pass
        
        if args.hcount: # head count flag indicated
            r.remove(args.hcount) # removing the argument for -n so it is not output
            r, size = valid_hcount(args.hcount, r, parser)
        else:
            size = len(r)

        if args.repeat: # repeat flag indicated
            r.remove('-r')
            arg_repeat(args.hcount, parser, r)
        else:
            for i in range(0, size): # printing out all args(except filename)
                sys.stdout.write(r[i] + '\n')

    elif args.irange: # input-range flag indicated
        irange = args.irange

        for char in irange: # -i arg can only contain digits and 1 -, also that dash can't be at the ends of the string
            if (not char.isdigit() and not '-') or (len(irange) < 3) or (irange.count('-') > 1):
                parser.error(f'invalid input range: {irange}')
            elif irange[0] == '-' or irange[len(irange) - 1] == '-':
                parser.error(f'invalid input range: {irange}')

        ranges = irange.split('-') # put the two values into a list
        ranges[:] = [int(x) for x in ranges] # convert them to ints for comparisons
        
        if ranges[0] > ranges[1]: # the lower bound can't be greater than the upper bound
            parser.error(f'invalid input range: {irange}')

        if args.FILE:
            parser.error(f'extra operand: {args.FILE}')
        elif extras:
            parser.error(f'extra operand: {extras[0]}')
        
        ranges = [str(x) for x in range(ranges[0], ranges[1] + 1)] # convert to str for stdout

        r = random.sample(ranges, len(ranges))

        if args.hcount: # headcount flag indicated
            r, size = valid_hcount(args.hcount, r, parser)
        else:
            size = len(r)

        if args.repeat: # repeat flag indicated
            arg_repeat(args.hcount, parser, r)
        else:
            for i in range(0, size): # print out the values in random order
                sys.stdout.write(r[i] + '\n')

    else: # other combinations of FILE + args
        try:
            shuffler = shuf(args.FILE)
        except FileNotFoundError:
            parser.error('No such file or directory')

        except TypeError: # in case of no file given ex. shuf.py -n 84
            shuffler = shuf('-')
            
        if extras:
            parser.error(f'extra operand: {extras[0]}')

        r = random.sample(shuffler.lines, len(shuffler.lines))
        
        if args.hcount: # headcount flag indicated
            r, size = valid_hcount(args.hcount, r, parser)
        else:
            size = len(r)

        if args.repeat: # repeat flag indicated
            arg_repeat(args.hcount, parser, r)
        else:
            for i in range(0, size):
                sys.stdout.write(r[i])

if __name__ == "__main__":
    main()
