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
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 30 then
      local boss = enemyManager:popEnemyAt("last2_boss", 1, 1)
      enemyManager:setBoss(boss)
      local bitL = enemyManager:popEnemyAt("L_bit_boss", 1, 0)
      local bitR = enemyManager:popEnemyAt("R_bit_boss", 1, 2)
    end
  end,
  getEnemyPopRate = function(level)
    return 0
  end,
  fixedEnemies = {
  }
}
