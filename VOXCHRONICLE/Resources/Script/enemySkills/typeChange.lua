-- 耐性をこちらのキャラの状態で切り替える
EnemySkill = {
  name = "装備",
  performSkill = function(self, user, characterManager, enemyManager)
    local chara = characterManager:getCurrentCharacter():getCharacterType() -- 現在のキャラタイプを取得
    local mManager = MessageManager:sharedManager()
    local rand = math.random(10)
    if rand <= 5 then
      user:setSkillType(SkillTypeNormal) --耐性なし
      mManager:pushMessage(user:getName().."は　たいせいを　ととのえた")
    else
      if chara == CharacterTypeVox then -- 物理耐性
        user:setSkillType(SkillTypePhysical)
        mManager:pushMessage(user:getName().."は　まもりを　かためた")
      elseif chara == CharacterTypeLaska then -- 魔法耐性
        user:setSkillType(SkillTypeMagical)
        mManager:pushMessage(user:getName().."の　まわりを　見えない霧が　包み込む")
      end
    end
  end
}
return EnemySkill
