Map = {
  name = "深海",
  wayMusic = "dub",
  bossMusic = "Ceres78",
  backgroundImage = "",
  skin = "skinA",
  ending = "endingC",
  nextMaps = {""},
  initialLevel = 21,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level < 30 then
      return {whale3C0 = 3, jfish3C0 = 2, naut3C0 = 1}
    elseif level == 30 then
      return {}
    end
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 30 then
      local kraken = enemyManager:popEnemyAt("kraken3C0", 4, 1) -- 頭
      enemyManager:setBoss(kraken)
      -- 足
      enemyManager:popEnemyAt("R_plfoot3C0", 5, 2)
      enemyManager:popEnemyAt("L_plfoot3C0", 5, 0)
      enemyManager:popEnemyAt("R_plfoot3C0", 4, 2)
      enemyManager:popEnemyAt("L_plfoot3C0", 4, 0)
      enemyManager:popEnemyAt("R_strclaw3C0", 3, 2)
      enemyManager:popEnemyAt("L_strclaw3C0", 3, 0)
      enemyManager:popEnemyAt("R_strclaw3C0", 2, 2)
      enemyManager:popEnemyAt("L_strclaw3C0", 2, 0)
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  fixedEnemies = {
  }
}
