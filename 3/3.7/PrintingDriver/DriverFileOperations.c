#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <asm/atomic.h>
#include <linux/rwsem.h>
#include <asm/uaccess.h>
#include <asm/desc.h>

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
	DEBUG_PRINT(DEVICE_NAME ": write invoked, do nothing\n");

	struct desc_struct desc;
	
	asm volatile("movq %%gs:%P1, %0" : "=r"(desc) : "m"(gdt_page.gdt[4]));
	DEBUG_PRINT(DEVICE_NAME " gs: gdt_page.gdt[4] = %lx\n", *((unsigned long *)(&desc)));

	asm volatile("movq %%fs:%P1, %0" : "=r"(desc) : "m"(gdt_page.gdt[4]));
	DEBUG_PRINT(DEVICE_NAME " fs: gdt_page.gdt[4] = %lx\n", *((unsigned long *)(&desc)));

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
