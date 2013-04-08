function getTime()
    local time = VQTime:sharedTime()
    local hour = time:getCurrentHour()
    local number = 0
    if 6 <= hour and hour < 16 then
      number = 0
    elseif 16 <= hour and hour < 19 then
      number = 1
    else
      number = 2
    end
    return number
end

Map = {
  name = "平原",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "field_background0.png",
  skin = "skinB",
  ending = "",
  nextMaps = {"2b_cave","2c_cyber"},
  initialLevel = 1,
  maxLevel = 10,
  
  onLoad = function(self, characterManager, enemyManager)
    local number = getTime()
    local imageName = "field_background"..number..".png"
    self:changeBackgroundImage(imageName)

    local level = characterManager:getLevel()
    --if number == 1 and level == 10
    
  end,
  getEnemyTable = function(level)
    local number = getTime()
    if number == 1 then
      if level <= 2 then
    --return {}
        return {slime1B7 = 3, moth1B0 = 2}
      elseif level <= 4 then
        return {flower1B0 = 1, moth1B0 = 5}
      elseif level <= 6 then
        return {flower1B0 = 1, hornet1B1 = 1}
      elseif level <= 8 then
        return {slime1B7 = 1, flower1B0 = 1, moth1B0 = 2}
      elseif level <= 9 then
        return {slime1B7 = 1, flower1B0 = 1, moth1B0 = 1, hornet1B1 = 1}
      end
    else
      if level <= 2 then
    --return {}
        return {slime1B7 = 3, moth1B0 = 2}
      elseif level <= 4 then
        return {flower1B0 = 1, moth1B0 = 5}
      elseif level <= 6 then
        return {flower1B0 = 1, hornet1B1 = 1}
      elseif level <= 8 then
        return {slime1B7 = 1, flower1B0 = 1, moth1B0 = 2}
      elseif level <= 10 then
        return {slime1B7 = 1, flower1B0 = 1, moth1B0 = 1, hornet1B1 = 1}
      end
    end  
    return {slime1B7 = 1, flower1B0 = 1, moth1B0 = 1, hornet1B1 = 1}
  end,
  onLevelUp = function(self, characterManager, enemyManager)
  end,
  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("flower.png")
    enemyManager:loadEnemyTextureAsync("slime.png")
    enemyManager:loadEnemyTextureAsync("moth.png")
    enemyManager:loadEnemyTextureAsync("hornet.png")    
  end,
  getEnemyPopRate = function(level)
    local number = getTime()
    if number == 1 then
      if level <= 2 then
        return 0.3
      elseif level <= 4 then
        return 0.4
      elseif level <= 6 then
        return 0.2
      elseif level <= 8 then
        return 0.3
      elseif level <= 10 then
        return 0.3
      end
    else
      if level <= 2 then
        return 0.3
      elseif level <= 4 then
        return 0.4
      elseif level <= 6 then
        return 0.2
      elseif level <= 8 then
        return 0.3
      elseif level <= 10 then
        return 0.3
      end
      return 0.2
    end
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    local number = getTime()
    if number == 1 then
    data:unlockAchievement("clear1B")
    end
    data:unlockAchievement("clear1B")
  end,

  fixedEnemies = {
    {"flower1B0",0}
  }
}
