CC_FLAGS=-Wall

compile:
	make clean
	mkdir ./build
<<<<<<< HEAD
	cc ./src/main.c ./src/file_handler.h ./src/file_handler.c ./src/packet_builder.h ./src/packet_builder.c -o $@
=======
	cc ${CC_FLAGS} ./src/main.c ./src/file_handler.h ./src/file_handler.c -c
	mv ./*.o ./build/

link:
	gcc ./build/*.o -o ./build/server
>>>>>>> origin/dev

clean:
	rm -rf build
	rm -rf ./src/*.h.*
	rm -rf ./src/a.out
