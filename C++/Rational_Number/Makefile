# Define the C++ compiler to use.
CXX = g++

# Define the flags we want to send to the compiler when we compile.
CPPFLAGS = -Wall -ansi -std=c++0x

# Define any directories we want to add to the default locations
# searched for standard libraries of object code.
INCLUDES =

# Define any additional libraries that our code requires.
LIBS =

# Define any flags required by those libraries.
LFLAGS =

# Define the name of the executable that we are creating here.
TARGET = lab6

# Define a list of source files used to make the TARGET executable.
SRCS = $(TARGET).cpp Rational.cpp PrecondViolatedExcep.cpp

# Define the names of the intermediate object files that will be
# created in the compilation of the TARGET executable.
OBJS = $(SRCS:.cpp=.o)

# Define phony targets in this Makefile - that is, targets that do not
# lead to an executable product.
#
# The command:
# % make clean
#
# will remove intermediate object files and the TARGET executable from
# the system, allowing the system to be rebuilt from scratch.
#
# The command:
# % make
#
# will (re)build TARGET.

# The (first and thus) default target in this Makefile.  A target has
# the form:
#
# target : dependency1 dependency2 ...
# <tab> command
# <tab> optionalCommand
# ...
# In this case, the command simply echos to the screen.

all: $(TARGET)
	@echo All done compiling $(TARGET)

# A target defining how to build the TARGET executable.  The TARGET
# is dependent on the object files.  The command builds the excutable
# TARGET.

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

# A target defining how to build an object file (.o) from a source
# file (.cpp).  The $@ in the command represents the object file to
# the left of the ':'.  The $< in the command represents the source
# file to the right of the ':'.

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

# The clean phony target.

.PHONY: clean

clean:
	-$(RM) $(TARGET) *.exe *.o *~ *.bak core *.stackdump *.dep
	chmod 644 *

%.dep: %.cpp
	$(CXX) -MM $(CPPFLAGS) $< -MF $@

-include $(OBJS:.o=.dep)
