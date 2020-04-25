# Name: Thomas Paris
# Project: lab2 - Launch Tube

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.

# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXEC_LAUNCH=launch
SRC_LAUNCH=launch.c
OBJ_LAUNCH=launch.o
EXEC_TUBE=tube
SRC_TUBE=tube.c
OBJ_TUBE=tube.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g -Wall -Wextra
SOURCES=EXEC_LAUNCH EXEC_TUBE

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: $(EXEC_TUBE) $(EXEC_LAUNCH)

# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
$(EXEC_LAUNCH): $(SRC_LAUNCH)
	$(CC) $(CFLAGS) -c $(SRC_LAUNCH)
	$(CC) $(CFLAGS) -o $@ $(OBJ_LAUNCH)

$(EXEC_TUBE): $(SRC_TUBE)
	$(CC) $(CFLAGS) -c $(SRC_TUBE)
	$(CC) $(CFLAGS) -o $@ $(OBJ_TUBE)


# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXEC_LAUNCH) $(OBJ_LAUNCH) *~
	rm -f $(EXEC_TUBE) $(OBJ_TUBE) *~
