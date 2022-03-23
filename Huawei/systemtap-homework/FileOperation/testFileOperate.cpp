#include<stdio.h>
#include <unistd.h>
#include "FileOperate.h"

int main(){
	int count = 100;
	for (int i = 0; i < count; i ++){
		FileOperate myfile("./test.txt");
		if(myfile.open(std::fstream::in | std::fstream::out | std::fstream::app)) {
			cout << "open file sucess" << endl;
			myfile.close();
		}	
		sleep(1);
	}
	return 0;
}
