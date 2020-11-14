# ja-full-text-search


### dependencies (all latest)
```bash
mecab, mecab-ipadic, mongocxx, mongodb (or a connection to a mongo server)
```

### compilation
```bash
make install
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