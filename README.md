# ja-full-text-search

### compilation
```bash
g++ -std=c++17 `mecab-config --cflags` `mecab-config --libs` index.cpp -o index $(pkg-config --cflags --libs libmongocxx)
g++ -std=c++17 `mecab-config --cflags` `mecab-config --libs` search.cpp -o search $(pkg-config --cflags --libs libmongocxx)
```

### dependencies
```bash
dependencies
mecab
mecab-ipadic
mongocxx
mongodb (or a connection to a mongo server)
```

### test-run
```bash
./index ウィキペディア ウィキペディア（Ｗｉｋｉｐｅ ｄｉａ）は誰でも編集できるフリー百科事典です

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



./search ウィキペディア

{ "_id" : { "$oid" : "5faf8e26952df97e4379ba12" }, "title" : "ウィキペディア", "content" : "ウィキペディア（Ｗｉｋｉｐｅｄｉａ）は誰でも編集できるフリー百科事典です" }
...
```