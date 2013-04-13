
local dictionaryEnemyCount = 53 -- 面倒なのでハードコーディングします

Achievement = {
  -- 毎ターン判定する実績は、関数で呼び出すとパフォーマンス低下が懸念されるので、dictで持つ
  saveData = {
    -- {SaveDataCountKey, count, "実績identifier"}
    {SaveDataCountKeyTurn, 1000, "beat1000"},
    {SaveDataCountKeyTurn, 10000, "beat10000"},
    {SaveDataCountKeyTurn, 50000, "beat100000"},
    {SaveDataCountKeyDefeat, 100, "defeat100"},
    {SaveDataCountKeyDefeat, 1000, "defeat1000"},
    {SaveDataCountKeyDefeat, 10000, "defeat10000"},
    {SaveDataCountKeyMPMiss, 10, "miss10"},
    {SaveDataCountKeyDictionaryCount, dictionaryEnemyCount * 0.5, "enemy50"},
    {SaveDataCountKeyDictionaryCount, dictionaryEnemyCount * 0.8, "enemy80"},
    {SaveDataCountKeyDictionaryCount, dictionaryEnemyCount, "enemy100"},
    {SaveDataCountKeyHitDamage, 1000, "hit1000"},
    {SaveDataCountKeyAttackDamage, 10000, "attack10000"},
    {SaveDataCountKeyDead, 1000, "play1000"}
  },
  -- 1回のプレイ中のカウントに依存する実績を書きます
  playLog = {
    {PlayLogKeyMaxDefeat, 10, "defeat10"}, -- 一気呵成
    {PlayLogKeyMaxRepeatCount, 20, "repeat20"}, -- こだわりのワンパターン
    {PlayLogKeyMaxRepeatChangeCount, 10, "change10"} -- 戦場の踊り子
  },
  -- クリア時に実績チェックのために呼び出されます
  checkAchievementOnClear = function(playlog, characterManager, enemyManager)
    local data = SaveData:sharedData()
    if playlog:getCount(PlayLogKeyTurn) <= 300 then -- 疾風迅雷
      data:unlockAchievement("clearSpeedy")
    end
    if playlog:getCount(PlayLogKeyRunCount) >= 20 then -- りえきは　ないと　いったのに
      data:unlockAchievement("run20")
    end
    if playlog:getCount(PlayLogKeyVOXAttackCount) == playlog:getCount(PlayLogKeyLSKAttackCount) then -- シンクロナイズ
      data:unlockAchievement("sync")
    end
    if characterManager:getHP() == 1 then -- 死線、紙一重
      data:unlockAchievement("hp1")
    end
    if characterManager:getMP() == 0 then -- お疲れラスカ
      data:unlockAchievement("mp0")
    end
    if playlog:getCount(PlayLogKeyChangeCount) == 0 then -- 孤高の戦士
      data:unlockAchievement("nochange")
    end
    if playlog:getCount(PlayLogKeyTensionCount) == 0 then -- 能ある鷹は爪を隠す
      data:unlockAchievement("notension")
    end
    if playlog:getCount(PlayLogKeyHitDamage) == 0 then -- 完全無欠
      data:unlockAchievement("clearNoDamage")
    end
  end
}

return Achievement