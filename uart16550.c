// SPDX-License-Identifier: GPL-2.0
/*
 * uart16550.c - UART16550 driver
 *
 * Author: Horia Nedelcu <nedelcu.horia.alexandru@gmail.com>
 * Author: Robert Lica   <robertlica21@gmail.com>
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include "./uart16550.h"


int major = 42, option = OPTION_BOTH, first_minor, num_minors;
module_param(major,  int, 0000);
module_param(option, int, 0000);


struct uart16550_dev {
   struct cdev cdev;
   /*TODO */
};

static struct uart16550_dev devs[MAX_NUMBER_DEVICES];

static int uart16550_open(struct inode *inode, struct file *file)
{
	/*TODO */
	pr_info("my dick is huge\n");
	return 0;
}

static int uart16550_release(struct inode *inode, struct file *file)
{
	/*TODO */
	return 0;
}

static ssize_t uart16550_read(struct file *file,  char __user *user_buffer,
								size_t size, loff_t *offset)
{
	/*TODO */
	return 0;
}

static ssize_t uart16550_write(struct file *file,
								const char __user *user_buffer,
								size_t size, loff_t *offset)
{
	/*TODO */
	return 0;
}

static long
uart16550_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	/*TODO */
	return 0;
}

static const struct file_operations uart16550_fops = {
	.owner          = THIS_MODULE,
	.open           = uart16550_open,
	.release        = uart16550_release,
	.read           = uart16550_read,
	.write          = uart16550_write,
	.unlocked_ioctl = uart16550_ioctl
};

static int __init uart16550_init(void)
{
	int i, err;

	switch (option)
	{
	case OPTION_COM1:
		first_minor = 0;
		num_minors  = 1;
		
		break;
	case OPTION_COM2:
		first_minor = 1;
		num_minors  = 1;

		break;
	case OPTION_BOTH:
		first_minor = 0;
		num_minors  = MAX_NUMBER_DEVICES;

		break;
	default:
		return -EINVAL;
	}

	err = register_chrdev_region(MKDEV(major, first_minor), num_minors, MODULE_NAME);
	if (err != 0) {
		pr_err("register_chrdev_region failed");
		return err;
	}

	for (i = 0; i < num_minors; i++) {
		/* init and add cdev to kernel core */
		// TODO: handle errors
		cdev_init(&devs[i].cdev, &uart16550_fops);
		cdev_add( &devs[i].cdev, MKDEV(major, i + first_minor), 1);
	}

	return 0;
}

static void __exit uart16550_exit(void)
{
	int i;

	for (i = 0; i < num_minors; i++) {
		/* delete cdev from kernel core */
		cdev_del(&devs[i].cdev);
	}

	/* unregister char device region */
	unregister_chrdev_region(MKDEV(major, first_minor), num_minors);
}

module_init(uart16550_init);
module_exit(uart16550_exit);

MODULE_DESCRIPTION("UART16550 Driver");
MODULE_AUTHOR("Horia Nedelcu <nedelcu.horia.alexandru@gmail.com>");
MODULE_AUTHOR("Robert Lica <robertlica21@gmail.com>");
MODULE_LICENSE("GPL v2");