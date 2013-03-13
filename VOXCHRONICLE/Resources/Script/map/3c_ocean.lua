Map = {
  name = "深海",
  wayMusic = "dub",
  bossMusic = "Ceres78",
  backgroundImage = "",
  skin = "skinA",
  ending = "endingC",
  nextMaps = {""},
  initialLevel = 21,
  maxLevel = 30,
  getEnemyTable = function(level)
    if level < 30 then
      return {whale3C0 = 3, jfish3C0 = 2, naut3C0 = 1}
    elseif level == 30 then
      return {}
    end
  end,
  getEnemyPopRate = function(level)
    return 0.6
  end,
  fixedEnemies = {
  }
}
