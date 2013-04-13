Enemy = {
  name = "かわずたん",
  imageName = "kawaztan",
  attack = 3,
  baseExp = 6,
  hasFrame = true,
  counter = 2,
  getSpeed = function(enemy, characterManager)
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 2
  end,
  description = [[
    みんなのアイドルかわずたんが黒魔法と光剣術を習得して参戦したぞ！
    『まとめてのしイカにしてやるケロ～☆』
  ]],
  habitat = "草原",
  disableSkills = {},
  animationFrames = 4,
  performSkill = function(self, characterManager, enemyManager)
    math.random(100)
    local row = self:getRow()
    local key = "skillCharge"
     --[[ user:setAnimationClip("attack", 1, true) -- グラを変更する
      user:setRegister(key, turn + 1)
    ]] --  MessageManager:sharedManager():pushMessage(user:getName().."は　ちからを　ためている")
      -- 溜め初回ターンの時
    local chargeTurn = self.__IRegister__:getRegister(key, 0)
    if chargeTurn > 0 then -- 溜め中の時
      self.__IRegister__:setBool("isLastAttack", true) -- 前のターン攻撃したフラグ
      self:setCounter(2)
      return "charge_attack_kawaz" -- 直接攻撃する
    elseif self.__IRegister__:getBool("isLastAttack") then -- 前のターンが攻撃してたとき
      self.__IRegister__:setBool("isLastAttack", false) -- 前のターン攻撃したフラグを下ろして
      self:setCounter(0)
      return "" -- 何もしない
    else -- それ以外の時
      local rand = math.random(100) -- 乱数出して
      if rand < 30 then -- 3割は何もしない
        self:setCounter(0)
        return ""
      elseif rand < 100 then -- 7割はその他の攻撃
        local r2 = math.random(100)
        if r2 < 35 then
          self:setCounter(1)
          return "kawaz_beam"
        elseif r2 < 50 then
          return "charge_attack_kawaz"
        elseif r2 > 90 then
          if self:getItem() == EnemyItemNone then
            self:setCounter(3)
            return "equip"
          end
        elseif  r2 > 80 then -- HPが7割以下なら10%で回復
          if self:getHP() < self:getMaxHP() * 0.7 then
            self:setCounter(3)
            return "cure_skill" -- 回復
          end
        elseif r2 > 70 then -- 現在MPによって
          if characterManager:getMP() > characterManager:getMaxMP() * 0.5 then
            self:setCounter(3)
            return "mp_absorb" -- MP吸収   
          end
        end
        return ""
      end
    end
    self:setCounter(0)
    return "kawaz_laugh" -- とにかく笑う
  end
}

return Enemy