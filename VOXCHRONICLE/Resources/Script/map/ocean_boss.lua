Map = {
  name = "戦闘！クラーケン",
  wayMusic = "dub",
  bossMusic = "Ceres78",
  backgroundImage = "",
  skin = "skinA",
  ending = "endingC",
  nextMaps = {},
  initialLevel = 30,
  maxLevel = 30,
  getEnemyTable = function(level)
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 30 then
      local kraken = enemyManager:popEnemyAt("kraken3C0", 4, 1) -- 頭
      enemyManager:setBoss(kraken)
      -- 足
      enemyManager:popEnemyAt("clawfoot3C2", 5, 0)
      enemyManager:popEnemyAt("clawfoot3C1", 5, 1)
      enemyManager:popEnemyAt("clawfoot3C2", 5, 2)
      enemyManager:popEnemyAt("clawfoot3C1", 4, 0)
      enemyManager:popEnemyAt("clawfoot3C2", 4, 2)
      enemyManager:popEnemyAt("clawfoot3C0", 3, 0)
      enemyManager:popEnemyAt("clawfoot3C0", 3, 2)
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  fixedEnemies = {
  }
}
