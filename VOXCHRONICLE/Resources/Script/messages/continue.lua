return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  return {
  --コンティニュ―後にゲームが再開した時
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
--コンティニュ―時（全ステージ共通部分）
--各ステージ部分
--1a
--1b昼
--2a
--2b
--2c
--3a
--3b
--3c
--3d
--1b夕暮れ
--１ｂ夜
end