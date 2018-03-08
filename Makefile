all: client server test

client: Client.cpp
	g++ Client.cpp -o Client.out

server: Server.cpp
	g++  Server.cpp -o Server.out

test: test.sh
	chmod +x test.sh
	./test.sh

clean: Server.out Client.out
	rm Server.out
	rm Client.out
