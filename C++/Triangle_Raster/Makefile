CXX=g++
CXXFLAGS=`sdl-config --cflags`
LDFLAGS=`sdl-config --libs`
OBJS=main.o Color.o Rasterizer.o

triangleraster:	$(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o triangleraster

clean:
	rm -f triangleraster
	rm -f $(OBJS)

main.o: main.cpp
Color.o: Color.cpp
Rasterizer.o: Rasterizer.cpp
