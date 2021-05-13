./build/server.o: ./src/main.c
	make clean
	mkdir ./build
	cc ./src/main.c -o $@

clean:
	rm -rf build
