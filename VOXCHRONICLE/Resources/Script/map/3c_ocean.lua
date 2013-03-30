Map = {
  name = "深海",
  wayMusic = "negi",
  bossMusic = "Ceres78",
  backgroundImage = "",
  skin = "skinA",
  ending = "endingC",
  nextMaps = {""},
  initialLevel = 21,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level <= 21 then
      return {jfish3C4 = 1, naut3C5 = 1}
    elseif level <= 22 then
      return {whale3C8 = 1, cryst3C7 = 1}
    elseif level <= 23 then
      return {whale3C8 = 1, naut3C5 = 1}
    elseif level <= 24 then
      return {jfish3C4 = 1, naut3C5 = 2}
    elseif level <= 25 then
      return {whale3C8 = 1, cryst3C7 = 3}
    elseif level <= 26 then
      return {jfish3C4 = 2, naut3C5 = 2, wave3C0 = 1}
    elseif level <= 27 then
      return {whale3C8 = 1, cryst3C7 = 1, wave3C0 = 1}
    elseif level <= 28 then
      return {jfish3C4 = 1, naut3C5 = 2, wave3C0 = 1}
    elseif level <= 29 then
      return {whale3C8 = 1, jfish3C4 = 2, cryst3C7 = 3, wave3C0 = 2}
    elseif level == 30 then
      return {}
    end
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
    return 0.25
  end,
  fixedEnemies = {
  }
}
