#include<stdio.h>
#include<unistd.h>

int main(){
	int count = 1000;
	for (int i = 0; i < count; i ++){
		int length = 100;
		int *value = (int *)malloc(sizeof(int) * length);
		printf("pid : %d, address : 0x%x\n", getpid(), value);
		sleep(1);
		free(value);
	}
	return 0;	
}
