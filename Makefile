./build/server.o: ./src/main.c
	make clean
	mkdir ./build
	cc ./src/main.c ./src/file_handler.h ./src/file_handler.c -o $@

clean:
	rm -rf build
