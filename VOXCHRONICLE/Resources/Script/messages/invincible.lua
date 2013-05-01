require("variable_expansion")
return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  return {
  --無敵により敵の攻撃をはじいた時
    _("#{chara}は　てきの　こうげきを　はじいた"),
    _("#{chara}は　むてきだ！"),
    _("#{chara}に　てきはいない"),
    _("#{chara}は　きずつかない"),
    "むだ　むだ　むだぁ！",
    "わたしたちは　むてき",
    "まったく　もって　だいじょうぶ",
    "いたくも　かゆくも　ない",
    "あっとうてき　むてき",
    _("#{chara}は　ひらりと　みをかわした"),
    "あたらなければ　どうということは　ない",
    "てきの　こうげきが　くうを　きった",
    "こうげきなんて　ぜんぜん　へいき",
    _("#{chara}　むそうちゅう"),
    "バーリアー！へいきだもーん！！"
  }
end