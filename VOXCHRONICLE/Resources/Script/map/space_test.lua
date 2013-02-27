-- テスト用の宇宙面です
Map = {
  name = "宇宙",
  wayMusic = "nmb",
  bossMusic = "AttaQ3-D",
  backgroundImage = "3d_background0.png",
  skin = "skinA",
  ending = "endingB",
  nextMaps = {},
  initialLevel = 21,
  maxLevel = 30,
  onLoad = function()
  end,
  getEnemyTable = function(level)
    if level <= 2 then
      return {leaf01 = 3, acorn01 = 2 }
    elseif level <= 5 then
      return {leaf01 = 3, acorn01 = 2, flower01 = 2 }
    else
      return {leaf02 = 3, acorn02 = 2, flower02 = 2, doku01 = 1}
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  fixedEnemies = {
  }
}
