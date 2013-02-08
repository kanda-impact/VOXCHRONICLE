Map = {
  name = "ゆうき面(2-B)",
  wayMusic = "yuki",
  bossMusic = "",
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 99,
  getEnemyTable = function(level)
    if level <= 5 then
      return {slime = 5, leaf = 5, typhoon = 5, geek_shield = 2, tnt = 3, ginet = 2}
    else
      return {dragon = 1, acorn = 3, hornet = 3}
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
