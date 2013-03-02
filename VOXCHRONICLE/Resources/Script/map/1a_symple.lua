Map = {
  name = "シンプル",
  wayMusic = "",
  bossMusic = "",
  backgroundImage = "",
  skin = "skinA",
  ending = "",
  nextMaps = {"2a_forest","2b_cave"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <= 2 then
      return {leaf01 = 3, acorn01 = 2 }
    elseif level <= 5 then
      return {leaf01 = 3, acorn01 = 2, flower01 = 2 }
    else
      return {acorn02 = 2, flower02 = 2, doku01 = 1}
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  fixedEnemies = {
  }
}
