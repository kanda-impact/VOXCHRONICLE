return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  --Ｌｖアップの時
return {
    "${chara}　レベルアップ！",
    "${chara}の　レベルが　あがった",
    "けいけんちが　たまった",
    "レベルアップ　したわよ！",
    "レベルあーーっぷ",
  }

end