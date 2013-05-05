-- 笑うだけ。舐めプ技
EnemySkill = {
  name = "笑う",
  performSkill = function(self, user, characterManager, enemyManager)
    local mManager = MessageManager:sharedManager()
    local text = {
      user:getName().."は　不敵な　笑みを　浮かべている",
      user:getName().."は　ふしぎな　おどりを　おどった",
      user:getName().."は　にやにや　している",
      user:getName().."は　こちらの　ようすを　うかがっている"
    }
    local rand = math.random(#text)
    mManager:pushMessage(text[rand])
  end
}
return EnemySkill
