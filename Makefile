# Created by: Nasseef Abukamail
# This Makefile will run tests for the stack class
# 
# Usage for Mac and Windows:
#    make 
#    mingw32-make (rename a.out to a.exe)
#

CC = g++
CFLAGS = -g -Wall -std=c++11

# Create the a.out executable, rename if you like
a.out: bug.h ant.h wasp.h main.cc
	$(CC) $(CFLAGS) main.cc -o a.out

clean:
	rm -rf *.o a.out