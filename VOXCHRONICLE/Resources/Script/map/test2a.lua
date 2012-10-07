Map = {
  name = "テストマップ2",
  prefix = "dub",
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 10,
  maxLevel = 20,
  getEnemyTable = function(level)
    if level <=13 then
      return {geek = 1, ginet1 = 2, tetufez = 2, tnt = 2}
    elseif level <= 17 then
      return {geek = 4, ginet1 = 1, tetufez = 1, tnt = 1}
    else
      return {geek = 1}
    end
    return {}
  end,
  getEnemyPopRate = function(level)
    if level <= 15 then
      return 0.7
    elseif level <= 17 then
      return 0.8
    end
    return 1.0
  end
}
