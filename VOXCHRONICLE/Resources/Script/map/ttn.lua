Map = {
  name = "たわし面",
  wayMusic = "ttn1",
  bossMusic = "",
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 99,
  getEnemyTable = function(level)
    if level <= 5 then
      return {acorn = 3, hornet = 3, slime = 5, leaf = 5, typhoon = 5}
    else
      return {dragon = 1, mask = 3, gargoyle = 2}
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
