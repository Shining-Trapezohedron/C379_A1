
memchunk: memchunk.o test.o
	gcc -std=c99 -m32 -Wall memchunk.o test.o -o memchunk

memchunk.o: memchunk.c memchunk.h
	gcc -std=c99 -m32 -Wall  -c memchunk.c memchunk.h

test.o: test.c
	gcc -std=c99 -m32 -Wall -c test.c
clean:
	rm -f *.o *.gch memchunk core
backup:
	cp memchunk.c backup.c

tar:
	tar cvf submit.tar *.c *.h Makefile Readme LICENCE
