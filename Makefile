install:
	g++ -std=c++17 `mecab-config --cflags` `mecab-config --libs` ./src/index.cpp -o index `pkg-config --cflags --libs libmongocxx`

	g++ -std=c++17 `mecab-config --cflags` `mecab-config --libs` ./src/search.cpp -o search `pkg-config --cflags --libs libmongocxx`