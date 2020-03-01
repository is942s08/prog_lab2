test_app : src/main.c src/IntVector.c src/IntVector.h
	gcc -g -Wall -o test_app src/main.c src/IntVector.c src/IntVector.h