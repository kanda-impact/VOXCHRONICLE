require("variable_expansion")
return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  --Ｌｖアップの時
return {
    _("#{chara}　レベルアップ！"),
    _("#{chara}の　レベルが　あがった"),
    "けいけんちが　たまった",
    "レベルアップ　したわよ！",
    "レベルあーーっぷ",
  }

end