Lab2.2.6: Lab2.2.6.c Lab2.2.6.h
		gcc -o Lab2.2.6 Lab2.2.6.c -ansi -pedantic -lm 
Lab2.2.6TEST: Lab2.2.6.c Lab2.2.6.h Lab2.2.6Test.c 
		 gcc -o Lab2.2.6Test Lab2.2.6Test.c Lab2.2.6.c -ansi -pedantic -D TESTING -lm
Valgrind:
	echo "15\n0.001\n" > input.txt
	valgrind ./Lab2.2.6 < input.txt
	valgrind ./Lab2.2.6Test

TESTALL: Lab2.2.6 Lab2.2.6TEST Valgrind 
