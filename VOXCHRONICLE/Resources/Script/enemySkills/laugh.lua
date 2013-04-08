-- 笑うだけ。舐めプ技
EnemySkill = {
  name = "笑う",
  performSkill = function(self, user, characterManager, enemyManager)
    local mManager = MessageManager:shaderManager()
    mManager:pushMessage(enemy:getName().."は　不適な　笑みを　浮かべている")
  end
}
return EnemySkill
