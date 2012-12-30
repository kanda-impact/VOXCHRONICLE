Map = {
  name = "スクリプトテスト",
  wayMusic = "dub",
  bossMusic = "boss",
  backgroundImage = "",
  nextMaps = {"test"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <=9 then
      return {geek_shield = 1, slime = 2, leaf = 5, typhoon = 2}
    elseif level == 10 then
      return {}
    end
    return {}
  end,
  getEnemyPopRate = function(level)
    if level <=5 then
      return 0.3
    end
    return 0.5
  end,
  fixedEnemies = {
    {"ginet", 100},
    {"tnt", 20},
    {"Level10", 10}
  }
}
