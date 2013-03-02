Map = {
  name = "歪み電脳",
  wayMusic = "",
  bossMusic = "",
  backgroundImage = "",
  skin = "skinA",
  ending = "",
  nextMaps = {"3c","3d"},
  initialLevel = 11,
  maxLevel = 20,
  getEnemyTable = function(level)
    if level <= 20 then
      return {tetufez1B0 = 1} --歪み電脳の敵はすべて未実装
    elseif level <= 3 then
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
