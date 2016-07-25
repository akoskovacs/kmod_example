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

# Usage
### Reading `hello` sysfs attribute
`cat /sys/kernel/hello/hello`

Will give the string _Hello, world!_, proving that the module does work.

### Reading `hello_num`
`cat /sys/kernel/hello/hello_num`

Reads _500_ initially when the module's internal variable is going live, but it can be modified later to any integer number.

### Writing to `hello`
`sudo sh -c "echo -n 'this is a test' > /sys/kernel/hello/hello"`
The `sh -c` is needed for `sudo` to work properly. If you are root, the `echo -n 'this is a test' > /sys/kernel/hello/hello` should also work.

The result could be seen in the kernel logs, by issuing:
`dmesg | tail`, you would get:
```
[12449.884238] hello: Hello, I am a cool small module!
[12712.550500] hello: I got 'this is a test' :D
```
If the `-n` is not used the end quote mark will start in the next line due to the end line mark also written to the file.

### Writing to `hello_num`
The line: `sudo sh -c "echo -n '900' > /sys/kernel/hello/hello_num"`, will change the internal integer
variable to _900_ instead of the initial _500_. This can be tested, by reading the _sysfs attribute_ again:
`cat /sys/kernel/hello/hello_num`

