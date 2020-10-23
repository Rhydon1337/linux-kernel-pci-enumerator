# linux-kernel-pci-enumerator
## TL;DR
Enumrate all PCI devices inside all PCI buses in other words my lightweight lspci.

Tested on linux kernel version: 4.19.91, 5.4.0-48-generic.

## How it works
First of all, we must understand how the CPU is able to communicate with peripheral devices in a computer (disk, mouse, keyboard etc).
In personal comuper there are two different configurations to achieve this:

* **Memory-mapped I/O uses the same address space to address both memory and I/O devices.** The memory and registers of the I/O devices are mapped to address values. So when an address is accessed by the CPU, it may refer to a portion of physical RAM, or it can instead refer to memory of the I/O device. Thus, the CPU instructions used to access the memory can also be used for accessing devices.

* Port-mapped I/O often uses a special class of CPU instructions designed specifically for performing I/O, such as the in and out instructions found on processors based on the x86 and x86-64 architectures. **I/O devices have a separate address space from general memory, either accomplished by an extra "I/O" pin on the CPU's physical interface, or an entire bus dedicated to I/O.**

### Note: the processor fetches data from address spaces and we can control from which address space it will be.

There are three well known address spaces:

* RAM.
* Isolated I/O (Port-mapped I/O which mentioned above) - method of performing input/output (I/O) between the central processing unit (CPU) and peripheral devices in a computer.
* PCI configuration space - the PCI specification provides for totally software driven initialization and configuration of each device (or target) on the PCI Bus via a separate Configuration Address Space.

### Note: the configuration space is typically 256 bytes, and can be accessed with read/write. The target device for the configuration space access is selected with the initialization device select (IDSEL - individual device select for configuration) signal, which is then decoded by the target device.

The kernel module iterate on every PCI device configuartion on every PCI bus and will fetch device_id, vendor_id, subsystem_id, subsystem_vendor_id and subsystem_vendor_id.

![image](https://upload.wikimedia.org/wikipedia/commons/c/ca/Pci-config-space.svg)

## Limitations
Currently, there is no support for PCI-e (pci express).

## Usage
cd linux-kernel-pci-enumerator

make

insmod pci_enumerator.ko

cat /dev/pci_enumerator

DONE!!!
