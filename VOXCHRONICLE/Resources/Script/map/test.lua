Map = {
  name = "テストマップ",
  prefix = "dub",
  backgroundImage = "",
  nextMaps = {"test", "test"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <=3 then
      return {geek = 1}
    elseif level <= 7 then
      return {geek = 2, ginet1 = 3}
    else
      return {geek = 1, ginet1 = 4, ginet2 = 2,tnt = 3}
    end
    return {}
  end,
  getEnemyPopRate = function(level)
    return 0.8
  end
}
