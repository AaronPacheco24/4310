#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kern_levels.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/random.h>
MODULE_LICENSE("GPL");

#define ECE_BUF_SIZE 4096

static char ece_buffer[ECE_BUF_SIZE];
int isReg;
int major;
int ece_offset_w;
int ece_offset_r;
int ece_size;
int z;
int randomgen;
static ssize_t ece_read(struct file *fp,char *buf,size_t count,loff_t *offset)
{
	int ret;
	char *message;
	int length;
	if (ece_offset_r + count >= ECE_BUF_SIZE)
	{
		printk(KERN_INFO " Read overflow. Abort\n");
		return -1;
	}

	get_random_bytes(&z, sizeof(int));
	randomgen = z %3;
	switch (randomgen)
	{
	case 0: 
		message = "R";
		break;
	case 1:
		message = "P";
		break;
	case 2:
		message = "S";
		break;
	default:
		message = "R";
		break;

	}
	length = strlen(message); 
	
	printk(KERN_INFO "COPY TO USER\n");
	ret = copy_to_user(buf,message, length);
	if (ret!=0)
	{
		printk(KERN_INFO "ERR COPY TO USER\n");
		return -1;
	}

	ece_offset_r = ece_offset_r + count;

	return count;
}




static ssize_t ece_write(struct file* fp, const char* buf, size_t count, loff_t* op)
{
	int ret =0;
	if (ece_offset_w+count>=ECE_BUF_SIZE)
	{
		printk(KERN_INFO "WRITE OVERFLOW. ABORT\n");
		return -1;
	}

	printk(KERN_INFO "COPYING FROM USER\n");
	ret = copy_from_user(&ece_buffer[ece_offset_w], buf, count);
	
	if(ret !=0)
	{
		printk(KERN_INFO "ERR COPY FROM USER. ABORT\n");
		return -1;
	}
	ece_offset_w = ece_offset_w + count;

	return count;
}

static struct file_operations ece_fops =
{
	.read = ece_read,
	.write = ece_write,
};

int ece_init(void)
{
	int ret =0;
	major = register_chrdev(0,"test_module",&ece_fops);
	ece_offset_w = 0;
	ece_offset_r = 0;
	ece_size = 0;
	if (major <0)
	{
		isReg = 0;
		printk(KERN_INFO " ECE 4310. Testmodule failed to deploy\n");
	}
	else
	{
		isReg = 1;
		printk(KERN_INFO " ECE 4310. Testmodule  deployed\n");
	}
	return 0;
}

void ece_end(void)
{
	if (isReg)
	{
		unregister_chrdev(major,"test_module");
	}
	printk(KERN_INFO "Module Removed");
}

module_init(ece_init);
module_exit(ece_end);

