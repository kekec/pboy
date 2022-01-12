SUBDIR = gbit

all: cpu.o main.o test_cpu.o testlib
	gcc -L$(SUBDIR) main.o cpu.o test_cpu.o -o main -lgbit

babytest: cpu.o babytest.o 
	gcc babytest.o cpu.o -o babytest

babytest.o: babytest.c
	gcc -c babytest.c

testlib:
	$(MAKE) -C $(SUBDIR)

cpu.o: cpu.c cpu.h
	gcc -I$(SUBDIR) -c cpu.c

main.o: main.c
	gcc -I$(SUBDIR) -c main.c

test_cpu.o: test_cpu.c
	gcc -I$(SUBDIR) -c test_cpu.c
clean:
	make -C $(SUBDIR) clean
	rm -rf *.o main babytest

install: testlib
	sudo cp $(SUBDIR)/libgbit.so /usr/lib

run: main
	./main
