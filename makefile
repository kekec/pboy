SUBDIR = gbit

all: cpu.o main.o test_cpu.o mmu.o timer.o testlib
	gcc -L$(SUBDIR) main.o cpu.o test_cpu.o timer.o mmu.o -o main -lgbit

babytest: cpu.o babytest.o mmu.o timer.o
	gcc babytest.o cpu.o mmu.o timer.o -o babytest

babytest.o: babytest.c
	gcc -c babytest.c

testlib:
	$(MAKE) -C $(SUBDIR)

cpu.o: cpu.c cpu.h
	gcc -I$(SUBDIR) -c cpu.c

mmu.o: mmu.c mmu.h
	gcc -I$(SUBDIR) -c mmu.c

timer.o: timer.c timer.h
	gcc -I$(SUBDIR) -c timer.c

main.o: main.c
	gcc -I$(SUBDIR) -c main.c

test_cpu.o: test_cpu.c
	gcc -I$(SUBDIR) -c test_cpu.c
clean:
	make -C $(SUBDIR) clean
	rm -rf *.o main babytest rom.gb

install: testlib
	sudo cp $(SUBDIR)/libgbit.so /usr/lib

run: main
	./main
