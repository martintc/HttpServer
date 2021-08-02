CC_FLAGS=-Wall -g

CC_FLAGS_DEBUG=-Wall -g -fsanitize=undefined -fsanitize=address

compile:
	make clean
	mkdir ./build
	cc ${CC_FLAGS} ./src/main.c ./src/file_handler.h ./src/file_handler.c ./src/packet_builder.h ./src/packet_builder.c ./src/packet_parser.h ./src/packet_parser.c ./src/log.h ./src/log.c -c
	mv ./*.o ./build/
	gcc ./build/*.o -o ./build/thttp

jenkins:
	make clean
	mkdir ./build
	cc ${CC_FLAGS} ./src/main.c ./src/file_handler.h ./src/file_handler.c ./src/packet_builder.h ./src/packet_builder.c ./src/packet_parser.h ./src/packet_parser.c ./src/log.h ./src/log.c -c
	mv ./*.o ./build/

debug:
	make clean
	mkdir ./build
	cc ${CC_FLAGS} ./src/main.c ./src/file_handler.h ./src/file_handler.c ./src/packet_builder.h ./src/packet_builder.c ./src/packet_parser.h ./src/packet_parser.c ./src/log.h ./src/log.c -c
	mv ./*.o ./build/
	gcc ${CC_FLAGS_DEBUG} ./build/*.o -o ./build/thttp

clean:
	rm -rf build
	rm -rf ./src/*.h.*
	rm -rf ./src/a.out
