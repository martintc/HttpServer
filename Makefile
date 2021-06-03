./build/server.o: ./src/main.c
	make clean
	mkdir ./build
	cc ./src/main.c ./src/file_handler.h ./src/file_handler.c ./src/packet_builder.h ./src/packet_builder.c -o $@

clean:
	rm -rf build
	rm -rf ./src/*.h.*
	rm -rf ./src/a.out
