Map = {
  name = "戦闘！ナイト",
  wayMusic = "dub",
  bossMusic = "3Bb",
  ending = "endingB",
  backgroundImage = "",
  skin = "skinA",
  nextMaps = {},
  initialLevel = 30,
  maxLevel = 30,
  getEnemyTable = function(level)
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 30 then
      knight = enemyManager:popEnemyAt("knight_boss", MAX_ROW - 1, 1)
      enemyManager:setBoss(knight)
    end
  end,
  getEnemyPopRate = function(level)
    return 1.0
  end,
  fixedEnemies = {
    {"level10", 0}
  }
}
