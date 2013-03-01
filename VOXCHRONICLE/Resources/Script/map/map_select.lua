Map = {
  name = "マップセレクトテスト面",
  wayMusic = "volca",
  bossMusic = "",
  ending = "",
  backgroundImage = "",
  skin = "skinA",
  nextMaps = {"map_selectL", "map_selectR"}, -- マップセレクトのテスト面です。左右のどっちかに飛びます
  initialLevel = 9,
  maxLevel = 10,
  getEnemyTable = function(level)
    return {leaf02 = 3, acorn02 = 2, flower02 = 2, doku01 = 1}
  end,
  onLevel = function(level, characterManager, enemyManager)
  end,
  getEnemyPopRate = function(level)
    return 1.0
  end,
  fixedEnemies = {
    {"level10", 0}
  }
}
