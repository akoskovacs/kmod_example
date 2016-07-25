# Sysfs kernel module example project
This kernel module will create two files, under `/sys/kernel/hello`:
  * `hello`, which contains the string 'Hello, world!'
  * `hello_num`, which reads 500 by default

Both are writable by root. `hello` will dump it's contents to the kernel log, while `hello_num` will 
save the number given by the users to a variable.

# How to build
```sh
 git clone https://github.com/akoskovacs/kmod_example.git
 cd kmod_example
 ./install-deps.sh
 make insert
```

Currently the `install-deps.sh` script can install all the neccessary dependencies only for the **Raspbian** Linux distribution.

The __insert__ command will build the module using the current kernel's headers, then it will replace the any other module
named `hello` _(if any)_ with the newly built one.

