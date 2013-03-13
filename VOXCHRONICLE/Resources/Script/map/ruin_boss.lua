Map = {
  name = "戦闘！砦",
  wayMusic = "ttn1",
  bossMusic = "Hawaii",
  backgroundImage = "ruin_background.png",
  skin = "skinC",
  ending = "endingA",
  nextMaps = {},
  initialLevel = 30,
  maxLevel = 30,
  getEnemyTable = function(level)
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 30 then
      fortress = enemyManager:popEnemyAt("fortress3A0", MAX_ROW - 1, 1)
      enemyManager:setBoss(fortress)
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
