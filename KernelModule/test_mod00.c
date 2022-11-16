#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kern_levels.h>

MODULE_LICENSE("GPL");

int ece_init(void)
{
    printk(KERN_INFO " ECE4310: Start here\n "); //print kernel | kern info is an interger. its a flag. defined in kern levels header. between 0-7.  based on that level the system will decide if it wants to keep track of your message or not.
    return 0;
}
void ece_end(void)
{
    printk(KERN_INFO " ECE 4310: End Here\n"); //prints in the log file.
}

module_init(ece_init);
module_exit(ece_end);