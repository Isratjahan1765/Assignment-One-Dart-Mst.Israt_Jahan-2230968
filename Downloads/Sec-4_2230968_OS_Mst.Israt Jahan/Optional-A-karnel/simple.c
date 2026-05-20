#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mst. Israt Jahan");
MODULE_DESCRIPTION("A simple Linux kernel module with GOLDEN_RATIO_PRIME and GCD");
MODULE_VERSION("1.0");

static int __init simple_init(void) {
    printk(KERN_INFO "Simple Module: Hello, Kernel!\n");
    printk(KERN_INFO "GOLDEN_RATIO_PRIME = %lu\n", (unsigned long)GOLDEN_RATIO_PRIME);
    return 0;
}

static void __exit simple_exit(void) {
    unsigned long result = gcd(3700, 24);
    printk(KERN_INFO "GCD of 3700 and 24 is: %lu\n", result);
    printk(KERN_INFO "SIMPLE MODULE: GOODBYE, KERNEL!\n");
}

module_init(simple_init);
module_exit(simple_exit);