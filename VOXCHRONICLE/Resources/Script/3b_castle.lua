Map = {
  name = "城",
  wayMusic = "",
  bossMusic = "",
  backgroundImage = "",
  skin = "skinC",
  ending = "",
  nextMaps = {""},
  initialLevel = 21,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level <= 2 then
      return {mimic3B0 = 3, gargoyle3B0 = 2,slime3B0 = 2 }
    elseif level <= 5 then
      return {}
    else
      return {}
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  fixedEnemies = {
  }
}
