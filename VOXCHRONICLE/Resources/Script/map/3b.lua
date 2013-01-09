Map = {
  name = "てつ面(3-B)",
  wayMusic = "dub",
  bossMusic = "boss",
  backgroundImage = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <= 2 then
      return {slime = 2, typhoon = 2}
    elseif level <= 5 then
      return {slime =
        2, typhoon = 2, leaf = 2}
    elseif level <= 7 then
      return {slime_physical = 3, leaf = 5, typhoon = 1}
    elseif level <= 9 then
      return {slime_physical = 1, leaf = 3, typhoon_magical = 1, geek_shield = 2}
    elseif level == 10 then
      return {}
    end
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 10 then
      knight = enemyManager:popEnemyAt("knight", MAX_ROW - 1, 1)
    end
  end,
  getEnemyPopRate = function(level)
    if level <=5 then
      return 0.5
    end
    return 0.7
  end,
  fixedEnemies = {
    {"Level10", 10}
  }
}
