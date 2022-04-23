#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string>

using namespace std;

__thread int x = 5;

int test()
{
	int fd = 0;
	int ret;

	string toSend = "hello driver";

	if((fd = open("/dev/msg_printer", O_RDWR)) < 0)
	{
		cerr << strerror(errno) << endl;	
		return -1;
	}

	ret = write(fd, toSend.c_str(), toSend.size());	
	if(ret < 0)
	{
		cerr << strerror(errno) << endl;
		close(fd);
		return -1;	
	}

	close(fd);

	return 0;
}


void GetGSBase(int t_id)
{
	int fd = 0;
	int ret;

	string toSend = "hello driver";
	toSend += '0' + t_id;
	if((fd = open("/dev/msg_printer", O_RDWR)) < 0)
	{
		cerr << strerror(errno) << endl;	
		return;
	}

	//ret = write(fd, toSend.c_str(), toSend.size());	
	ret = write(fd, toSend.c_str(), t_id);
	if(ret < 0)
	{
		cerr << strerror(errno) << endl;
		close(fd);
		return;	
	}

	close(fd);
}

void *thread(void *arg)
{
	x++;

	long i = (long)arg;
	if(i == 1)
	{
		sleep(3);
		cout << "thread 1: x = " << x << endl;

		unsigned long addr = (unsigned long)(&x);
		cout << "thread 1: addr of x = 0x" << hex << addr << endl;
		GetGSBase(1);
	}
	else
	{
		sleep(i);
		cout << "thread 2: x = " << x << endl;

		unsigned long addr = (unsigned long)(&x);
		cout << "thread 2: addr of x = 0x" << hex << addr << endl;
		GetGSBase(i);
	}

	return (void *)0;
}

int main()
{
	pthread_t tid1;
	pthread_t tid_array[2];
	if(pthread_create(&tid1, NULL, thread, (void *)1) != 0)
	{
		cout << "pthread_create error" << endl;
		return 0;
	}

	pthread_t tid2;
	if(pthread_create(&tid2, NULL, thread, (void *)2) != 0)
	{
		cout << "pthread_create error" << endl;
		return 0;
	}

	for (int i = 0; i < 2; i ++)
	{
		if (pthread_create(&tid_array[i], NULL, thread, (void *)i) != 0)
		{
			cout << "pthread_create erro" << endl;
			return 0;
		}
	}

	pthread_join(tid1, 0);
	pthread_join(tid2, 0);
	for (int i = 0; i < 2; i ++)
	{
		pthread_join(tid_array[i], 0);
	}

	return 0;
}
