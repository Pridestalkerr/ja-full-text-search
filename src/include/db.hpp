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

#include "tokenizer.hpp"



class Database
{

private:

	mongocxx::instance m_instance;

    mongocxx::uri m_uri;
    mongocxx::client m_client;
    mongocxx::database m_db;

    mongocxx::collection m_messages_coll;
    mongocxx::collection m_indexes_coll;

public:
	Database(std::string &&, std::string &&);

	auto insert(const std::string&&, const std::string&&);

	auto find(const std::string&&);

};


Database::Database(std::string&& uri, std::string&& db_name)
	:
	m_instance(),
	m_uri(std::forward <std::string>(uri)),
	m_client(m_uri),
	m_db(m_client[db_name]),
	m_messages_coll(m_db["messages"]),
	m_indexes_coll(m_db["indexes"])
{
	mongocxx::options::index index_options{};
	index_options.unique(true);
	m_indexes_coll.create_index(
        document{} << "token" << 1 << finalize,
        index_options
    );
}


auto Database::insert(const std::string&& title, const std::string&& content)
{
    auto mail = document{} << "title" << title
                           << "content" << content
                           << finalize;

    auto result = m_messages_coll.insert_one(std::move(mail));
    std::string mail_id = result->inserted_id().get_oid().value.to_string();

    auto tokens = Tokenizer <std::string>::tokenize_to_copy(content);
    for(auto token : tokens)
    {
        m_indexes_coll.update_one(
            document{} << "token" << std::string(token) << finalize,

            document{} << "$addToSet"
                       << open_document << "matches" << mail_id
                       << close_document
                       << finalize
        );
    }

    return std::move(tokens);
}


auto Database::find(const std::string&& keyword)
{
    auto result = m_indexes_coll.find_one(
        document{} << "token" << keyword << finalize
    );

    auto matches = bsoncxx::array::view(
        result->view()["matches"].get_array().value
    );

    std::vector <bsoncxx::stdx::optional <bsoncxx::document::value>> results;
    for(auto doc : matches) {

        const std::string mail_id {std::move(
            bsoncxx::string::to_string(
                doc.get_utf8().value
            )
        )};

        auto message = m_messages_coll.find_one(
            document{} << "_id" << bsoncxx::oid(mail_id) << finalize
        );

        results.push_back(
            message
        );
    }

    return std::move(results);
}
