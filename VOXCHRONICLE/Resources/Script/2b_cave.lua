Map = {
  name = "炭鉱",
  wayMusic = "yuki",
  bossMusic = "",
  backgroundImage = "",
  skin = "skinA",
  ending = "",
  nextMaps = {"3b_castle","3c_ocean"},
  initialLevel = 11,
  maxLevel = 20,
  getEnemyTable = function(level)
  return {slime0 = 1}
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
