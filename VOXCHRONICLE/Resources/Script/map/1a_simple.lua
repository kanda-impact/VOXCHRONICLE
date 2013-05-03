Map = {
  name = "荒野",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "simple_background.png",
  thumbnailImage = "simple_thumbnail.png",
  skin = "skinA",
  ending = "",
  nextMaps = {"2a_forest", "2b_cave"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <= 2 then
      return {leaf1A0 = 1, slime1A0 = 1 }
    elseif level <= 4 then
      return {leaf1A0 = 5, acorn1A0 = 2 }
    elseif level <= 6 then
      return {leaf1A0 = 5, slime1A0 = 2, acorn1A0 = 2}
    elseif level <= 8 then
      return {leaf1A0 = 5, slime1A0 = 3, acorn1A0 = 2}
    else
      return {slime1A0 = 1, acorn1A0 = 2}
    end
  end,
  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("leaf.png")
    enemyManager:loadEnemyTextureAsync("slime.png")
    enemyManager:loadEnemyTextureAsync("acorn.png")
    SaveData:sharedData():setClearedForMap("fp_simple")
    EffectLayer:sharedLayer():setCutinColor(ccc3(157, 241, 255))
  end,

  getEnemyPopRate = function(level)
    if level <= 6 then
      return 0.6
    else
      return 0.4
    end
    return 0.4
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    data:unlockAchievement("clear1A")
  end,

  fixedEnemies = {
  --{"level10",0}
  }
}
