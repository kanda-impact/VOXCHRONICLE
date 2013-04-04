Map = {
  name = "戦闘！クラーケン",
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
      local kraken = enemyManager:popEnemyAt("kraken3C0", 3, 1) -- 頭
      enemyManager:setBoss(kraken)
      -- 足
      enemyManager:popEnemyAt("R_strfoot3C0", 4, 2)
      enemyManager:popEnemyAt("L_plfoot3C0", 4, 0)
      enemyManager:popEnemyAt("R_plfoot3C0", 3, 2)
      enemyManager:popEnemyAt("L_strfoot3C0", 3, 0)
      enemyManager:popEnemyAt("R_strclaw3C0", 2, 2)
      enemyManager:popEnemyAt("L_plclaw3C0", 2, 0)
      enemyManager:popEnemyAt("R_plclaw3C0", 1, 2)
      enemyManager:popEnemyAt("L_strclaw3C0", 1, 0)
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  fixedEnemies = {
  }
}
