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

	int *pTmp = new int;
	*pTmp = 0x12345678;

	ret = ioctl(fd, 1, (void *)pTmp);
	if(ret < 0)
	{
		cerr << strerror(errno) << endl;
		close(fd);
		return -1;	
	}

	cout << "After ioctl pTmp = " << hex << *pTmp << endl;

	delete pTmp;

	close(fd);

	return 0;
}
