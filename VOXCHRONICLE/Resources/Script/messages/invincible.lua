return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  return {
  --無敵により敵の攻撃をはじいた時
    "${chara}は　てきの　こうげきを　はじいた",
    "${chara}は　むてきだ！",
    "${chara}に　てきはいない",
    "${chara}は　きずつかない",
    "むだ　むだ　むだぁ！",
    "わたしたちは　むてき",
    "まったく　もって　だいじょうぶ",
    "いたくも　かゆくも　ない",
    "あっとうてき　むてき",
    "${chara}は　ひらりと　みをかわした",
    "あたらなければ　どうということは　ない",
    "てきの　こうげきが　くうを　きった",
    "こうげきなんて　ぜんぜん　へいき",
    "${chara}　むそうちゅう",
    "バーリアー！へいきだもーん！！"
  }
end