return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  --なにもしないで3ターン経過すると流れる．．．（いらない？）
return {
    _("#{chara}は　ぼーっとしている"),
    _("#{chara}は　なにもしていない"),
    _("#{chara}！　どうした　てがとまっているぞ"),
    _("#{chara}　かつどうていしちゅう"),
    _("#{chara}　かんがえちゅう"),
    _("#{chara}は　ようすをうかがっている"),
  }
end