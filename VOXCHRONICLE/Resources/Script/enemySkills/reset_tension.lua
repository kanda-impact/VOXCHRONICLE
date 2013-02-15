-- いてつくはどう
EnemySkill = {
  name = "いてつくはどう",
  performSkill = function(self, user, characterManager, enemyManager)
      local message = user:getName().."の　ゆびさきから　はどうが　ほとばしる"
      MessageManager:pushMessage(message)
      local message2 = characterManager:getCurrentCharacter():getName().."の　テンションが　もとにもどってしまった！"
      MessageManager:pushMessage(message2)
      characterManager:resetTension() -- テンションを0にする
  end
}
return EnemySkill
