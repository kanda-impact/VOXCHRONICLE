math.randomseed(os.time())
Enemy = {
  name = "ラスボス第1形態",
  imageName = "flast",
  attack = 20,
  baseExp = 1,
  hasFrame = true,
  counter = 0,
  width = 256,
  height = 170.75,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  description = [[
  ラスボスだよー
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self, characterManager, enemyManager)
    math.random(100)
    local row = self:getRow()
    local key = "directAttack"
    local chargeTurn = self.__IRegister__:getRegister(key, 0)
    if self:getHP() < 50 then -- HPが50以下なら
      return "boss_change" -- 第2形態変身
    end
    if chargeTurn > 0 then -- 溜め中の時
      self.__IRegister__:setBool("isLastAttack", true) -- 前のターン攻撃したフラグ
      self:setCounter(2)
      return "charge_attack_last" -- 直接攻撃する
    elseif self.__IRegister__:getBool("isLastAttack") then -- 前のターンが攻撃してたとき
      self.__IRegister__:setBool("isLastAttack", false) -- 前のターン攻撃したフラグを下ろして
      self:setCounter(0)
      return "warp" -- 確実にワープする
    elseif row == 0 then -- 最前列にいるとき
    self:setCounter(2)
      return "charge_attack_last" -- 確実に溜め攻撃
    else -- それ以外の時
      local rand = math.random(100) -- 乱数出して
      if rand < 40 then -- 4割はワープ
        self:setCounter(0)
        return "warp"
      elseif rand < 100 then -- 6割はその他の攻撃
        local r2 = math.random(100)
        if r2 < 35 then
          self:setCounter(1)
          return "beam"
        elseif r2 < 60 then
          if self:getItem() == EnemyItemNone then
            self:setCounter(3)
            return "equip"
          end
        elseif r2 < 70 then -- 敵が1体だけなら10%で
          if enemyManager:getEnemies():count() == 1 then 
            self:setCounter(1)
            return "call_last" -- t2ファージ召喚
          end
        elseif  r2 < 90 then -- HPが半分以下なら5%で回復
          if self:getHP() < self:getMaxHP() * 0.5 then
            self:setCounter(3)
            return "cure_skill" -- 回復
          end
        elseif r2 < 95 then -- 現在MPによって
          if characterManager:getMP() > characterManager:getMaxMP() * 0.8 then
            self:setCounter(3)
            return "mp_absorb" -- MP吸収   
          end
        end
      end
    end
    self:setCounter(0)
    return "laugh" -- とにかく笑う
  end
}

return Enemy