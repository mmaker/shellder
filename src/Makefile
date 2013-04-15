CC=gcc
CFLAGS:=$(CFLAGS) -ansi -Wall -fstack-protector -lreadline -ggdb
EXECUTABLE=shellder


SOURCES=shell.c utils.c process.c
OBJECTS=$(SOURCES: .c=.o)


%.o:  %.c
	$(CC) $(CFLAGS) -c $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

all: $(SOURCES) $(EXECUTABLE)

.PHONY:	clean

clean:
	find -name '*.o' -delete
	find -executable -delete


