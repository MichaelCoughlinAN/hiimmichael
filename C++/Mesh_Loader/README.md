3D Mesh Loading and Rendering
==============
This program renders a world consisting of a set of polygonal meshes, where each mesh is defined in a separate file with ".off" suffix. 

Features
--------------

- parallel/perspective projection
- animate/freeze mesh
- animate/freeze light
- flat/smooth shading
- zoom in/out
- vertex mode
- edge mode
- face mode
- Left mouse click-and-drag rotation of the universe
- Animate/freeze light source

Complie
--------------
Standard Compilation - use make (make clean removes unnecessary files):

    make
    ./meshloader [file_names]


Usage
--------------
This program accepts a list of file names as command line inputs. 
Usage:

    ./meshloader [file_names]
Example:

    ./meshloader venus.off eight.off

The format of a polygon-mesh text file is expected to follow the format below:
number-of-vertices number-of-faces	//int int
//for each vertex:
x y z					//3 doubles
//for each face:
list of vertices by index		//int list

User Interaction: (keyboard shortcuts)
'p': parallel/perspective projection
'a': animate/freeze mesh
'l': animate/freeze light
's': flat/smooth shading
'UP': zoom in
'DOWN': zoom out
'v': vertex mode
'e': edge mode
'f': face mode
q/Q/escape: quit


FILES
-------------
- README
- C++ files: main.cpp vector.cpp vertex.cpp edge.cpp face.cpp mesh.cpp 
- Header files: main.h vector.h vertex.h edge.h face.h mesh.h mats.h
- Executable C program: meshloader
- Makefile

This program is divided into 6 separate files

1) vector.cpp
This is our self-constructed vector library.

2) vertex.cpp
This class represents a single node of vertex. It stores the position of vertex, the vertex norm, the index, and a list of pointers to its adjacent faces.

3) face.cpp
This class represents a single node of face. It stores the face norm, and a list of the adjacent vertices.

4) edge.cpp
This class represents a single node of edge. It stores two vertices and two adjacent faces.

5) mesh.cpp
This class represents a single node of mesh to be drawn. It stores lists of vertices, faces, and edges required for a polygonal mesh. 

6) main.cpp
This is where the main() is at. For user-interactive purpose it handles situations with mouse and keyboard input.
