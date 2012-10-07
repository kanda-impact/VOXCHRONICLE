Map = {
  name = "テストマップ",
  prefix = "dub",
  backgroundImage = "",
  nextMaps = {"test", "test"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <=3 then
      return {geek = 4, ginet1 = 1}
    elseif level <= 6 then
      return {geek = 2, ginet1 = 3, tnt = 1}
    else
      return {geek = 1, ginet1 = 3, tnt = 2, tetufez = 1}
    end
    return {}
  end,
  getEnemyPopRate = function(level)
    if level <= 2 then
      return 0.4
    elseif level <=5 then
      return 0.6
    elseif level <=8 then
      return 0,8
    end
    return 0.5


  end
}
