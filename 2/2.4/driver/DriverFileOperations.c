#include "DriverFileOperations.h"
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
	int *pTmp = NULL;

	DEBUG_PRINT(DEVICE_NAME ": ioctl invoked, do nothing\n");
	
	if(1 == uiCmd)
	{
		DEBUG_PRINT(DEVICE_NAME ": uiCmd = 1\n");

		pTmp = (int *)ulArg;
		if(pTmp != NULL)
		{
			DEBUG_PRINT(DEVICE_NAME ": pTmp = %x\n", *pTmp);

			*pTmp = 0x78563412;

			return 0;
		}
		else
		{
			DEBUG_PRINT(DEVICE_NAME ": ulArg = NULL\n");
			return -1;
		}
	}

	return 0;
}

int DriverMMap(struct file *pslFileStruct, struct vm_area_struct *pslVirtualMemoryArea)
{
	DEBUG_PRINT(DEVICE_NAME ": mmap invoked, do nothing\n");
	return 0;
}
