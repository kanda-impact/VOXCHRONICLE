Map = {
  name = "テストマップ",
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
    if level <=5 then
      return 0.6
    end
    return 0.7
  end,
  fixedEnemies = {
    {"ginet", 100},
    {"tnt", 20}
  }
}
