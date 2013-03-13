Map = {
  name = "古代遺跡",
  wayMusic = "ttn1",
  bossMusic = "Hawaii",
  backgroundImage = "ruin_background.png",
  skin = "skinC",
  ending = "endingA",
  nextMaps = {},
  initialLevel = 29,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level <= 22 then
      return {mask3A3 = 3, wisp3A0 = 1 ,gargoyle3A0 = 1}
    elseif level <= 23 then
      return {typhoon3A6 = 3,gargoyle3A0 = 1}
    elseif level <= 25 then
      return {mask3A3 = 2, wisp3A6 = 1, typhoon3A6 = 1}
    elseif level <= 27 then
      return {mask3A3 = 1, typhoon3A6 = 1}
    elseif level < 30 then
      return { wisp3A6 = 2, typhoon3A6 = 1,gargoyle3A0 = 1}
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
