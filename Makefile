all: test_app 

src/%.o : src/%.c
	gcc -Wall -I include -c -o $@ $< 

test_app : src/main.o src/IntVector.o
	gcc -Wall -o test_app src/main.o src/IntVector.o

clean:
	rm -f test_app src/*.o
