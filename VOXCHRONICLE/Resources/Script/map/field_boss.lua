Map = {
  name = "かわずたん",
  wayMusic = "1b",
  bossMusic = "",
  backgroundImage = "field_background1.jpg",
  skin = "skinB",
  ending = "",
  nextMaps = {"2b_cave", "2c_cyber"},
  initialLevel = 10,
  maxLevel = 11,
  getEnemyTable = function(level)
    return {}
  end,
  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("kawaztan.png")
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 10 then
      local kawaztan = enemyManager:popEnemyAt("kawaztan1S0", MAX_ROW - 1, 1)
    end
  end,
  onClear = function(self, characterManager, enemyManager)
  end,
  getEnemyPopRate = function(level)
    return 0
  end,
  fixedEnemies = {
  }
}
