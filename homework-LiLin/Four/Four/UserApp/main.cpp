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


int driverIOCtl()
{
	int fd = 0;
	int ret;

	string toSend = "hello driver";

	if((fd = open("/dev/msg_printer", O_RDWR)) < 0)
	{
		cerr << strerror(errno) << endl;	
		return -1;
	}

	ioctl(fd, 0, 0);
	close(fd);

	return 0;
}

int main()
{
	int num_proc = 4;
	int i = 2;
	pid_t child_pid = fork();
	while (child_pid != 0 && i <= num_proc)
	{
		i ++;
		child_pid = fork();
	}

	if (child_pid == 0)
	{
		cout << "child process" << endl;
		int io_time = 100000;
		for (int j = 0; j < io_time; j ++)
			driverIOCtl();
	}
	else
	{	
		for (int j = 0; j < num_proc; j ++)
			wait(NULL);
	}

	cout << child_pid << endl;
	
	return 0;
}

