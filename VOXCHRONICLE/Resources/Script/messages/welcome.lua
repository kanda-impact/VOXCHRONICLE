return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
--開始時メッセージ関係
  return {
    "モンスターが　あらわれた",
    "モンスターだ　どうする？　こまんど▼",
    "ついに　まものが　あらわれた",
    string.format("%sの　ぼうけんが　いま　はじまる！", chara),
    string.format("%sは　たたかいに　おもむいた", chara),
    "やってやるぜ　おやじの　かたき！",
    "こんどこそ　まけない",
    "なんと　ボタンを　おすと　こうどうします",
    "けんをとれ　たたかいが　はじまるぞ",
  }
--ステージ開始時共通
--ステージ開始時1a
--ステージ開始時1b昼
--ステージ開始時2a
--ステージ開始時2b
--ステージ開始時2c
--ステージ開始時3a
--ステージ開始時3b
--ステージ開始時3c
--ステージ開始時3d
--ステージ開始時1b夕
--ステージ開始時1b夜
end