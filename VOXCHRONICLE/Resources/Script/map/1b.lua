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
      return {slime0 = 5}
    else
      return {slime0 = 1}
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
