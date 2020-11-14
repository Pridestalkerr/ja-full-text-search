#include <iostream>
#include <bsoncxx/json.hpp>

#include "./include/db.hpp"



int main(int argc, char **argv)
{
    Database db{"mongodb://localhost:27017", "ja-full-text-search"};

    auto tokens = db.insert(argv[1], argv[2]);
    for(auto token : tokens)
    {
        std::cout << token << std::endl;
    }

    return 0;
}