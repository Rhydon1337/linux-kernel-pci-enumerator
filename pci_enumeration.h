#pragma once

#include <linux/list.h>

struct PciID {
    struct list_head pci_ids_list;
    u16 pci_bus_id;
    u16 device_id;
    u16 vendor_id;
    u16 subsystem_id;
    u16 subsystem_vendor_id;
};

struct list_head* pci_enumrator(void);

void clean_up_list(struct list_head* pci_devices);