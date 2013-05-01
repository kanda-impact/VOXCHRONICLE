Enemy = {
  name = "リスアク・バ―",
  imageName = "fortress",
  attack = 50,
  baseExp = 0,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    local row = enemy:getRow()
    if row > 0 then
      return 1
    end
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 5
  end,
  disableSkills = {"knockback"},
  description = [[
攻防一体、退却も可能な万能要塞を！と作られた魔法生物。
しかしうっかりやさんでたびたび味方に危機をもたらし捨てられてしまった。
生息地：遺跡ほか　攻撃力：たかい　移動：おそい
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    local row = self:getRow()
    if row == 0 then
      return "direct_attack"
    end
    return ""
  end
}

return Enemy