all: teste

teste: cglib.o color.o main.o
	gcc -o teste cglib.o color.o main.o -lm -lX11

color.o: color.c color.h
	gcc -o color.o -c color.c 

cglib.o: cglib.c cglib.h
	gcc -o cglib.o -c cglib.c -lm -lX11

main.o: main.c cglib.h
	gcc -o main.o -c main.c