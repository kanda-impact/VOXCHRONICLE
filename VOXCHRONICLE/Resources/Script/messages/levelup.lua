return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  --Ｌｖアップの時
return {
    string.format("%s　レベルアップ！", chara),
    string.format("%sの　レベルが　あがった", chara),
    "けいけんちが　たまった",
    "レベルアップ　したわよ！",
    "レベルあーーっぷ",
  }

end