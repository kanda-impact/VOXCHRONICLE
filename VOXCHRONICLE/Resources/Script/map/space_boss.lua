Map = {
  name = "戦闘！ラスボス",
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
    enemyManager:loadEnemyTextureAsync("flast.png")
    enemyManager:loadEnemyTextureAsync("2last.png")
    enemyManager:loadEnemyTextureAsync("bit.png")
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 30 then
      local boss = enemyManager:popEnemyAt("last1_boss", 3, 1)
      enemyManager:setBoss(boss)
    end
  end,
  getEnemyPopRate = function(level)
    return 0
  end,
  fixedEnemies = {
  }
}
