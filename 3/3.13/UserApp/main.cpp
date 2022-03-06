#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <pthread.h>
#include "../PrintingDriver/IoCtlSupport.h"

using namespace std;

int EnterKernel()
{
	int fd = 0;
	int ret;

	string toSend = "hello driver";

	fd = open("/dev/msg_printer", O_RDWR);
	if(fd < 0)
	{
		cout << "open error" << endl;	
		return -1;
	}

	ret = write(fd, toSend.c_str(), toSend.size());	
	if(ret < 0)
	{
		cout << "write error" << endl;	
		return -1;	
	}

	close(ret);
	return 0;
}

void* ThreadFunc(void *arg)
{
	pthread_mutex_t *pmutex = (pthread_mutex_t *)arg;

	if(pthread_mutex_lock(pmutex) == 0)
	{
		EnterKernel();

		pthread_mutex_unlock(pmutex);
	}
}

int main()
{
	pthread_mutex_t mutex;

	if(pthread_mutex_init(&mutex, 0) != 0)
	{
		cout << "pthread_mutex_init error" << endl;
		return -1;
	}

	pthread_t tid;
	if(pthread_create(&tid, NULL, ThreadFunc, &mutex) != 0)
	{
		cout << "pthread_create error" << endl;
		pthread_mutex_destroy(&mutex);
		return 0;
	}

	if(pthread_mutex_lock(&mutex) == 0)
	{
		EnterKernel();

		pthread_mutex_unlock(&mutex);
	}
	else
		cout << "pthread_mutex_lock error" << endl;

	pthread_join(tid, NULL);

	pthread_mutex_destroy(&mutex);
	
	return 0;
}
