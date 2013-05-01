return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  local skill = characterManager:getLastSkill()
  if skill then
    local skillId = skill:getIdentifier()
    if skillId == "attack" or skillId == "slash" then
      --攻撃対象がいなかった時：アタック　スラッシュ
      return {
        "しかし　だれも　いない",
        "こうげきは　むなしく　くうを　きった",
        "けんの　おとだけが　ひびきわたった",
        "オクスは　すぶりを　している",
        "からぶり　なう",
        "だが　てきは　いない",
        "おちついて！　てきは　もういないのよ",
        "てきが　こない",
        "オクス　しゅぎょうちゅう",
        "だれに　こうげき　しているのか",
        "オクスは　むだに　はりきっている",
        "オクス　やるきだけは　じゅうぶんだ",
        "てきは　まだか！",
        "オクスは　そわそわ　している"
      }
    elseif skillId == "knockback" or skillId == "bow" then
      --攻撃対象がいなかった時：ノックバック　スナイプ
      return {
        "しかし　だれも　いない",
        "こうげきは　むなしく　くうを　きった",
        "からぶり　なう",
        "だが　てきは　いない",
        "てきが　いない",
        "むだに　はりきっている",
        "やるきだけは　じゅうぶんだ",
        "てきは　まだか！",
        "こうげきたいしょうが　いなかった",
        "ざんねん！　からぶり！",
        "てきさんが　いらっしゃらない",
        "てきがいない　とは",      
      }
    elseif skillId == "magic" or skillId == "thunder" then
      return {
        "しかし　だれも　いない",
        "こうげきは　むなしく　くうを　きった",
        "まほうの　ためしうちよ",
        "からぶりしたわけじゃ　ないんだから",
        "からぶり　なう",
        "だが　てきは　いない",
        "おちつけ！　てきは　もういないぞ",
        "てき　まだー？",
        "ラスカ　れんしゅうちゅう",
        "だれに　こうげき　しているんだ？",
        "ラスカは　むだに　はりきっている",
        "やるきだけは　じゅうぶんだ　ラスカ",
        "てきがくるまで　こうげきできない",
        "ラスカは　そわそわ　している"
      }
    end
  end
  return {}
end