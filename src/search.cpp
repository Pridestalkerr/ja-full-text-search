#include <iostream>
#include <bsoncxx/json.hpp>

#include "./include/db.hpp"



int main(int argc, char **argv)
{
    Database db{"mongodb://localhost:27017", "ja-full-text-search"};

    auto results = db.find(argv[1]);
    for(auto result : results)
    {
        std::cout << bsoncxx::to_json(*result) << std::endl << std::endl;
    }

    return 0;
}