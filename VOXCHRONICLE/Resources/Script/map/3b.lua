Map = {
  name = "てつ面(3-B)",
  wayMusic = "dub",
  bossMusic = "3Bb",
  backgroundImage = "",
  nextMaps = {"2a"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level < 10 then
      return {slime0 = 1}
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
    if level <=5 then
      return 0.5
    end
    return 0.7
  end,
  fixedEnemies = {
    {"level10", 0}
  }
}
