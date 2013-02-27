Map = {
  name = "たわし面",
  wayMusic = "ttn1",
  bossMusic = "",
  backgroundImage = "ruin_background.png",
  skin = "skinC",
  ending = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 99,
  getEnemyTable = function(level)
    return {slime0 = 1}
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
