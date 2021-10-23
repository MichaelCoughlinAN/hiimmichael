# Compilation Flags 
OBJS = main.o vector.o vertex.o face.o edge.o mesh.o
CC = g++
CFLAGS = -Wall -g
ifeq ($(shell uname -s), Darwin)
FRAMEWORK = -framework OpenGL -framework GLUT
else
    FRAMEWORK = -lX11 -lGL -lGLU -lglut -lm
    endif

all: meshloader

meshloader:	$(OBJS)
	$(CC) $(CFLAGS) -o meshloader $(OBJS) $(FRAMEWORK)

main.o:	mesh.h main.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp


mesh.o:	vector.h vertex.h face.h mesh.h mesh.cpp
	$(CC) $(CFLAGS) -c mesh.cpp

edge.o:	vector.h vertex.h face.h edge.h edge.cpp
	$(CC) $(CFLAGS) -c edge.cpp

face.o:	vector.h vertex.h face.h face.cpp
	$(CC) $(CFLAGS) -c face.cpp

vertex.o:	vector.h face.h vertex.h vertex.cpp
	$(CC) $(CFLAGS) -c vertex.cpp	

vector.o:	vector.h vector.cpp
	$(CC) $(CFLAGS) -c vector.cpp

clean:
	rm *.o *~ meshloader
