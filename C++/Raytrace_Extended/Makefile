# Compilation Flags 
OBJS = vector.o texture.o matrix.o vertex.o face.o mesh.o light.o surFinish.o util.o ray.o shape.o image.o scene.o main.o
CC = g++
CFLAGS = -Wall -g 

all: raytracer

raytracer:	$(OBJS)
	$(CC) $(CFLAGS) -o raytracer $(OBJS) 

main.o:	vector.h matrix.h light.h surFinish.h ray.h shape.h image.h main.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp	

scene.o:	vector.h matrix.h light.h surFinish.h ray.h shape.h image.h scene.h scene.cpp
	$(CC) $(CFLAGS) -c scene.cpp	

image.o:	vector.h image.h image.cpp
	$(CC) $(CFLAGS) -c image.cpp	

shape.o:	vector.h matrix.h surFinish.h ray.h shape.h shape.cpp
	$(CC) $(CFLAGS) -c shape.cpp	

util.o:	vector.h util.h util.cpp
	$(CC) $(CFLAGS) -c util.cpp	

ray.o:	vector.h ray.h ray.cpp
	$(CC) $(CFLAGS) -c ray.cpp

surFinish.o: surFinish.h surFinish.cpp
	$(CC) $(CFLAGS) -c surFinish.cpp

light.o:	vector.h light.h light.cpp
	$(CC) $(CFLAGS) -c light.cpp

mesh.o:	vector.h vertex.h face.h mesh.h mesh.cpp
	$(CC) $(CFLAGS) -c mesh.cpp	

face.o:	vector.h vertex.h face.h face.cpp
	$(CC) $(CFLAGS) -c face.cpp	

vertex.o:	vector.h face.h vertex.h vertex.cpp
	$(CC) $(CFLAGS) -c vertex.cpp

matrix.o:	vector.h matrix.h matrix.cpp
	$(CC) $(CFLAGS) -c matrix.cpp	

texture.o:	texture.h texture.cpp
	$(CC) $(CFLAGS) -c texture.cpp	

vector.o:	vector.h vector.cpp
	$(CC) $(CFLAGS) -c vector.cpp

clean:
	rm *.o raytracer *~ *.ppm
