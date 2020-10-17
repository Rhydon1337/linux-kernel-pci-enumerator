#include "pci_enumeration.h"

#include <linux/pci.h>

char* pci_enumrator(void) {
    struct pci_bus* bus;
	list_for_each_entry(bus, &pci_root_buses, node) {
        
    }
    return NULL;
}