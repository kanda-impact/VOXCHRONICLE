Map = {
  name = "森林",
  wayMusic = "shinka",
  bossMusic = "",
  backgroundImage = "forest_background.png",
  thumbnailImage = "forest_thumbnail.png",
  skin = "skinB",
  ending = "",
  nextMaps = {"3a_ruin","3b_castle"},
  initialLevel = 11,
  maxLevel = 20,
  getEnemyTable = function(level)
      if level <= 12 then
      return {leaf1A0 = 2, acorn1A0 = 1, moth2A0 = 1}
    elseif level <= 14 then
      return {leaf1A0 = 1, acorn1A0 = 2, moth2A0 = 3}
    elseif level <= 16 then
      return {slime1A0 = 1, hornet2A0 = 1}
    elseif level <= 18 then
      return {leaf1A0 = 2, hornet2A0 = 5, toadstool2A0 = 1}
    else
      return {moth2A0 = 3, hornet2A0 = 1, toadstool2A0 = 1}
    end
    return {leaf2A0 = 1}
  end,
  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("leaf.png")
    enemyManager:loadEnemyTextureAsync("slime.png")
    enemyManager:loadEnemyTextureAsync("acorn.png")
    enemyManager:loadEnemyTextureAsync("moth.png")
    enemyManager:loadEnemyTextureAsync("hornet.png")    
    enemyManager:loadEnemyTextureAsync("toadstool.png")
    data:setClearedForMap("fp_forest")
  end,
  getEnemyPopRate = function(level)
  if level <= 12 then
      return 0.7
  elseif level <= 14 then
      return 0.8
  elseif level <= 16 then
      return 0.4
  elseif level <= 18 then
      return 0.3
  else
      return 0.4
  end
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    data:unlockAchievement("clear2A")
  end,

  fixedEnemies = {
    --{"level10",0}
  }
}
