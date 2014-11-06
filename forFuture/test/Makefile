CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= ../utils/memory.c \
	../utils/singleLinkList.c \
	 ../utils/doubleLinkList.c \
	../utils/stack.c \
	../utils/queue.c \
	test.c
OBJECTS=$(SOURCES:.c=.o)
DEPS= ../include/common.h \
	../include/singleLinkList.h \
	../include/doubleLinkList.h \
	../include/stack.h \
	../include/queue.h \
	../include/memory.h \
	../include/my.h \
	../include/set.h

EXECUTABLE=test

all:$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) test


