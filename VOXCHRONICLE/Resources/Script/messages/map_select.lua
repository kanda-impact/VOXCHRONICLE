return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  return {
  --ステージセレクト時
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
--ステージセレクトで何もせず一定時間経過した時(作れそうであれば)
end