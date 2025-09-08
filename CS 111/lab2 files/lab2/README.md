# You Spin Me Round Robin

Simulation for the implementation of round robin scheduling

## Building

```shell
make
```

## Running

cmd for running
```shell
./rr <input file> <quantum length>
```

quantum length - a non-negative and non-zero integer

input file format
```shell
(number_of_processes)
(process_id), (arrival_time), (burst_time)
```

example
```shell
4
1, 0, 7
2, 2, 4
3, 4, 1
4, 5, 4
```

results
```shell
Average waiting time: 7.00
Average response time: 2.75
```

## Cleaning up

```shell
make clean
```
