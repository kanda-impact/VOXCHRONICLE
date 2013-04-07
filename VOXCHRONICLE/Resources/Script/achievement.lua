
local dictionaryEnemyCount = 10 -- モンスター図鑑の最大数。あとで関数から取れるようにします

-- 毎ターン判定する実績は、関数で呼び出すとパフォーマンス低下が懸念されるので、dictで持つ
saveDataAchievement = {
  -- {SaveDataCountKey, count, "実績identifier"}
  {SaveDataCountKeyTurn, 1000, "beat1000"},
  {SaveDataCountKeyTurn, 10000 "beat10000"},
  {SaveDataCountKeyTurn, 50000, "beat100000"},
  {SaveDataCountKeyDefeat, 100, "defeat100"},
  {SaveDataCountKeyDefeat, 1000, "defeat1000"},
  {SaveDataCountKeyDefeat, 10000, "defeat10000"},
  {SaveDataCountKeyMPMiss, 10, "miss10"},
  {SaveDataCountKeyDictionaryCount, dictionaryEnemyCount * 0.5, "enemy50"},
  {SaveDataCountKeyDictionaryCount, dictionaryEnemyCount * 0.8, "enemy80"},
  {SaveDataCountKeyDictionaryCount, dictionaryEnemyCount, "enemy100"},
  {SaveDataCountKeyHitDamage, 1000, "hit1000"},
  {SaveDataCountKeyAttackDamage, 1000, "attack1000"},
  {SaveDataCountKeyDead, 1000, "play1000"}
}

-- 1回のプレイ中のカウントに依存する実績を書きます
playLogAchievement = {
}

-- クリア時に実績チェックのために呼び出されます
function checkAchievementOnClear(characterManager, enemyManager, playlog)
  if characterManager:getHP() == 1 then
  end 
end