Enemy = {
  name = "ファージー",
  imageName = "t2pha",
  attack = 1,
  baseExp = 6,
  hasFrame = true,
  counter = 1,
  getSpeed = function(enemy, characterManager)
    local row = enemy:getRow()
    if row == 1 then
      return 1
    elseif row == 0 then
      return 0
    end
    return 2
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {},
  description = [[
生物と無生物の間で揺れる構造体。生物に対して無類の強さだが、電子生命に負ける。電子生命にはやる気がないので実質敵なし。
生息地：宙域　攻撃力：よわい　移動：はやい
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