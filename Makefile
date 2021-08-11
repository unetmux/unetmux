test: test_handling_server test_http_parser
	@echo executibles are stored in the bin directory

test_handling_server:
	g++ -o bin/handling_server.exe test/handling_server.cpp src/server.cpp -luv -lllhttp

test_http_parser:
	g++ -o bin/http_parser_test.exe test/http_parser.c -lllhttp

.PHONY : test_handling_server test_http_parser