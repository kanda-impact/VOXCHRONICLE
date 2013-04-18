return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
--ステージクリア―時
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
--クリア時（全ステージ共通部分）
--各ステージ部分
--1a
--1b昼
--2a
--2b
--2c
--1b夕暮れ
--１ｂ夜
end