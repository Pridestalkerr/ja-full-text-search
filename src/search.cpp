#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/string/to_string.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

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