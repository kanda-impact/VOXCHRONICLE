Map = {
  name = "テストマップ１",
  wayMusic = "dub",
  bossMusic = "boss",
  backgroundImage = "",
  skin = "skinA",
  nextMaps = {},
  ending = "endingB",
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <= 1 then
      return {tut_slime1 = 1}
    elseif level <= 2 then
      return {tut_slime0 = 1}
    else
      if level % 2 == 1 then
        return {tut_slime0 = 1}
      else
        return {tut_slime1 = 1}
      end
    end
    return {}
  end,
  onLevel = function(level, characterManager, enemyManager)
    if level == 10 then
      knight = enemyManager:popEnemyAt("knight_boss", MAX_ROW - 1, 1)
      enemyManager:setBoss(knight)
    end
  end,
  getEnemyPopRate = function(level)
    if level <= 1 then --アタックの使い方
      return 0.3
    elseif level <= 2 then  --4連撃など
      return 0.8
    elseif level <= 3 then  --キャラチェンジ
      return 0.7
    elseif level <= 4 then  --テンション
      return 0.3
    elseif level <= 5 then  --HPの高い敵が出てくる
      return 0.4
    elseif level <= 6 then  --ラスカサンダーの説明
      return 0.3
    elseif level <= 7 then  --実践
      return 1
    elseif level <= 8 then  --オクスラッシュの説明
      return 0.3
    elseif level <= 9 then  --実践
      return 1
    elseif level <= 10 then
     return 0.3
    end
    return 0.7
  end,
  fixedEnemies = {
    {"tut_flower", 240}
  }
}
