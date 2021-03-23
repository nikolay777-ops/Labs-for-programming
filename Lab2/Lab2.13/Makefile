Lab2.13: Lab2.13.c 
		gcc -ansi -pedantic Lab2.13.c -o Lab2.13 -lm
Lab2.13TEST: Lab2.13Test.c Lab2.13.c 
		 gcc -ansi -pedantic Lab2.13.c Lab2.13Test.c -o Lab2.13Test -D TESTING -lm
Valgrind:
	echo "2 3\n5 6\n5 6\n8 4\n8 4\n2 3\n" > input.txt
	valgrind ./Lab2.13 < input.txt
	valgrind ./Lab2.13Test

TESTALL: Lab2.13 Lab2.13TEST Valgrind 
