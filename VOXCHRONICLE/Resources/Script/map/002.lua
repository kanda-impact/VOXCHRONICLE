Map = {
  name = "テストステージ２",
  wayMusic = "ttn1",
  bossMusic = "",
  backgroundImage = "",
  skin = "skinB",
  ending = "",
  nextMaps = {"003"},
  initialLevel = 11,
  maxLevel = 20,
  getEnemyTable = function(level)
    if level <= 15 then
      return {slime01 = 3, bat01 = 2, hornet01 = 1 }
    else
      return {slime02 = 3, bat02 = 2, hornet02 = 2, moth01 = 1}
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  fixedEnemies = {
  }
}
