# Hash Hash Hash
TODO introduction

## Building
```shell
make
```

## Running
```shell
./hash-table-tester
optional arguments: -t #threads -s size-per-thread

example: ./hash-table-tester -t 4 -s 200000
```

## First Implementation
In the `hash_table_v1_add_entry` function, I added a mutex from the pthread library to prevent data loss \
caused by sudden context switches.

### Performance
```shell
./hash-table-tester

Generation: 8,680 usec
Hash table base: 25,722 usec
  - 0 missing
Hash table v1: 48,987 usec
  - 0 missing
Hash table v2: 14,028 usec
  - 0 missing
```
Version 1 is slower than the base version. As required in the specifications, the only way to reduce the \
performance of Version 1 was to wrap the entire add_entry function in a mutex. Because so many \
functions are called for variable initializations, memory allocation, etc, it increases the thread overhead \
as there is significantly more code in the critical section, making other threads wait longer.

## Second Implementation
In the `hash_table_v2_add_entry` function, I implemented a type of locking that divided the hash table into multiple segments per lock. \
This reduces lock contention and lessens the cost of memory allocations to the array of locks compared to having one lock per hash table bucket. \
The size of the lock array was decided on based on lots of testing on both the seasnet server and my vm with 4 cores. I chose the number 32 \
to be the size after noticing it did not have inconsistent v2 performances where sometimes v2 would have a larger time than base. This \
should not happen at all at size-per-thread values greater than 10000. Another reason is that is was able to consistently pass v2 test 2 \
and semi-consistently pass v2 test 1 with a high number of elements. I believe that the performance gains of locking should reduce \
as the size-per-thread decreases which can be observed in my implementation.

### Performance
```shell
./hash-table-tester -t 4 -s 100000

Generation: 33,899 usec
Hash table base: 788,765 usec
  - 0 missing
Hash table v1: 1,217,759 usec
  - 0 missing
Hash table v2: 251,630 usec
  - 0 missing
```

### More Results
```shell
./hash-table-tester -t 4 -s 10000

Generation: 3,496 usec
Hash table base: 4,117 usec
  - 0 missing
Hash table v1: 11,452 usec
  - 0 missing
Hash table v2: 3,168 usec
  - 0 missing
```

```shell
./hash-table-tester -t 4 -s 200000

Generation: 66,328 usec
Hash table base: 5,671,232 usec
  - 0 missing
Hash table v1: 7,078,419 usec
  - 0 missing
Hash table v2: 1,841,053 usec
  - 0 missing
```

```shell
./hash-table-tester -t 4 -s 500000

Generation: 166,364 usec
Hash table base: 51,366,463 usec
  - 0 missing
Hash table v1: 57,264,597 usec
  - 0 missing
Hash table v2: 16,339,927 usec
  - 0 missing
```

## Cleaning up
```shell
make clean
```