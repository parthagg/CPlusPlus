all: search

search: search.o webpage.o database.o
	g++ -g search.o database.o webpage.o -o search

search.o: search.cpp
	g++ -g -c search.cpp -o search.o

crawler: crawler.o webpage.o database.o
	g++ -g crawler.o database.o webpage.o -o crawler

crawler.o: crawler.cpp
	g++ -g -c crawler.cpp -o crawler.o

database.o: database.h webpage.o database.cpp
	g++ -g -Wall -c database.cpp -o database.o

webpage.o: webpage.h webpage.cpp
	g++ -g -Wall -c webpage.cpp -o webpage.o