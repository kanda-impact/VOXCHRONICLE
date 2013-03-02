Map = {
  name = "宇宙",
  wayMusic = "nmb",
  bossMusic = "AttaQ3-D",
  ending = "",
  skin = "skinC",
  introCount = 0,
  backgroundImage = "space_background.png",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level < 30 then
      return {dragon01 = 3, cryst01 = 1} --専用の敵はすべて未実装
    elseif level == 30 then
      return {}
    end
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
  end,
  getEnemyPopRate = function(level)
    return 0.3
  end
}

