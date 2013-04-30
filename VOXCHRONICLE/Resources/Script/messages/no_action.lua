return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  --なにもしないで3ターン経過すると流れる．．．（いらない？）
return {
    "(chara)は　ぼーっとしている",
    "(chara)は　なにもしていない",
    "(chara)！　どうした　てがとまっているぞ",
    "(chara)　かつどうていしちゅう",
    "(chara)　かんがえちゅう",
    "(chara)は　ようすをうかがっている",
  }
end