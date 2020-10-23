#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>

#include "consts.h"
#include "device_handlers.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rhydon");

static int dev_major = 0;
static struct cdev cdev;
static struct class* pci_enumerator_class = NULL;

static const struct file_operations fops = {
    .owner      = THIS_MODULE,
    .open       = device_open,
    .release    = device_close,
    .read       = device_read,
};

static int pci_enumerator_init(void)
{   
    int err;
    dev_t dev;
    printk(KERN_INFO "hello...\n");
    err = alloc_chrdev_region(&dev, 0, MINOR_VERSION, DEVICE_NAME);
    dev_major = MAJOR(dev);
    
    pci_enumerator_class = class_create(THIS_MODULE, DEVICE_NAME);

    cdev_init(&cdev, &fops);
    cdev_add(&cdev, MKDEV(dev_major, MINOR_VERSION), 1);
    device_create(pci_enumerator_class, NULL, MKDEV(dev_major, MINOR_VERSION), NULL, DEVICE_NAME);
    return 0;
}

static void pci_enumerator_exit(void)
{
    printk(KERN_INFO "bye...\n");
}

module_init(pci_enumerator_init);
module_exit(pci_enumerator_exit);