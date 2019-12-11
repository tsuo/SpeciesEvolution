evolution: evolution.o fetch-line.o xmalloc.o random.o linkedlist.o \
	   read.o write.o
	gcc evolution.o fetch-line.o xmalloc.o random.o \
		linkedlist.o read.o write.o -o evolution

evolution.o: evolution.c evolution.h
	gcc -c evolution.c

fetch-line.o: fetch-line.c fetch-line.h
	gcc -c fetch-line.c

xmalloc.o: xmalloc.c xmalloc.h
	gcc -c xmalloc.c

random.o: random.c random.h
	gcc -c random.c

linkedlist.o: linkedlist.c linkedlist.h 
	gcc -c linkedlist.c

read.o: read.c read.h
	gcc -c read.c

write.o: write.c write.h
	gcc -c write.c

clean:
	rm *.o evolution
