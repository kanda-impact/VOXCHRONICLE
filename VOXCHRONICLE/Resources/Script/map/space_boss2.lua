Map = {
  name = "宙域ボス２",
  wayMusic = "nmb",
  bossMusic = "AttaQ3-D",
  backgroundImage = "3d_background0.png",
  skin = "skinA",
  ending = "endingD",
  nextMaps = {},
  initialLevel = 30,
  maxLevel = 30,
  getEnemyTable = function(level)
    return {}
  end,
  onLoad = function(self, characterManager, enemyManager)
    --enemyManager:loadEnemyTextureAsync("flast.png")
    enemyManager:loadEnemyTextureAsync("2last.png")
    enemyManager:loadEnemyTextureAsync("bit.png")
  end,
  onBack = function(self, characterManager, enemyManager)
    local enemies = enemyManager:getEnemies()
    local enemyCount = enemies:count()
    local level = characterManager:getLevel()
    if level == 30 then
      local boss = enemyManager:getBoss()
      if boss then
        local bossHP = boss:getHP()
        local key = "lastBossAchieve"
        local count = enemyManager:getEnemies():count()
        if bossHP > 0 then
          self.__IRegister__:setRegister(key,count)
        elseif bossHP <= 0 and self.__IRegister__:getRegister(key,count) ==3 then
          self.__IRegister__:setRegister(key,100)
        end
      end
    end
  end,

  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 30 then
      local boss = enemyManager:popEnemyAt("last2_boss", 1, 1)
      enemyManager:setBoss(boss)
      local bitL = enemyManager:popEnemyAt("L_bit_boss", 1, 0)
      local bitR = enemyManager:popEnemyAt("R_bit_boss", 1, 2)
    end
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    local key = "lastBossAchieve"
    local achieveCount = self.__IRegister__:getRegister(key, 0)
    if achieveCount >= 100 then
      data:unlockAchievement("bossDex")
    end
  end,

  getEnemyPopRate = function(level)
    return 0
  end,
  fixedEnemies = {
  }
}
