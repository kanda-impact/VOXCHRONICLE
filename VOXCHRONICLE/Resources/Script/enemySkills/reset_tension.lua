-- いてつくはどう
EnemySkill = {
  name = "いてつくはどう",
  performSkill = function(self, user, characterManager, enemyManager)
      local message = user:getName().."の　ゆびさきから　はどうが　ほとばしる"
      local mManager = MessageManager:sharedManager() -- メッセージマネージャーを取り出す
      mManager:pushMessage(message)
      local message2 = characterManager:getCurrentCharacter():getName().."の　テンションが　もとにもどってしまった！"
      mManager:pushMessage(message2)
      characterManager:resetTension() -- テンションを0にする
  end
}
return EnemySkill
