all: cpu.o main.o
	gcc main.o cpu.o -o main
cpu.o: cpu.c cpu.h
	gcc -c cpu.c
main.o: main.c
	gcc -c main.c
clean:
	rm -rf *.o main
run: main
	./main&
