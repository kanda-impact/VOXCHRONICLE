Enemy = {
  name = "ツテフェズ",
  imageName = "tetufez",
  attack = 1,
  baseExp = 1,
  hasFrame = false,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    local row = enemy:getRow()
    if row < 1 then
      return 0
    end
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  disableSkills = {},
  description = [[
魔物か人工魔法生物か諸説あるが分かっていない。
叩くといい音がする。
生息地：チュートリアル　攻撃力：ふつう　移動：ふつう
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
  return ""
  end
}

return Enemy