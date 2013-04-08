-- 盾かバリアーをこちらのキャラの状態で切り替える
EnemySkill = {
  name = "装備",
  performSkill = function(self, user, characterManager, enemyManager)
    local chara = characterManager:getCurrentCharacter():getCharacterType() -- 現在のキャラタイプを取得
    local mManager = MessageManager:sharedManager()
    if chara == CharacterTypeVox then -- 盾装備
      user:setItem(EnemyItemShield)
      mManager:pushMessage(user:getName().."は 盾を　装備した")
    elseif chara == CharacterTypeLaska then -- バリアー装備
      user:setItem(EnemyItemBarrier)
      mManager:pushMessage(user:getName().."の　まわりを　妖しい光が　包み込む")
    end
  end
}
return EnemySkill
