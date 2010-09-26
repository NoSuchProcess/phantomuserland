#ifndef _PHANTOM_DEVICE_H
#define _PHANTOM_DEVICE_H

#include "vm/object.h"


struct phantom_device;


struct phantom_dev_ops
{
    int (*start)(struct phantom_device *dev); // Start device (begin using)
    int (*stop)(struct phantom_device *dev);  // Stop device

    // Pass in objects to transfer from/to
    // Objects have to be binary or string.
    // Driver will call back (sent/rcvd)
    int (*send)(struct phantom_device *dev, pvm_object_t data);
    int (*recv)(struct phantom_device *dev, pvm_object_t data);

    // Pass in objects to transfer from/to
    // Objects have to be binary or string.
    // No call back. given thread will be awaken after object is done
    int (*sendw)(struct phantom_device *dev, pvm_object_t data, struct data_area_4_thread *tc);
    int (*recvw)(struct phantom_device *dev, pvm_object_t data, struct data_area_4_thread *tc);

    // Access from kernel - can block!
    int (*read)(struct phantom_device *dev, void *buf, int len);
    int (*write)(struct phantom_device *dev, const void *buf, int len);

    // For network devices - get MAC addr
    int (*get_address)(struct phantom_device *dev, void *buf, int len);
};

typedef struct phantom_dev_ops phantom_dev_ops_t;

struct phantom_os_ops
{
    // Driver passes back finished objects - ones that
    // was sent from or recvd to
    int (*sent)(struct phantom_device *dev, pvm_object_t data);
    int (*rcvd)(struct phantom_device *dev, pvm_object_t data);

};

typedef struct phantom_os_ops phantom_os_ops_t;







#define PHANTOM_BUS_TYPE_UNKNOWN 0
#define PHANTOM_BUS_TYPE_ROOT 1

#define PHANTOM_BUS_TYPE_PCI 2
#define PHANTOM_BUS_TYPE_ISA 3
#define PHANTOM_BUS_TYPE_USB 4
#define PHANTOM_BUS_TYPE_FW 5

struct phantom_bus
{
    const char *        	name;
    int                 	type;
    struct phantom_device *     devices; // list
    struct phantom_bus *        buses; // child buses list
    struct phantom_bus *        next; // if i'm a child - here is my next sibling
};

typedef struct phantom_bus phantom_bus_t;

extern phantom_bus_t root_bus;
extern phantom_bus_t isa_bus;
extern phantom_bus_t pci_bus;
extern phantom_bus_t etc_bus;

struct phantom_device
{
    const char *                name;
    int                         seq_number; // Number of the device for the same name (driver)

    void *                      drv_private; // Driver's private part
    void *                      os_private; // Kernel's private part

    phantom_dev_ops_t           dops;
    phantom_os_ops_t            kops;

    phantom_bus_t *		bus;
    struct phantom_device *     next;

    // Main resources
    int                         iobase;
    int                         irq;
    physaddr_t                  iomem;
    size_t                      iomemsize;
};

typedef struct phantom_device phantom_device_t;

void devfs_register_dev( phantom_device_t* dev );


#define phantom_bus_add_dev( bus, dev ) do { (dev)->next = (bus)->devices; (bus)->devices = (dev);  devfs_register_dev( dev ); } while(0)
#define phantom_bus_add_bus( bus, child_bus ) do { (child_bus)->next = (bus)->buses; (bus)->buses = (child_bus); } while(0)


#endif //_PHANTOM_DEVICE_H
