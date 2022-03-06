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
	return 0;
}

long DriverIOControl(struct file *pslFileStruct, unsigned int uiCmd, unsigned long ulArg)
{
	int i = 0;
	unsigned int flag = ((uiCmd & 0x80000000) >> 31);
	unsigned int length = (uiCmd & 0x7FFFFFFF);

	DEBUG_PRINT(DEVICE_NAME ": ioctl invoked, do nothing\n");
	DEBUG_PRINT(DEVICE_NAME ": in ioctl uiCmd = %u, ulArg = %lu", uiCmd, ulArg);
	DEBUG_PRINT(DEVICE_NAME ": size of the ulArg is %ld", sizeof(ulArg));
	DEBUG_PRINT(DEVICE_NAME ": the address of ulArg is: %lx", ulArg);

	DEBUG_PRINT(DEVICE_NAME ": operation flag  = %d", flag);
	DEBUG_PRINT(DEVICE_NAME ": input length = %d", length);

	if (flag != 1)
		return -1;

	int *inputList = (int *)kmalloc(sizeof(int) * length, GFP_KERNEL);
	copy_from_user(inputList, ulArg, sizeof(int) * length);
	int tempSum = 0;
	
	for (i = 0; i < length; i ++)
	{
		DEBUG_PRINT(DEVICE_NAME " the value of %d element is %d", i, inputList[i]);
		tempSum += inputList[i];
	}
	
	copy_to_user(ulArg, &tempSum, sizeof(int));
	kfree(inputList);
	return 0;
}

int DriverMMap(struct file *pslFileStruct, struct vm_area_struct *pslVirtualMemoryArea)
{
	DEBUG_PRINT(DEVICE_NAME ": mmap invoked, do nothing\n");
	return 0;
}
