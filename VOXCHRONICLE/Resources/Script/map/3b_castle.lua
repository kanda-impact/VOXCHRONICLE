Map = {
  name = "古城",
  wayMusic = "dub",
  bossMusic = "3Bb",
  backgroundImage = "castle_background.png",
  thumbnailImage = "castle_thumbnail.png",
  skin = "skinC",
  ending = "endingB",
  nextMaps = {""},
  initialLevel = 21,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level <= 22 then
      return {slime3B1 = 1, mimic3B3 = 1}
    elseif level <= 24 then
      return {mimic3B3 = 2, gargoyle3B2 = 1}
    elseif level <= 26 then
      return {slime3B1 = 1, gargoyle3B2 = 1}
    elseif level <= 27 then
      return {slime3B1 = 1, dragon3B6 =1}
    elseif level <= 28 then
      return {slime3B1 = 3, mimic3B3 = 1, gargoyle3B2 = 2}
    elseif level <= 29 then
      return {slime3B1 = 3, gargoyle3B2 = 1, dragon3B6 =1}
    elseif level <= 30 then
      return {}
    else
      return {slime3B1 = 2, mimic3B3 = 3, gargoyle3B = 1, dragon3B6 =1}
    end
  end,
   onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("slime.png")
    enemyManager:loadEnemyTextureAsync("mimic.png")
    enemyManager:loadEnemyTextureAsync("gargoyle.png")
    enemyManager:loadEnemyTextureAsync("dragon.png")
    data:setClearedForMap("fp_castle")
  end,
   onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 29 then
      enemyManager:loadEnemyTextureAsync("knight.png")
      enemyManager:loadEnemyTextureAsync("iron.png")
    elseif level == 30 then
      CCTextureCache:sharedTextureCache():removeTextureForKey("slime.png")
      CCTextureCache:sharedTextureCache():removeTextureForKey("mimic.png")
      CCTextureCache:sharedTextureCache():removeTextureForKey("gargoyle.png")
      CCTextureCache:sharedTextureCache():removeTextureForKey("dragon.png")

      knight = enemyManager:popEnemyAt("knight_boss", MAX_ROW - 1, 1)
      enemyManager:setBoss(knight)
      SaveData:sharedData():setClearedForMap("fp_castle_boss")
    end
  end,
  getEnemyPopRate = function(level)
    if level <= 22 then
      return 0.22
    end
    return 0.2
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    data:unlockAchievement("clear3B")
  end,
  fixedEnemies = {
  }
}
