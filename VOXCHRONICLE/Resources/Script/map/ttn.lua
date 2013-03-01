Map = {
  name = "たわし面",
  wayMusic = "ttn1",
  bossMusic = "",
  backgroundImage = "ruin_background.png",
  skin = "skinC",
  ending = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 99,
  getEnemyTable = function(level)
    return {slime0 = 1}
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 1 then
      local layer = EffectLayer:sharedLayer()
      layer:addTutorialWindow()
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
