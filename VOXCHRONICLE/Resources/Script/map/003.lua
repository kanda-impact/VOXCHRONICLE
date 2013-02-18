Map = {
  name = "テストステージ3",
  wayMusic = "dub",
  bossMusic = "3Bb",
  ending = "endingB",
  introCount = 0,
  backgroundImage = "",
  ending = "",
  nextMaps = {},
  initialLevel = 21,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level < 30 then
      return {mimic01 = 4, dragon01 = 3, gago01 = 2, cryst01 = 1}
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
    return 0.3
  end
}

