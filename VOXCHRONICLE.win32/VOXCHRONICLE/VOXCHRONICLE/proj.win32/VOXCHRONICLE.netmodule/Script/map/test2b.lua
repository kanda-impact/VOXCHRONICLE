Map = {
  name = "テストマップ2b",
  prefix = "dub",
  introCount = 0,
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 10,
  maxLevel = 20,
  getEnemyTable = function(level)
    if level <=13 then
      return {ginet = 3, tetufez = 1}
    elseif level <= 17 then
      return {ginet = 1, tnt = 2}
    else
      return {tnt = 2, tetufez = 3}
    end
    return {}
  end,
  getEnemyPopRate = function(level)
    if level <= 15 then
      return 0.7
    end
    return 0.8
  end
}
