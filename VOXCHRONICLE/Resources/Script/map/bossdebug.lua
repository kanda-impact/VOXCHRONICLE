Map = {
  name = "古城ボス",
  wayMusic = "dub",
  bossMusic = "3Bb",
  ending = "endingB",
  backgroundImage = "castle_background.png",
  skin = "skinC",
  nextMaps = {},
  initialLevel = 30,
  maxLevel = 30,
  getEnemyTable = function(level)
    return {}
  end,
  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("knight.png")
  end,
  onBack = function(self, characterManager, enemyManager)
    local key = "knightAchieve"
    local boss = enemyManager:getBoss()
    if boss then
      local bossAttack = enemyManager:getBoss():getRegister("swordTurn",0)
      self.__IRegister__:setRegister(key,bossAttack)
    end
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 30 then
      knight = enemyManager:popEnemyAt("knight_boss", MAX_ROW - 1, 1)
      enemyManager:setBoss(knight)
    end
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    data:unlockAchievement("clear3B")
    local key = "knightAchieve"
    local bossAttack = self.__IRegister__:getRegister(key,0)
    if bossAttack > 0 then
      data:unlockAchievement("bossBex")
    end
  end,

  getEnemyPopRate = function(level)
    return 1.0
  end,
  fixedEnemies = {
  }
}
