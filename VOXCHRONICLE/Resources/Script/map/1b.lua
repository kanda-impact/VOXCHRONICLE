Map = {
  name = "ジーク面(1-A)",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "simple_background.png",
  skin = "skinA",
  ending = "",
  nextMaps = {"2a"},
  initialLevel = 1,
  maxLevel = 2,
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
