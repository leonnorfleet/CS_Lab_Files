# A Kernel Seedling
Kernel code for viewing current # of running processes

## Building
```shell
make
sudo insmod proc_count.ko
```

## Running
```shell
cat /proc/count
```
Outputs an integer representing the number of processes \
    running at execution

## Cleaning Up
```shell
make clean
sudo rmmod proc_count
```

## Testing
```python
python -m unittest
```
Clean up before testing

Ran 3 tests in 0.64s, all OK \
Output verified with ps command

```shell
uname -r -s -v
```
kernel release ver. 5.14.8