#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <asm/atomic.h>
#include <linux/rwsem.h>
#include <asm/uaccess.h>
#include <asm/desc.h>
#include <asm/msr.h>

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

	unsigned int gs_base_high, gs_base_low;
	rdmsr(MSR_GS_BASE, gs_base_low, gs_base_high);

	unsigned long gs_base = ((unsigned long)gs_base_high << 32) + gs_base_low;
	DEBUG_PRINT(DEVICE_NAME " gs_base = 0x%lx\n", gs_base);

	unsigned long gdt_offset = (unsigned long)&gdt_page;
	unsigned long gdt4_offset = (unsigned long)&gdt_page.gdt[4];

	DEBUG_PRINT(DEVICE_NAME " gdt_offset = 0x%lx\n", gdt_offset);
	DEBUG_PRINT(DEVICE_NAME " gdt4_offset = 0x%lx\n", gdt4_offset);

	unsigned long gdt_addr = gs_base + gdt_offset;
	unsigned long gdt4_addr = gs_base + gdt4_offset;

	DEBUG_PRINT(DEVICE_NAME " gdt_addr = 0x%lx\n", gdt_addr);
	DEBUG_PRINT(DEVICE_NAME " gdt4_addr = 0x%lx\n", gdt4_addr);

	DEBUG_PRINT(DEVICE_NAME " gdt[4] = 0x%lx\n", *((unsigned long *)gdt4_addr));

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
