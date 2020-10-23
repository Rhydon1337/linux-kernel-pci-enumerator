#include "device_handlers.h"

#include <linux/uaccess.h>

#include "consts.h"
#include "pci_enumeration.h"

#define OUTPUT_BUFFER_FORMAT "Bus id: %04x\nVendor id: %04x\nDevice id: %04x\nSubsytem id: %04x\nSubsytem vendor id: %04x\n"
#define MAX_MESSAGE_SIZE (sizeof(OUTPUT_BUFFER_FORMAT) + 4 * 4)

int device_open(struct inode *inode, struct file *file)
{
    return SUCCESS;
}

int device_close(struct inode *inode, struct file *file)
{
    return SUCCESS;
}

ssize_t device_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    char message[MAX_MESSAGE_SIZE];
    struct list_head* pci_devices;
    struct PciID *pci_id;
    size_t length = 0;
    size_t number_of_devices = 0;
    if (0 != *offset) {
        return 0;
    }
    pci_devices = pci_enumrator();
    
    list_for_each_entry(pci_id, pci_devices, pci_ids_list) {
        ++number_of_devices;
    }
    if (number_of_devices * MAX_MESSAGE_SIZE > len) {
        clean_up_list(pci_devices);
        return -EMSGSIZE;
    }
    
    list_for_each_entry(pci_id, pci_devices, pci_ids_list)
    {
        memset(message, 0, MAX_MESSAGE_SIZE);
        sprintf(message, OUTPUT_BUFFER_FORMAT, pci_id->pci_bus_id, pci_id->vendor_id, pci_id->device_id, pci_id->subsystem_id, pci_id->subsystem_vendor_id);
        copy_to_user(buffer + length, message, strlen(message));
        length += strlen(message);
    }
    *offset = length;
    clean_up_list(pci_devices);
    return length;
}