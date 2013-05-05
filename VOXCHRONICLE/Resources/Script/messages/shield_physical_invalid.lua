return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  --敵のシールドにこうげきが防がれる
return {
    "こうげきが　ふせがれてしまった",
    "けんがきかない　．．．だと！？",
    "けんが　はじかれてしまった",
    "まほうで　はじきとばしてもらうか",
    "まほうじゃないと　だめそうだな",
    "ラスカ　こいつを　なんとか　してくれ",
  }
end