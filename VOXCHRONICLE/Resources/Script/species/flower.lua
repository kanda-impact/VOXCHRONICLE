Enemy = {
  name = "パンジーさん",
  imageName = "flower",
  attack = 2,
  baseExp = 3,
  hasFrame = true,
  counter = 3,
  getSpeed = function(enemy, characterManager)
    local row = enemy:getRow()
    local rand = math.random(3)  
    if rand == 1 then
    rand = math.random(3)
    end
    if row >= 6 then
      return 1
    elseif row <=1 then
      return rand - (3 - row)
    end
    return rand - 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {},
  description = [[
  ハミングしていないと光合成できないので、
  常にハミングしてる。最近のパンジーさん界隈ではボッサが来てる。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(enemy,self)
    local row = enemy:getRow()
    local rand = math.random(5)
    if row == 0 and rand <= 3 then
        return "direct_attack"
    end
    return ""
  end
}

return Enemy