Map = {
  name = "テストマップ１",
  wayMusic = "dub",
  bossMusic = "boss",
  backgroundImage = "",
  skin = "skinA",
  nextMaps = {},
  ending = "endingB",
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <= 1 then
      return {tut_slime1 = 1}
    elseif level <= 2 then
      return {tut_slime0 = 1}
    else
      if level % 2 == 1 then
        return {tut_slime0 = 1}
      else
        return {tut_slime1 = 1}
      end
    end
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 10 then
      knight = enemyManager:popEnemyAt("knight_boss", MAX_ROW - 1, 1)
      enemyManager:setBoss(knight)
    end
  end,
  getEnemyPopRate = function(level)
    if level <= 1 then
      return 0.3
    elseif level <= 2 then
      return 0.8
    elseif level <= 3 then 
      return 0.7
    elseif level <= 4 then 
      return 0.3
    elseif level <= 5 then
      return 0.4
    elseif level <= 6 then
      return 0.3
    elseif level <= 7 then
      return 1
    elseif level <= 8 then
      return 0.3
    elseif level <= 9 then 
      return 1
    elseif level <= 10 then
     return 0.3
    end
    return 0.7
  end,
  fixedEnemies = {
    {"tut_flower", 240}
  }
}
