Map = {
  name = "森林",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "",
  skin = "skinB",
  ending = "",
  nextMaps = {"3a_ruin","3b_castle"},
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
