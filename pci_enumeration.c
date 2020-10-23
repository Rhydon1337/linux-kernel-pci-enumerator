#include "pci_enumeration.h"

#include <linux/pci.h>

#define MAX_NUMBER_OF_PCI_DEV_PER_BUS 255

struct list_head* pci_enumrator(void) {
    struct list_head *pci_ids = kmalloc(sizeof(struct list_head), GFP_KERNEL);
    struct pci_bus* bus;
    struct PciID* pci_id;
    size_t i, j;
    INIT_LIST_HEAD(pci_ids);
    j = 0;
    list_for_each_entry(bus, &pci_root_buses, node) {
        for (i = 0; i < MAX_NUMBER_OF_PCI_DEV_PER_BUS; i++) {
            u16 device_id = 0;
            u16 vendor_id = 0;
            u16 subsystem_id = 0;
            u16 subsystem_vendor_id = 0;
            pci_bus_read_config_word(bus, i, 0, &device_id);
            pci_bus_read_config_word(bus, i, 2, &vendor_id);
            pci_bus_read_config_word(bus, i, 44, &subsystem_id);
            pci_bus_read_config_word(bus, i, 46, &subsystem_vendor_id);
            if (device_id == U16_MAX || vendor_id == U16_MAX) {
                continue;
            }
            pci_id = kmalloc(sizeof(struct PciID), GFP_KERNEL);
            pci_id->pci_bus_id = (u16)j;
            pci_id->device_id = device_id;
            pci_id->vendor_id = vendor_id;
            pci_id->subsystem_id = subsystem_id;
            pci_id->subsystem_vendor_id = subsystem_vendor_id;
            pci_id->pci_ids_list.next = NULL;
            list_add_tail(&pci_id->pci_ids_list, pci_ids);
            
        }
        ++j;
    }
    return pci_ids;
}

void clean_up_list(struct list_head* pci_devices) {
    struct PciID* pci_id;
    struct list_head *pos, *q;
    list_for_each_safe(pos, q, pci_devices) {
        pci_id = list_entry(pos, struct PciID, pci_ids_list);
        list_del(pos);
        kfree(pci_id);
    }
    kfree(pci_devices);
}