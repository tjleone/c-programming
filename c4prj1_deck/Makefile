# Makefile for gtest examples

GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/local/include

G++ = g++
G++_FLAGS = -c -Wall -I $(GOOGLE_TEST_INCLUDE)
LD_FLAGS = -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread

CC = gcc
CFLAGS = -ggdb -Wall -Werror -pedantic

OBJECTS = poker_unittest.o cards.o deck.o eval.o gtest_main.o
TARGET = poker

all: $(TARGET)

$(TARGET): $(OBJECTS)
	    g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o : %.cpp
	    $(G++) $(G++_FLAGS) $<

%.o : %.c
	    $(CC) $(G++_FLAGS) $(CFLAGS) $<

clean:
	    rm -f $(TARGET) $(OBJECTS)

PHONY: all clean
