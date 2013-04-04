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
      return {cryst2B3 = 1, bat2B0 = 4}
    elseif level <= 16 then
      return {mukade2B0 = 2, bat2B0 = 3}
    elseif level <= 18 then
      return {cryst2B3 = 1, mukade2B0 = 3, bat2B0 = 3}
    elseif level <= 20 then
      return {cryst2B3 = 1, bat2B0 = 3, wisp2B6 = 1}
    end
      return {cryst2B3 = 1, bat2B0 = 1, mukade2B0 = 1, wisp2B6 = 1}
  end,
  getEnemyPopRate = function(level)
    if level <= 12  then
    return 0.25
    elseif level <= 14 then
    return 0.23
    elseif level <= 16 then
    return 0.27
    elseif level <= 18 then
    return 0.25
    elseif level <= 20 then
    return 0.24
    end
  end,
  fixedEnemies = {
    {"dragon2B0",840}
  }
}
