SUBDIR = gbit
IDIR = $(SUBDIR)/lib/

all: cpu.o main.o testlib
	gcc main.o cpu.o -o main

testlib:
	$(MAKE) -C $(SUBDIR)

cpu.o: cpu.c cpu.h
	gcc -I$(IDIR) -c cpu.c

main.o: main.c
	gcc -I$(IDIR) -c main.c
clean:
	make -C $(SUBDIR) clean
	rm -rf *.o main

run: main
	./main&
