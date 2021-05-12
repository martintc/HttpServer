./build/server.o: ./src/main.c
	cc ./src/main.c -o $@

clean:
	rm build/*
