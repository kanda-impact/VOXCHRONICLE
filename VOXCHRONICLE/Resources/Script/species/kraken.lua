math.randomseed(os.time())
Enemy = {
  name = "クラーケン",
  imageName = "kraken_body",
  attack = 1,
  baseExp = 3,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  animationFrames = 4,
  performSkill = function(self)
    local key = "waveTurn"
    local waitTurn = 6
    local turn = self:getRegister(key, 0)
    math.random(100)
    local random = math.random(100)
    -- 波はwaitTurnターン以内には出ない
    if random <= 30 and turn == 0 then
      self:setRegister(key, 1)
      return "wave_skill"
    end
    
    if turn > 0 then
      if turn + 1 > waitTurn then
        self:setRegister(key, 0)
      else
        self:setRegister(key, turn + 1)
      end
    end
    return ""
  end
}

return Enemy