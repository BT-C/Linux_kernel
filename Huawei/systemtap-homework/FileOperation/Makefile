main:testFileOperate.o FileOperate.o
	g++ testFileOperate.o FileOperate.o -o cbt_file_operate

FileOperate.o:FileOperate.cpp FileOperate.h
	g++ -c FileOperate.cpp -o FilerOperate.o
testFileOperate.o:testFileOperate.cpp
	g++ -c testFileOperate.cpp -o testFileOperate.o

clean:
	rm -rf *.o 
