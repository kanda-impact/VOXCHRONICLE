Map = {
  name = "炭鉱",
  wayMusic = "yuki",
  bossMusic = "",
  backgroundImage = "cave_background.png",
  thumbnailImage = "cave_thumbnail.png",
  skin = "skinC",
  ending = "",
  nextMaps = {"3b_castle","3c_ocean"},
  initialLevel = 11,
  maxLevel = 20,
  getEnemyTable = function(level)
    if level <= 12 then
      return {mukade2B0 = 3, wisp2B6 = 2}
    elseif level <= 14 then
      return {cryst2B3 = 2, bat2B0 = 3}
    elseif level <= 16 then
      return {mukade2B0 = 1, bat2B0 = 1, wisp2B6 = 2}
    elseif level <= 18 then
      return {cryst2B3 = 1, mukade2B0 = 1, bat2B0 = 2}
    elseif level <= 19 then
      return {mukade2B0 = 2, bat2B0 = 1, wisp2B6 = 1}
    elseif level <= 20 then
      return {cryst2B3 = 1, bat2B0 = 2, wisp2B6 = 1}
    end
      return {cryst2B3 = 1, bat2B0 = 1, mukade2B0 = 1, wisp2B6 = 1}
  end,
  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("cryst.png")
    enemyManager:loadEnemyTextureAsync("bat.png")
    enemyManager:loadEnemyTextureAsync("mukade.png")
    enemyManager:loadEnemyTextureAsync("wisp.png")
  end,
  getEnemyPopRate = function(level)
    if level <= 12  then
    return 0.23
    elseif level <= 14 then
    return 0.25
    elseif level <= 16 then
    return 0.25
    elseif level <= 19 then
    return 0.25
    elseif level <= 20 then
    return 0.22
    end
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    data:unlockAchievement("clear2B")
  end,

  fixedEnemies = {
    {"dragon2B0",840}
  }
}
