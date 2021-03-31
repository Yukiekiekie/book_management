bmain:book_management.o main.o
	gcc book_management.o main.o -o main
book_management.o:book_management.c book_management.h
	gcc -c book_management.c -o book_management.o
main.o:main.c book_management.h
	gcc -c main.c -o main.o
clean:
	rm -rf *.o main
