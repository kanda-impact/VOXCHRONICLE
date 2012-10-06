# マップスクリプト

## 免責事項
スクリプトの仕様は予告なく変更になる可能性があります。わかんなかったら聞いてください

## 概要
各ステージのパラメータが記述できます

## サンプル
```lua
Map = {
  name = "テストマップ",
  prefix = "dub",
  backgroundImage = "",
  nextMaps = {"test", "test"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    enemies = {}
    if true then
      enemies = {tnt = 30}
    end
    return enemies
  end,
  getEnemyPopRate = function(level)
    return 0.4
  end
}
```

## 各パラメーターの意味
### name
ステージの名前を指定してください。ステージ選択画面やメッセージ表示上で使用されるかもしれません

### prefix
そのステージに使う音楽ファイルの接頭辞を指定してください。存在しないモノを指定すると落ちる気がします

### nextMaps
次のステージに進むとき、隣接するマップの識別子を書いてください。識別子とはファイル名から.luaを抜いたモノです。

空のテーブルを指定した場合はこのステージが最終面になります。

要素が一つだけのテーブルを指定した場合は、ステージクリア後、強制的にそのマップへ移動します

要素が2つ以上の時、1つめのステージが左、2つめのステージが右として選択肢に出てきて分岐します。3つ目以上は無視されます。

### initialLevel
そのステージの初期レベルを設定してください。

ステージに入ったときに強制的にそのレベルに変更されます。

最初のステージは1から始めるべきです。

### maxLevel
そのステージの最終レベルを設定してください。

そのレベルから次のレベルに上がったとき、nextMapsへ移行します

### getEnemyTable

現在のレベルを引数として受け取って、モンスター名をkey, 出現率をvalueにしたテーブルを返してください。

これによって、このステージにおいて指定したレベルのモンスター出現テーブルを実装できます。


例えば以下のような関数を実装した場合を考えます。

```lua
getEnemyTable = function(level)
    enemies = {}
    if level <=3 then
      return {monster0 = 1}
    elseif level <= 7 then
      return {monster0 = 2, monster1 = 3} 
    else
      return {monster0 = 1, monster1 = 4, monster2 = 5}
    end
    return enemies
  end,
```

このとき、レベル3以下の時はmonster0のみが

4以上7以下の時はmonster0が 2 / (2 + 3)で40%、monster1が 3 / (2 + 3)で60%

レベル8以上の時はmonster0が 1 / (1 + 4 + 5)で10%、以下同様に40%, 50%の確率で出現します。

出現率については、互いに疎になるように指定した方が良いです。余り大きい数を書くと動作に影響を与える恐れがあります。

× monster0 = 100, monster1 = 200, monster2 = 300

○ monster0 = 1, monster1 = 2, monster2 = 3



### getEnemyPopRate

現在のレベルを引数として受け取って、モンスター全体の出現率を0~1の値で返してください。

小数点以下3ケタ以降は無視されます。


```lua
getEnemyPopRate = function(level)
  return 0.4
end
```

例えば上記のように実装した場合、レベルにかかわらず10小節に4回の割合で何らかのモンスターが出現します。


レベルによって変えたい場合はifとか使って上手い具合にやってください
