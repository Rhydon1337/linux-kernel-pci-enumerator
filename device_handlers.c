#include "device_handlers.h"

#include <linux/uaccess.h>

#include "consts.h"
#include "pci_enumeration.h"

int device_open(struct inode *inode, struct file *file) {
    return SUCCESS;
}

int device_close(struct inode *inode, struct file *file) {
    return SUCCESS;
}

ssize_t device_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
   char* pci_devices;
   size_t length;
   if (0 != *offset) {
       return 0;
   }
   pci_devices = pci_enumrator();
   pci_devices = "Hi\n";
   length = strlen(pci_devices);
   copy_to_user(buffer, pci_devices, length);
   *offset = length;
   return length;
}