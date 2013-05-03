math.randomseed(os.time())
Enemy = {
  name = "ヴゥゥ・マー",
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
  description = [[
深海を根城にする海の荒くれ王者。通りかかる帆船を襲い、沈没させてはコレクションして最大サイズを競う。
生息地：深海ほか　攻撃力：つよい　移動：しない
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self, characterManager, enemyManager)
    local key = "waveTurn"
    local waitTurn = 6
    local turn = self:getRegister(key, 0)
    local tension = characterManager:getTension()
    math.random(100)
    local random = math.random(100)
    local tensionTurn = self:getRegister("tensionWave", 0) -- いてつくはどうの溜めターン取得
    if tensionTurn > 0 or random <= tension * 10 then
      return "reset_tension"
    end
    -- 波はwaitTurnターン以内には出ない
    if enemyManager:getEnemies():count() < 3 and random <= 30 then
      return "revive_foot"
    end
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