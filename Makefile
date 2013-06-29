all: src/ctree.c src/dotfile.c src/dotfile.h src/tree.c src/tree.h src/md5/md5.c src/md5/md5.h
	gcc -Wall -std=c99 -o ctree src/ctree.c src/dotfile.c src/tree.c src/md5/md5.c -lgvc -lcdt -lgraph -lpthread

clean: ctree
	rm -r ctree
