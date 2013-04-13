function getTime()
  local time = VQTime:sharedTime()
  local hour = time:getCurrentHour()
  if 6 <= hour and hour < 16 then -- 朝
    return 0
  elseif 16 <= hour and hour < 19 then -- 夕方
    return 1
  end
  return 2
end

local normalTable = function(level)
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
  return {}
end

local sunsetTable = function(level)
  if level <= 2 then
    --return {}
    return {slime1S7 = 1, moth1S6 = 2}
  elseif level <= 4 then
    return {flower1S0 = 1, moth1S6 = 7}
  elseif level <= 6 then
    return {flower1S0 = 3, hornet1S1 = 1, bat1S5 = 1}
  elseif level <= 8 then
    return {slime1S7 = 2, moth1S6 = 2, hornet1S1 = 1}
  elseif level <= 9 then
    return {flower1S0 = 1, moth1S6 = 1, bat1S5 = 1}
  end
  --return {slime1S7 = 1, flower1S0 = 1, moth1S0 = 1, hornet1S1 = 1, bat1S2 =1}
  return {}
end

Map = {
  name = "平原",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "field_background0.png",
  skin = "skinB",
  ending = "",
  nextMaps = {"2b_cave","2c_cyber"},
  initialLevel = 8,
  maxLevel = 10,
  getEnemyTable = function(level)
    local time = getTime()
    if time == 1 then -- 夕方面
      return sunsetTable(level)
    else --その他
      return normalTable(level)
    end
  end,
  onLevelUp = function(self, characterManager, enemyManager)
  end,
  onLoad = function(self, characterManager, enemyManager)
    local number = getTime()
    local imageName = "field_background"..number..".png"
    self:changeBackgroundImage(imageName)
    local level = characterManager:getLevel()
    self.__IRegister__:setRegister("currentTime", number)
    enemyManager:loadEnemyTextureAsync("flower.png")
    enemyManager:loadEnemyTextureAsync("slime.png")
    enemyManager:loadEnemyTextureAsync("moth.png")
    enemyManager:loadEnemyTextureAsync("hornet.png")
    print("hoge")
  end,
  getEnemyPopRate = function(level)
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
    return 0
  end,
  onClear = function(self, characterManager, enemyManager)
    local data = SaveData:sharedData()
    local number = self.__IRegister__:getRegister("currentTime", 0)
    if number == 1 then
      data:unlockAchievement("tasonobara")
    end
    data:unlockAchievement("clear1B")
    data:setClearedForMap("fp_field")
  end,
  fixedEnemies = {
   -- {"flower1B0",0}
  }
}
--[[
Map['onLevelUp'] = function(self, characterManager, enemyManager)
  local time = self.__IRegister__:getRegister('currentTime', 0)
  if time == 1 then -- 夕方面
    Map['popEnemyTable'] = sunsetTable
  else --その他
    Map['popEnemyTable'] = normalTable
  end
  local time = getTime()
  local level = characterManager:getLevel()
  if time == 1 then
    if level == 9 then
      enemyManager:popEnemyAt("flower1S0", 6, 1)
    elseif level == 10 then
      enemyManager:popEnemyAt("kawaztan1S0", 3, 1)
    end
  end
  
end]]