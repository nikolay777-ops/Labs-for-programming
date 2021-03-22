Lab2.2.6: Lab2.2.6.c Lab2.2.6.h
		gcc -ansi -pedantic Lab2.2.6.c -o Lab2.2.6 -lm
Lab2.2.6TEST: Lab2.2.6Test.c Lab2.2.6.c Lab2.2.6.h
		 gcc -ansi -pedantic Lab2.2.6.c Lab2.2.6Test.c -o Lab2.2.6Test -D TESTING -lm
Valgrind:
	echo "15\n" > input.txt
	valgrind ./Lab2.2.6 < input.txt
	valgrind ./Lab2.2.6TEST

Linter:
	cpplint --filter=-readability/casting,-legal/copyright Lab2.2.6.c Lab2.2.6TEST.c

TESTALL: Lab2.2.6 Lab2.2.6Test Valgrind Linter
