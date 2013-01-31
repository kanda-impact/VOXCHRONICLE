Map = {
  name = "ジーク面(1-B)",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 99,
  getEnemyTable = function(level)
    if level <= 5 then
      return {slime = 5, leaf = 5, typhoon = 5, geek_shield = 2, tnt = 3, ginet = 2}
    else
      return {moth = 1}
    end
  end,
  getEnemyPopRate = function(level)
    if level <= 5 then
      return 0.7
    end
    return 1.0
  end,
  fixedEnemies = {
  }
}
