#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string>

using namespace std;

int main()
{
	int fd = 0;
	int ret;

	string toSend = "hello driver";

	if((fd = open("/dev/msg_printer", O_RDWR)) < 0)
	{
		cerr << strerror(errno) << endl;	
		return -1;
	}
	
	int length = 100;
	int *input = new int[length];
	int i = 0;
	for (i = 0; i < length; i ++)
	{
		input[i] = i + 1;
	}
	
	printf("the address of input is : %p\n", input);
	int flag = ioctl(fd, (1 << 31) + length, input);
	printf("sum = %d\n", input[0]);
	//printf("%d\n", temp);
	
/*
	ret = write(fd, toSend.c_str(), toSend.size());	
	if(ret < 0)
	{
		cerr << strerror(errno) << endl;
		close(fd);
		return -1;	
	}
*/
	delete input;
	close(fd);

	return 0;
}
