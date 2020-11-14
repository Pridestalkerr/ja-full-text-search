// $ g++ `mecab-config --cflags` `mecab-config --libs` -Os mecab.cpp

#include <string>
#include <string_view>
#include <vector>
#include <mecab.h>



template <typename String_T = std::string>
class Tokenizer
{
    
    using Char_T = typename String_T::value_type;
    using View_T = typename std::basic_string_view <Char_T>;

public:

    Tokenizer() = default;

    static constexpr std::vector <View_T> tokenize_to_view(const String_T&);
    static constexpr std::vector <String_T> tokenize_to_copy(const String_T&);
};


template <typename String_T>
constexpr std::vector <typename Tokenizer <String_T>::View_T>
Tokenizer <String_T>::tokenize_to_view(const String_T& value)
{
    std::vector <View_T> views;

    const MeCab::Node* node = MeCab::createTagger("")->parseToNode(value.c_str());
    for(; node; node = node->next)
    {
        switch(node->stat)
        {
            case MECAB_BOS_NODE:
            case MECAB_EOS_NODE:
                continue;
            default:
                views.push_back(View_T(node->surface, node->length));
        }
    }

    return std::move(views);
}

template <typename String_T>
constexpr std::vector <String_T>
Tokenizer <String_T>::tokenize_to_copy(const String_T& value)
{
    std::vector <String_T> views;

    const MeCab::Node* node = MeCab::createTagger("")->parseToNode(value.c_str());
    for(; node; node = node->next)
    {
        switch(node->stat)
        {
            case MECAB_BOS_NODE:
            case MECAB_EOS_NODE:
                continue;
            default:
                views.push_back(String_T(node->surface, node->length));
        }
    }

    return std::move(views);
}