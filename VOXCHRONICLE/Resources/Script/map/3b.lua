Map = {
  name = "てつ面(3-B)",
  wayMusic = "dub",
  bossMusic = "boss",
  backgroundImage = "",
  nextMaps = {"2a"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <= 2 then
      return {slime = 2, wisp = 2, mask = 2}
    elseif level <= 5 then
      return {mask =
        2, mimic = 2, wisp = 2}
    elseif level <= 7 then
      return {slime_physical = 3, mimic = 5, wisp = 1}
    elseif level <= 9 then
      return {slime_physical = 1, gargoyle = 3, mimic = 1, geek_shield = 2}
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
    {"Level10", 0}
  }
}
