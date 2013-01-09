Map = {
  name = "ジーク面(1-B)",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 11,
  maxLevel = 99,
  getEnemyTable = function(level)
    return {slime = 5, leaf = 5, typhoon = 5, geek_shield = 2, tnt = 3, ginet = 2}
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
