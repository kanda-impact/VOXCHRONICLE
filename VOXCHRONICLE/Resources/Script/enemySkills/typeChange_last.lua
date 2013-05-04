-- 耐性をこちらのキャラの状態で切り替える
EnemySkill = {
  name = "装備",
  performSkill = function(self, user, characterManager, enemyManager)
    local chara = characterManager:getCurrentCharacter():getCharacterType() -- 現在のキャラタイプを取得
    local mManager = MessageManager:sharedManager()
    local rand = math.random(10)
    local someEnemy = enemyManager:getEnemies():randomObject()
    local userName = user:getName()
    local someName = someEnemy:getName()
    if chara == CharacterTypeVox then -- 物理耐性
      someEnemy:setSkillType(SkillTypePhysical)
      mManager:pushMessage(userName.."は　まもりを　かためた")
      --user:getName()..は　ぼうぎょしょうへきを　てんかいした！
    elseif chara == CharacterTypeLaska then -- 魔法耐性
      someEnemy:setSkillType(SkillTypeMagical)
      mManager:pushMessage(userName.."の　まわりを　見えない霧が　包み込む")
        --user:getName()..は　まほうしょうへきを　てんかいした！
        --user:getName()..の　まほうの　カベ！
        --user:getName()..は　まほうが　ききにくくなった！
    end
  end
}
return EnemySkill
