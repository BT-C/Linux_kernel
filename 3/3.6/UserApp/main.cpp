#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include "../PrintingDriver/IoCtlSupport.h"

using namespace std;

int main()
{
	int fd = 0;
	int ret;
	unsigned short cs, ds, ss;

	string toSend = "hello driver";

	fd = open("/dev/msg_printer", O_RDWR);
	if(fd < 0)
	{
		cout << "open error" << endl;	
		return -1;
	}

	asm volatile ("mov %%cs, %0 \n\t" : "=m"(cs));
	asm volatile ("mov %%ds, %0 \n\t" : "=m"(ds));
	asm volatile ("mov %%ss, %0 \n\t" : "=m"(ss));

	cout << "user cs : " << hex << cs << endl;
	cout << "user ds : " << hex << ds << endl;
	cout << "user ss : " << hex << ss << endl;

	ret = write(fd, toSend.c_str(), toSend.size());	
	if(ret < 0)
	{
		cout << "write error" << endl;	
		return -1;
	}
	
	close(ret);
	
	return 0;
}
