Map = {
  name = "森林",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "forest_background.png",
  skin = "skinB",
  ending = "",
  nextMaps = {"3a_ruin","3b_castle"},
  initialLevel = 11,
  maxLevel = 20,
  getEnemyTable = function(level)
      if level <= 12 then
      return {leaf2A1 = 2, acorn1A0 = 1, flower1A0 = 1}
    elseif level <= 14 then
      return {leaf2A1 = 4, flower1A0 = 1}
    elseif level <= 16 then
      return {leaf2A0 = 1, acorn2A1 = 1, flower1A0 = 2}
    elseif level <= 18 then
      return {leaf2A0 = 1, acorn2A0 = 1, toadstool2A0 = 1}
    else
      return {leaf2A0 = 3, acorn2A0 = 1}
    end
    return {leafg2A0 = 1}
  end,
  getEnemyPopRate = function(level)
  if level <= 12 then
      return 0.3
  elseif level <= 16 then
      return 0.4
  elseif level <= 18 then
      return 0.3
  else
      return 0.4
  end
  end,
  fixedEnemies = {
    --{"level10",0}
  }
}
