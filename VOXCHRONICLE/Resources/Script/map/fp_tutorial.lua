Map = {
  name = "レッスン",
  wayMusic = "chabo",
  bossMusic = "",
  backgroundImage = "tutorial_background.png",
  skin = "skinA",
  ending = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 30,
  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("leaf.png")
    enemyManager:loadEnemyTextureAsync("slime.png")
    enemyManager:loadEnemyTextureAsync("acorn.png")
  end,
  onLevel = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 19 then
      enemyManager:loadEnemyTextureAsync("moth.png")
      enemyManager:loadEnemyTextureAsync("hornet.png")
      enemyManager:loadEnemyTextureAsync("toadstool.png")
    elseif level == 29 then
      enemyManager:loadEnemyTextureAsync("mask.png")
      enemyManager:loadEnemyTextureAsync("wisp.png")
      enemyManager:loadEnemyTextureAsync("typhoon.png")
      enemyManager:loadEnemyTextureAsync("mimic.png")
      enemyManager:loadEnemyTextureAsync("gargoyle.png")
    end
  end,
  getEnemyTable = function(level)
    if level <= 2 then
      return {leaf1A0 = 1, slime1A0 = 1 }
    elseif level <= 4 then
      return {leaf1A0 = 5, acorn1A0 = 2 }
    elseif level <= 6 then
      return {leaf1A0 = 5, slime1A0 = 2, acorn1A0 = 2}
    elseif level <= 8 then
      return {leaf1A0 = 5, slime1A0 = 3, acorn1A0 = 2}
    elseif level <= 10 then
      return {slime1A0 = 1, acorn1A0 = 2}
    elseif level <= 12 then
      return {leaf1A0 = 2, acorn1A0 = 1, moth2A0 = 1}
    elseif level <= 14 then
      return {leaf1A0 = 1, acorn1A0 = 2, moth2A0 = 3}
    elseif level <= 16 then
      return {slime1A0 = 1, hornet2A0 = 1}
    elseif level <= 18 then
      return {leaf1A0 = 2, hornet2A0 = 5, toadstool2A0 = 1}
    elseif level <= 20 then
      return {moth2A0 = 3, hornet2A0 = 1, toadstool2A0 = 1}
    elseif level <= 22 then
      return {mimic3A1 = 2, mask3A1 = 5}
    elseif level <= 24 then
      return {wisp3A2 = 3, typhoon3A2 = 2}
    elseif level <= 26 then
      return {mimic3A1 = 2,mask3A1 = 6,gargoyle3A0 = 2}
    elseif level <= 28 then
      return {mask3A1 = 3, wisp3A2 = 3, typhoon3A2 = 1, mimic3A1 = 1}
    elseif level < 30 then
      return {mask3A1 = 3, typhoon3A2 = 3,gargoyle3A0 = 1}
    end
  end,
  getEnemyPopRate = function(level)
    if level <= 10 then
      return 0.5
    elseif level <= 20 then
      return 0.4
    else
      return 0.3
    end
  end,
  fixedEnemies = {
  }
}
