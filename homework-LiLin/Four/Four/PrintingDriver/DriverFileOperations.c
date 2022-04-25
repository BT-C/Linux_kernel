#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <asm/atomic.h>
#include <linux/rwsem.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>

#include "DriverFileOperations.h"
#include "DriverMain.h"
#include "ToolFunctions.h"

DEFINE_PER_CPU(long, gUsage) = 0;
//unsigned long count = 0;
//atomic_t count;
int count_init = 0;

int DriverOpen(struct inode *pslINode, struct file *pslFileStruct)
{
	//DEBUG_PRINT(DEVICE_NAME ": open invoked, do nothing\n");
	return 0;
}

int DriverClose(struct inode *pslINode, struct file *pslFileStruct)
{
	//DEBUG_PRINT(DEVICE_NAME ": close invoked, do nothing\n");
	return 0;
}

ssize_t DriverRead(struct file *pslFileStruct, char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	DEBUG_PRINT(DEVICE_NAME ": read invoked, do nothing\n");
	return 0;
}

ssize_t DriverWrite(struct file *pslFileStruct, const char __user *pBuffer, size_t nCount, loff_t *pOffset)
{
	/*
	int i;
	int j = 0;
	long *pUsage = NULL;

	DEBUG_PRINT(DEVICE_NAME ": write invoked, do nothing\n");

	pUsage = this_cpu_ptr((long *)(&gUsage));
	
	DEBUG_PRINT(DEVICE_NAME ": pUsage = 0x%lx", (unsigned long)pUsage);

	for(i = 0; i < 10; i++)
	{
		DEBUG_PRINT(DEVICE_NAME ": CPU %d base = %lx\n", i, __per_cpu_offset[i]);
	}

	DEBUG_PRINT(DEVICE_NAME ": NR_CPUS = %d\n", NR_CPUS);

	for_each_online_cpu(j)
	{
		DEBUG_PRINT(DEVICE_NAME " CPU %d per cpu base = %lx\n", j, __per_cpu_offset[j]);
	}
	*/
	
	DEBUG_PRINT("==================================\n");
	DEBUG_PRINT("name : %d\n", nCount);
	unsigned long gsbase = (unsigned long)this_cpu_ptr((long *)(0));
	
	DEBUG_PRINT(DEVICE_NAME ": gsbase = 0x%lx", (unsigned long)gsbase);

	int i = 0;
	int j = 0;
	for(i = 0; i < 10; i++)
	{
		DEBUG_PRINT(DEVICE_NAME ": CPU %d base = %lx\n", i, __per_cpu_offset[i]);
	}
	
	DEBUG_PRINT("------------------------------------------\n");
	for_each_online_cpu(j)
	{
		DEBUG_PRINT(DEVICE_NAME " CPU %d per cpu base = %lx\n", j, __per_cpu_offset[j]);
	}

	unsigned int gs_base_high, gs_base_low;
	asm volatile ("mov $0xc0000101, %%ecx \n\t"
		"rdmsr \n\t" : "=d"(gs_base_high), "=a"(gs_base_low) : : "%ecx", "memory");

	unsigned long gs_base = ((unsigned long)gs_base_high << 32) + gs_base_low;
	DEBUG_PRINT(DEVICE_NAME " gs_base = 0x%lx\n", gs_base);

	return 0;
}

long DriverIOControl(struct file *pslFileStruct, unsigned int uiCmd, unsigned long ulArg)
{
	
	//DEBUG_PRINT(DEVICE_NAME ": ioctl invoked, do nothing\n");
	//atomic_inc(&in_count);
	//DEBUG_PRINT("%d\n", atomic_read(&in_count));
	long *pUsage = NULL;
	pUsage = this_cpu_ptr((long *)(&gUsage));
	//(*pUsage)++;
	int tempUsage = (*pUsage) + 1;
	int temp = 0;
	int i = 0;
	for (i = 0; i < 1000000000; i ++)
		temp = 99 * 99;
	long *nowUsage = NULL;
	nowUsage = this_cpu_ptr((long *)(&gUsage));
	if (nowUsage != pUsage)
		DEBUG_PRINT("CPU SHCHEDULE from %ld to %ld\n", pUsage, nowUsage);
	(*pUsage) = tempUsage;
	int preemptCount = preempt_count();
	//DEBUG_PRINT("%d\n", &gUsage);
	
	//DEBUG_PRINT("%d per_cpu_usage : %d", 1, per_cpu(gUsage, 1));
	//DEBUG_PRINT("%d\n", *pUsage);
	return 0;
}

int DriverMMap(struct file *pslFileStruct, struct vm_area_struct *pslVirtualMemoryArea)
{
	DEBUG_PRINT(DEVICE_NAME ": mmap invoked, do nothing\n");
	return 0;
}
