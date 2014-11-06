CC = gcc

CFLAGS = -c -std=c99 -Wall

LIBS = -lgvc -lcdt -lcgraph -lpthread

SOURCES = ctree.o dotfile.o tree.o md5.o

OBJECTS = $(SOURCES:.c = .o)

EXECUTABLE = ctree

all: $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS) $(LIBS)

ctree.o: src/ctree.c
	$(CC) $(CFLAGS) src/ctree.c

dotfile.o: src/dotfile.c src/dotfile.h
	$(CC) $(CFLAGS) src/dotfile.c

tree.o: src/tree.c src/tree.h
	$(CC) $(CFLAGS) src/tree.c

md5.o: src/md5/md5.c src/md5/md5.h
	$(CC) $(CFLAGS) src/md5/md5.c

.PHONY : clean
clean:
	rm -r $(OBJECTS)
