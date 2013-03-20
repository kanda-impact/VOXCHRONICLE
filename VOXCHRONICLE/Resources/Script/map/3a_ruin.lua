Map = {
  name = "古代遺跡",
  wayMusic = "ttn1",
  bossMusic = "Hawaii",
  backgroundImage = "ruin_background.png",
  skin = "skinC",
  ending = "endingA",
  nextMaps = {},
  initialLevel = 21,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level <= 22 then
      return {mimic3A1 = 2, mask3A1 = 5}
    elseif level <= 24 then
      return {wisp3A2 = 3, typhoon3A2 = 2}
    elseif level <= 26 then
      return {mimic3A1 = 2,mask3A1 = 6,gargoyle3A0 = 2}
    elseif level <= 28 then
      return {mask3A1 = 3, wisp3A2 = 3, typhoon3A2 = 1, mimic3A1 = 1}
    elseif level < 30 then
      return {mask3A1 = 3, typhoon3A2 = 3,gargoyle3A0 = 1}
    end
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 30 then
      fortress = enemyManager:popEnemyAt("fortress3A0", MAX_ROW - 1, 1)
      enemyManager:setBoss(fortress)
    end
  end,
  getEnemyPopRate = function(level)
    if level <= 24 then
      return 0.4
    elseif level <= 26 then
      return 0.3
    elseif level <= 28 then
      return 0.4
    else
      return 0.3
    end
    return 0.6
  end,
  fixedEnemies = {
  }
}
