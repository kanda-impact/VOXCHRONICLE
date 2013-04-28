Map = {
  name = "深海",
  wayMusic = "negi",
  bossMusic = "Ceres78",
  backgroundImage = "ocean_background.png",
  thumbnailImage = "ocean_thumbnail.png",
  skin = "skinA",
  ending = "endingC",
  nextMaps = {""},
  initialLevel = 29,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level <= 21 then
      return {jfish3C4 = 1, naut3C5 = 1}
    elseif level <= 22 then
      return {whale3C0 = 1, cryst3C4 = 1}
    elseif level <= 23 then
      return {whale3C0 = 1, naut3C5 = 1}
    elseif level <= 24 then
      return {jfish3C4 = 1, naut3C5 = 2}
    elseif level <= 25 then
      return {whale3C0 = 1, cryst3C4 = 3}
    elseif level <= 26 then
      return {jfish3C4 = 2, naut3C5 = 2,}
    elseif level <= 27 then
      return {whale3C0 = 1, cryst3C4 = 1}
    elseif level <= 28 then
      return {jfish3C4 = 1, naut3C5 = 2}
    elseif level <= 29 then
      return {whale3C0 = 1, naut3C5 = 2, cryst3C4 = 3}
    elseif level == 30 then
      return {}
    end
  end,
[[  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("naut.png")
    enemyManager:loadEnemyTextureAsync("jfish.png")
    enemyManager:loadEnemyTextureAsync("cryst.png")
    enemyManager:loadEnemyTextureAsync("whale.png")
    SaveData:sharedData():setClearedForMap("fp_ocean")
    end,
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 29 then
    enemyManager:loadEnemyTextureAsync("kraken_body.png")
    enemyManager:loadEnemyTextureAsync("R_strfoot.png")
    enemyManager:loadEnemyTextureAsync("R_plfoot.png")
    enemyManager:loadEnemyTextureAsync("R_plclaw.png")
    enemyManager:loadEnemyTextureAsync("R_strclaw.png")
    enemyManager:loadEnemyTextureAsync("L_strfoot.png")
    enemyManager:loadEnemyTextureAsync("L_plfoot.png")
    enemyManager:loadEnemyTextureAsync("L_plclaw.png")
    enemyManager:loadEnemyTextureAsync("L_strclaw.png")

    elseif level == 30 then
      CCTextureCache:sharedTextureCache():removeTextureForKey("naut.png")
      CCTextureCache:sharedTextureCache():removeTextureForKey("whale.png")
      CCTextureCache:sharedTextureCache():removeTextureForKey("jfish.png")
      
      enemyManager:popEnemyAt("L_plfoot3C0", 2, 0)
      enemyManager:popEnemyAt("L_strfoot3C0", 3, 1)
      enemyManager:popEnemyAt("R_plfoot3C0", 2, 2)
      SaveData:sharedData():setClearedForMap("fp_ocean_boss")
    end
  end,]]
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
  end,
  
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    data:unlockAchievement("clear3C")
    SaveData:sharedData():addDefeatedCountForEmemy("wave3C0")
  end,

  getEnemyPopRate = function(level)
    return 0.16
  end,
  fixedEnemies = {
  {"wave3C1",1720}

  }
}
