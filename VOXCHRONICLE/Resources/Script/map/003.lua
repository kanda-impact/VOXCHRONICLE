Map = {
  name = "テストステージ3",
  wayMusic = "dub",
  bossMusic = "boss",
  introCount = 0,
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 20,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level < 30 then
      return {mimic01 = 4, dragon01 = 3, gago01 = 2, cryst01 = 1}
    end
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 10 then
      knight = enemyManager:popEnemyAt("knight_boss", MAX_ROW - 1, 1)
      enemyManager:setBoss(knight)
    end
  end,
    return {}
  end,
  getEnemyPopRate = function(level)
    if level <= 15 then
      return 0.6
    end
    return 0.6
  end
}

