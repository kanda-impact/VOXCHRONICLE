return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  --敵のバリアーにこうげきが防がれる
return {
    "わたしの　こうげきが　きかない！？",
    "まほうが　きかないみたい！",
    "まほうが　ふせがれてしまった",
    "ひかりのかべに　こうげきが　すいこまれた",
    "けんで　こうげきしないと　だめね",
    "オクス！　けんで　こわして　もらえる？",
    "バリア！？　けんで　こわさないと　だめね！",
  }
end