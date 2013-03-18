Map = {
  name = "テストステージ3",
  wayMusic = "dub",
  bossMusic = "3Bb",
  ending = "endingB",
  skin = "skinC",
  introCount = 0,
  backgroundImage = "castle_background.png",
  nextMaps = {},
  initialLevel = 21,
  maxLevel = 30,
  getEnemyTable = function(level)
      if level <= 22 then
       return {mimic01 = 2, dragon01 = 1}
      elseif level <= 24 then
       return {mimic01 = 2, gago01 = 1, cryst01 = 2}
      elseif level <= 25 then
       return {gago01 = 3, cryst01 = 2}
      elseif level <= 27 then
       return {mimic01 = 2, dragon01 = 1, gago01 = 2}
      elseif level <= 28 then
       return {mimic01 = 1, dragon01 = 2, gago01 = 2}
      elseif level <= 29 then
       return {dragon01 = 2, gago01 = 1, cryst01 = 2}
      end
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 30 then
      knight = enemyManager:popEnemyAt("knight_boss", MAX_ROW - 1, 1)
      enemyManager:setBoss(knight)
    end
  end,
  getEnemyPopRate = function(level)
    if level < 25 then
      return 0.3
    else 
      return 0.4
    end
  end
}

