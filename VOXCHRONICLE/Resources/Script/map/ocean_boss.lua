Map = {
  name = "深海ボス",
  wayMusic = "negi",
  bossMusic = "Ceres78",
  backgroundImage = "ocean_background.png",
  skin = "skinA",
  ending = "endingC",
  nextMaps = {},
  initialLevel = 30,
  maxLevel = 30,
  getEnemyTable = function(level)
    return {}
  end,
  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("kraken_body.png")
    enemyManager:loadEnemyTextureAsync("R_strfoot.png")
    enemyManager:loadEnemyTextureAsync("R_plfoot.png")
    enemyManager:loadEnemyTextureAsync("R_plclaw.png")
    enemyManager:loadEnemyTextureAsync("R_strclaw.png")
    enemyManager:loadEnemyTextureAsync("L_strfoot.png")
    enemyManager:loadEnemyTextureAsync("L_plfoot.png")
    enemyManager:loadEnemyTextureAsync("L_plclaw.png")
    enemyManager:loadEnemyTextureAsync("L_strclaw.png")
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 30 then
      -- 足
      enemyManager:popEnemyAt("L_plfoot3C0", 2, 0)
      enemyManager:popEnemyAt("L_strfoot3C0", 3, 1)
      enemyManager:popEnemyAt("R_plfoot3C0", 2, 2)


    end
  end,
  onBack = function(self, characterMavager, enemyManager)
    local enemyCount = enemyManager:getEnemies():count()
    local key0 = "bossRound"
    local round = self.__IRegister__:getRegister(key0, 0)
    local rand = math.random(20)
    local key1 = "blankTurn"
    local blank = self.__IRegister__:getRegister(key1, 5)
    if blank > 0 then
      self.__IRegister__:setRegister(key1, blank -1)
    else--
      if round <= 1 and rand ==1 and enemyCount >= 2 then
        enemyManager:popEnemyAt("wave3C0", 7, 1)
      end
      if enemyCount == 0 then
        if round == 0 then
          round = self.__IRegister__:setRegister(key0, 1)

          enemyManager:popEnemyAt("L_plclaw3C0", 2, 0)
          enemyManager:popEnemyAt("R_strfoot3C0", 3, 1)
          enemyManager:popEnemyAt("R_plclaw3C0", 2, 2)
        elseif round == 1 then
          round = self.__IRegister__:setRegister(key0, 2)

          enemyManager:popEnemyAt("R_strclaw3C0", 2, 2)
          enemyManager:popEnemyAt("L_strclaw3C0", 2, 0)
          local kraken = enemyManager:popEnemyAt("kraken3C0", 3, 1) -- 頭
          enemyManager:setBoss(kraken)
        elseif round >= 2 then
          round = self.__IRegister__:setRegister(key0, 3)
        end
      end--
    end
    
    -- 実績判定周り
    local boss = enemyManager:getBoss()
    if boss then
      local key = "crakenAchieve"
      local count = enemyManager:getEnemies():count()
      local enemies = enemyManager:getEnemies()
      for i=1, enemies:count() do
        local enemy = enemies:objectAtIndex(i - 1)
        if enemy and enemy:getSpecies():getIdentifier() == 'wave' then
          count = count - 1
        end
      end
      
      self.__IRegister__:setRegister(key,count)
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    local key = "crakenAchieve"
    if self.__IRegister__:getRegister(key,0) == 1 then
      data:unlockAchievement("bossCex")
    end
    data:addDefeatedCountForEnemy("wave")
  end,
  fixedEnemies = {
  }
}
