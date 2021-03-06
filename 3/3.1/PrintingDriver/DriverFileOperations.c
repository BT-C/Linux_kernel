#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <asm/atomic.h>
#include <linux/rwsem.h>
#include <asm/uaccess.h>

#include "DriverFileOperations.h"
#include "DriverMain.h"
#include "ToolFunctions.h"
#include "IoCtlSupport.h"

int DriverOpen(struct inode *pslINode, struct file *pslFileStruct)
{
	DEBUG_PRINT(DEVICE_NAME ": open invoked, do nothing\n");
	return 0;
}

int DriverClose(struct inode *pslINode, struct file *pslFileStruct)
{
	DEBUG_PRINT(DEVICE_NAME ": close invoked, do nothing\n");
	return 0;
}

ssize_t DriverRead(struct file *pslFileStruct, char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	DEBUG_PRINT(DEVICE_NAME ": read invoked, do nothing\n");
	return 0;
}

ssize_t DriverWrite(struct file *pslFileStruct, const char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	unsigned long gdt_addr;
	unsigned short cs, ds, ss;
	char gdtr[6] = {0};

	DEBUG_PRINT(DEVICE_NAME ": write invoked, do nothing\n");

	asm volatile ("mov %%cs, %0 \n\t" : "=m"(cs));
	asm volatile ("mov %%ds, %0 \n\t" : "=m"(ds));
	asm volatile ("mov %%ss, %0 \n\t" : "=m"(ss));

	DEBUG_PRINT("kernel cs: %x\n", cs);
	DEBUG_PRINT("kernel ds: %x\n", ds);
	DEBUG_PRINT("kernel ss: %x\n", ss);

	asm volatile ("sgdt %0\n\t" : "=m"(gdtr) : :);

	DEBUG_PRINT("gdtr is: \n");
	MEM_PRINT((unsigned long)gdtr, 6);

	gdt_addr = (*(unsigned long *)(gdtr + 2));
	
	DEBUG_PRINT("GDT:\n");
	MEM_PRINT(gdt_addr, 8*32);

	return 0;
}

long DriverIOControl(struct file *pslFileStruct, unsigned int uiCmd, unsigned long ulArg)
{
	DEBUG_PRINT(DEVICE_NAME ": ioctl invoked, do nothing\n");
	return 0;
}

int DriverMMap(struct file *pslFileStruct, struct vm_area_struct *pslVirtualMemoryArea)
{
	DEBUG_PRINT(DEVICE_NAME ": mmap invoked, do nothing\n");
	return 0;
}
