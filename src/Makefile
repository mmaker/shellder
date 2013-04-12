CC=gcc
CFLAGS:=$(CFLAGS) -ansi -Wall -fstack-protector
EXECUTABLE=shellder


SOURCES=shell.c utils.c
OBJECTS=$(SOURCES: .c=.o)


%.o:  %.c
	$(CC) $(CFLAGS) -c $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

all: $(SOURCES) $(EXECUTABLE)

.PHONY:	clea

clean:
	find -name '*.o' -delete
	find -executable -delete


