test_app : src/main.c src/IntVector.c src/IntVector.h
	gcc -g -Wall -I include -o test_app src/main.c src/IntVector.c src/IntVector.h