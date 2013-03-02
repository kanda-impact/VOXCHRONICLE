Map = {
  name = "古代遺跡",
  wayMusic = "",
  bossMusic = "",
  backgroundImage = "",
  skin = "skinC",
  ending = "",
  nextMaps = {""},
  initialLevel = 21,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level <= 2 then
      return {mask3A0 = 3, typhoon3A0 = 2,wisp3A0 = 2 }
    elseif level <= 5 then
      return {}
    else
      return {}
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  fixedEnemies = {
  }
}
