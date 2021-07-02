CC_FLAGS=-Wall -g

compile:
	make clean
	mkdir ./build
	cc ${CC_FLAGS} ./src/main.c ./src/file_handler.h ./src/file_handler.c ./src/packet_builder.h ./src/packet_builder.c ./src/packet_parser.h ./src/packet_parser.c -c
	mv ./*.o ./build/

link:
	gcc ./build/*.o -o ./build/thttp

clean:
	rm -rf build
	rm -rf ./src/*.h.*
	rm -rf ./src/a.out
