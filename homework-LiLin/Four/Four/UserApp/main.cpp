#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>

using namespace std;


int driverIOCtl(int len, int pid)
{
	int fd = 0;
	int ret;

	string toSend = "hello driver";

	if((fd = open("/dev/msg_printer", O_RDWR)) < 0)
	{
		cerr << strerror(errno) << endl;	
		return -1;
	}

	ioctl(fd, len, pid);
	close(fd);

	return 0;
}

int main()
{
	int num_proc = 128;
	int i = 2;
	int pid_num = 0;
	pid_t child_pid = fork();
	while (child_pid != 0 && i <= num_proc)
	{
		i ++;
		child_pid = fork();
		pid_num ++ ;
	}

	if (child_pid == 0)
	{
		//int io_time = 40000000;
		int io_time = 1;
		//if (pid_num + 1 == num_proc)
			//sleep(5);
		for (int j = 0; j < io_time; j ++)
			driverIOCtl(num_proc, pid_num);
		printf("pid_num : %d\n", pid_num);
	}
	else
	{	
		for (int j = 0; j < num_proc; j ++)
			wait(NULL);
	}

	
	return 0;
}

