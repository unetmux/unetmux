DEFAULT_GOAL := test

test:
	g++ -o bin/handling_server.exe test/handling_server.cpp src/server.cpp -luv -lllhttp

.PHONY : test