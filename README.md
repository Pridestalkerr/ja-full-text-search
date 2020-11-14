# ja-full-text-search

Japanese language tokenization and indexing for full-text searching. 

### dependencies (all latest)
gcc (or any c++17 compiler), mecab, mecab-ipadic, mongocxx, mongodb (or a connection to a mongo server)

### compilation
```bash
$ make install
```

### instructions
You can insert a document (title, content) by using the ./index binary created by Make
```bash
$ ./index title content
```

You can search for a token by using the ./search binary.
```bash
$ ./search token
```

### test-run
```bash
$ ./index ウィキペディア ウィキペディア（Ｗｉｋｉｐｅ ｄｉａ）は誰でも編集できるフリー百科事典です

ウィキペディア
（
Ｗｉｋｉｐｅｄｉａ
）
は
誰
でも
編集
できる
フリー
百科
事典
です


$ ./search ウィキペディア

{ "_id" : { "$oid" : "5faf8e26952df97e4379ba12" }, "title" : "ウィキペディア", "content" : "ウィキペディア（Ｗｉｋｉｐｅｄｉａ）は誰でも編集できるフリー百科事典です" }
...
```

### about
Compared to most other languages, Japanese text indexing is an inherently more difficult task.\
Thankfully, many peoples contribution made it so that today we have a fair amount of tools at our disposal.
Perhaps the most famous tool for Japanese tokenization is MeCab, a C++ library. Although most documentation is in Japanese, after some digging we can figure out how to make use of it.\
This small application provides just that, an example of how to use MeCab to tokenize Japanese text, and inverse-indexing it in a database, mongoDB in our case.\
Disclaimer: Other options exist, such as SOLR as full-text searching database and kuromoji's analyzer, both of which are incredibly easy to get set up, as long as you're fine with messing around with some Java.
