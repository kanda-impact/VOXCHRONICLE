Map = {
  name = "草原",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "",
  skin = "skinB",
  ending = "",
  nextMaps = {"2b_cave","2c_cyber"},
  initialLevel = 1,
  maxLevel = 10,
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
    --{"level10",0}
  }
}
