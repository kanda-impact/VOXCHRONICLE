-- 笑うだけ。舐めプ技
EnemySkill = {
  name = "笑う",
  performSkill = function(self, user, characterManager, enemyManager)
    local mManager = MessageManager:sharedManager()
    mManager:pushMessage(user:getName().."は"..characterManager:getCurrentCharacter:getName().."にやさしく　ほほえんだ")
  end
}
return EnemySkill
