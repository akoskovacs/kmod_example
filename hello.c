#define pr_fmt(fmt) 	KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sysfs.h>

#include <linux/printk.h>

static struct kobject *hello;
static int hello_num = 500;

static ssize_t 
hello_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return scnprintf(buf, PAGE_SIZE, "Hello, world!\n");
}

static ssize_t 
hello_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
//	snprintf(kobj->name, sizeof(kobj->name), "%.*s", );
	if (buf && buf[count-1] == '\n') {
		pr_debug("Got an enter at the end of the line.");
	}	
	pr_info("I got '%s' :D\n", buf);
	return count;
}

static ssize_t 
hello_num_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", hello_num);
}

static ssize_t 
hello_num_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	sscanf(buf, "%du", &hello_num);
	return count;
}


static struct kobj_attribute num = __ATTR_RW(hello_num);
static struct kobj_attribute helloattr = __ATTR_RW(hello);

static __init int hello_init(void)
{
	int error;
	pr_info("Hello, I am a cool small module!\n");
	hello = kobject_create_and_add("hello", kernel_kobj);
	if (!hello) {
		return -ENOMEM;
	}	
	error = sysfs_create_file(hello, &num.attr);
	if (error) {
		pr_debug("Cannot create sysfs file 'num'!\n");
		return error;
	}
	error = sysfs_create_file(hello, &helloattr.attr);
	if (error) {
		pr_debug("Cannot create sysfs file 'hello'!\n");
	}
	return error;
}

static __exit void hello_exit(void)
{
	kobject_put(hello);
	pr_info("I am removed :(\n");
}

//static DEVICE_ATTR(hello, S_IWUSR | S_IRUGO, read_hello_file, write_hello_file);

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("My cool driver");
MODULE_VERSION("0.1.3");
