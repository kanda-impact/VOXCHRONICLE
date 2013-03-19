Map = {
  name = "戦闘！ナイト",
  wayMusic = "dub",
  bossMusic = "3Bb",
  ending = "endingB",
  backgroundImage = "castle_background.png",
  skin = "skinC",
  nextMaps = {},
  initialLevel = 30,
  maxLevel = 30,
  getEnemyTable = function(level)
    return {}
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 30 then
      knight = enemyManager:popEnemyAt("knight_boss", MAX_ROW - 1, 1)
      enemyManager:setBoss(knight)
    end
  end,
  getEnemyPopRate = function(level)
    return 1.0
  end,
  fixedEnemies = {
  }
}
