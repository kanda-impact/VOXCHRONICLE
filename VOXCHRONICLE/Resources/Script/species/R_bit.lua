math.randomseed(os.time())
Enemy = {
  name = "右ティアムー",
  imageName = "bit",
  attack = 100,
  baseExp = 1,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    return 0
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  description = [[
ワート・モショウが呼び出したしもべ。
ワート・モショウの作り出す不規則な音を拾い、増幅させる。
いつかラスボスになれる日を夢見て職務を全うしている、ただの中間管理職。
生息地：宙域　攻撃力：ふつう　移動：しない
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self, characterManager, enemyManager)
    math.random(100)
    --[[local row = self:getRow()
    local col = self:getCol()
    if row == 1 and col == 2 then
    self:setRow(0)
    self:setCol(1)
    elseif row == 0 and col == 1 then
    self:setRow(1)
    self:setCol(0)
    elseif row == 1 and col == 0 then
    self:setRow(2)
    self:setCol(1)
    elseif row == 2 and col == 1 then
    self:setRow(1)
    self:setCol(2)
    end]]
    local reviveTurn = self:getRegister("reviveTurn", 0)
    if reviveTurn > 0 then
      return "revive"
    end
    local r = math.random(100)
    local blankTurn = self:getRegister("blank", 0)
    if blankTurn >= 20 then -- 20ターンは確実に待つ
      if enemyManager:getEnemies():count() < 3 and r < 10 then -- 誰か死んでるかつ10%
        local leftBitDead = true
        for i=0, enemyManager:getEnemies():count() - 1 do
          local enemy = enemyManager:getEnemies():objectAtIndex(i)
          enemy = tolua.cast(enemy, "Enemy")
          if enemy and enemy:getIdentifier() == "L_bit_boss" then
            leftBitDead = false
            break
          end
        end
        if leftBitDead then
          self:setRegister("blank",0)
          --self:getRegister("reviveSkillCount",reviveSkillCount +2)
          return "revive" -- 蘇生呪文
        end
      end
    else
      self:setRegister("blank",blankTurn + 1)
    end
    -- ベホマラー
    local boss = enemyManager:getBoss()
    if boss then
      if boss:getHP() < boss:getMaxHP() * 0.6 and r < 4 then -- ボスのHP6割以下、かつ5%
        return "cure_all_skill"
      end
    end
    if r < 2 then -- 2%でレーザー
      return "beam"
    elseif r < 18 then -- 属性変化
      return "typeChange_last"
    end
    return ""
  end
}

return Enemy
