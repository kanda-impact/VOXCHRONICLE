return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
--開始時メッセージ関係
--ステージ開始時共通
return {
    "さあ　てきだ！",
    "モンスターが　あらわれた",
    "モンスターだ　どうする？　こまんど▼",
    "まものが　あらわれた",
    "さあ　いくわよ！！",
    "まものの　においがする．．．",
    "てきがくるぞ　きをつけろ",
  }
end