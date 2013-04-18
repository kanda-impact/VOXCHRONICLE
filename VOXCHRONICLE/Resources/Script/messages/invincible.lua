return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  return {
  --無敵により敵の攻撃をはじいた時
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
end