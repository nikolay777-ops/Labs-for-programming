Lab5: Lab5.c
	gcc -ansi -pedantic Lab5.c -o Lab5
Lab5Test: Lab5Test.c Lab5.h Lab5.c
	gcc -ansi -pedantic Lab5Test.c Lab5.h Lab5.c -o Lab5Test
Valgrind:
	valgrind ./Lab5
	valgrind ./Lab5Test
TestAll: Lab5 Lab5Test Valgrind
