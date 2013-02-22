Map = {
  name = "AttaQ面",
  wayMusic = "AttaQ3-D",
  bossMusic = "",
  ending = "",
  skin = "skinC",
  introCount = 0,
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level < 30 then
      return {mimic01 = 4, dragon01 = 3, gago01 = 2, cryst01 = 1}
    end
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
  end,
  getEnemyPopRate = function(level)
    return 0.3
  end
}

