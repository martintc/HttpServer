./build/server.o: ./src/main.c
	mkdir ./build
	cc ./src/main.c -o $@

clean:
	rm build/*
