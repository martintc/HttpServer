CC_FLAGS=-Wall

compile:
	make clean
	mkdir ./build
	cc ${CC_FLAGS} ./src/main.c ./src/file_handler.h ./src/file_handler.c -c
	mv ./*.o ./build/

link:
	gcc ./build/*.o -o ./build/server

clean:
	rm -rf build
