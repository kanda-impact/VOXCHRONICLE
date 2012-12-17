Map = {
  name = "テストマップ",
  prefix = "dub",
  introCount = 2,
  backgroundImage = "",
  nextMaps = {"test2a", "test2b"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <=3 then
      return {geek = 4, ginet = 1}
    elseif level <= 7 then
      return {geek = 2, ginet = 3, tnt = 1}
    else
      return {geek = 1, ginet = 3, tnt = 2, tetufez = 1}
    end
    return {}
  end,
  getEnemyPopRate = function(level)
    if level <=5 then
      return 0.6
    end
    return 0.7
  end,
  fixedEnemies = {
    {"ginet", 100},
    {"tnt", 20}
  }
}
