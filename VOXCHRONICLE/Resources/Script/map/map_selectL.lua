Map = {
  name = "マップセレクトテスト面L",
  wayMusic = "ttn1",
  bossMusic = "",
  ending = "",
  backgroundImage = "",
  skin = "skinB",
  nextMaps = {},
  initialLevel = 10,
  maxLevel = 99,
  getEnemyTable = function(level)
    return {shield_test = 1}
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
  end,
  getEnemyPopRate = function(level)
    return 0.8
  end,
  fixedEnemies = {
  }
}
