# Sysfs kernel module example project
This kernel module will create two files, under `/sys/kernel/hello`:
  * `hello`, which contains the string 'Hello, world!'
  * `hello_num`, which reads 500 by default

Both are writable by root. `hello` will dump it's contents to the kernel log, while `hello_num` will save
