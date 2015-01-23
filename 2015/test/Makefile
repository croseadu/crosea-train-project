CC=gcc
CFLAGS=-Wall -g
LDFLAGS=
SOURCES=testSingleLinkList.c ../util/singleLinkList.c
TEMP=testSingleLinkList.o ../util/singleLinkList.o

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -g -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@
clean:
	rm test $(TEMP)