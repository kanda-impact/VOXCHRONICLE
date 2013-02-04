Map = {
  name = "ちゃぼ面(2-A)",
  wayMusic = "nmb",
  bossMusic = "",
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 99,
  getEnemyTable = function(level)
    return {slime = 5, leaf = 5, typhoon = 5, toadstool = 2, dragon = 3, tnt = 3, ginet = 2, moth = 1}
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
