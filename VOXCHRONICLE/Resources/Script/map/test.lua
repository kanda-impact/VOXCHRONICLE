Map = {
  name = "テストマップ",
  prefix = "dub",
  backgroundImage = "",
  nextMaps = {"test", "test"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    enemies = {}
    if true then
      enemies = {tnt = 30}
    end
    return enemies
  end,
  getEnemyPopRate = function(level)
    return 0.4
  end
}
