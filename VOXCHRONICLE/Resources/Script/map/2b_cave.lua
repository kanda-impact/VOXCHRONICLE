Map = {
  name = "炭鉱",
  wayMusic = "yuki",
  bossMusic = "",
  backgroundImage = "",
  skin = "skinC",
  ending = "",
  nextMaps = {"3b_castle","3c_ocean"},
  initialLevel = 11,
  maxLevel = 20,
  getEnemyTable = function(level)
    if level <= 22 then
      return {mukade2B0 = 3, wisp2B6 = 2}
    elseif level <= 24 then
      return {mukade2B0 = 2, bat2B0 = 3}
    elseif level <= 26 then
      return {cryst2B3 = 1, bat2B0 = 4}
    elseif level <= 28 then
      return {cryst2B3 = 1, mukade2B0 = 3, bat2B0 = 3}
    elseif level <= 30 then
      return {cryst2B3 = 1, bat2B0 = 3, wisp2B6 = 1}
    end
      return {cryst2B3 = 1, bat2B0 = 1, mukade2B0 = 0, wisp2B6 = 1}
  end,
  getEnemyPopRate = function(level)
    if level <= 22  then
    return 0.28
    elseif level <= 24 then
    return 0.3
    elseif level <= 26 then
    return 0.27
    elseif level <= 28 then
    return 0.28
    elseif level <= 30 then
    return 0.26
    end
  end,
  fixedEnemies = {
    {"dragon2B0",900}
  }
}
