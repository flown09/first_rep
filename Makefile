all: s21_cat

s21_cat: main.o flag-s.o
	gcc flag-s.o main.o -o s21_cat

flag-s.o: flag-s.c
	gcc -c flag-s.c -o flag-s.o

main.o: main.c
	gcc -c main.c -o main.o

clean: 
	DEL *.o *.exe

rebuild:
	clean all