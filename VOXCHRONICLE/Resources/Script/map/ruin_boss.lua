Map = {
  name = "戦闘！砦",
  wayMusic = "ttn1",
  bossMusic = "Hawaii",
  backgroundImage = "ruin_background.png",
  skin = "skinC",
  ending = "endingA",
  nextMaps = {},
  initialLevel = 10,
  maxLevel = 10,
  getEnemyTable = function(level)
    return {}
  end,
  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("fortress.png")
  end,
  onBack = function(self, characterManager, enemyManager)
    local key = "fortressAchieve"
    local boss = enemyManager:getBoss()
    if boss then
      local bossRow = enemyManager:getBoss():getRow()
      self.__IRegister__:setRegister(key,bossRow)
      print(bossRow)
    end
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 10 then
      fortress = enemyManager:popEnemyAt("fortress3A0", MAX_ROW - 1, 1)
      enemyManager:setBoss(fortress)
    end
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    data:unlockAchievement("clear3A")
    local key = "fortressAchieve"
    local row = self.__IRegister__:getRegister(key,1)
    if row == 0 then
      data:unlockAchievement("nagoya")
    end
  end,
  getEnemyPopRate = function(level)
    if level <= 22 then
      return 0.3
    elseif level <= 29 then
      return 0.2
    else
      return 0.3
    end
    return 0.6
  end,
  fixedEnemies = {
  }
}
