Map = {
  name = "テストマップ2a",
  wayMusic = "dub",
  bossMusic = "boss",
  introCount = 0,
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 10,
  maxLevel = 20,
  getEnemyTable = function(level)
    if level <=13 then
      return {geek = 1, ginet = 2, ginet2 = 1}
    elseif level <= 17 then
      return {geek = 1, ginet = 2, ginet = 2, tnt = 1}
    else
      return {geek = 1,ginet = 2, ginet2 = 3, tnt = 1, tetufez = 1}
    end
    return {}
  end,
  getEnemyPopRate = function(level)
    if level <= 15 then
      return 0.7
    end
  end
}
