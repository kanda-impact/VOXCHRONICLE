-- 笑うだけ。かわいい
EnemySkill = {
  name = "笑う",
  performSkill = function(self, user, characterManager, enemyManager)
    local mManager = MessageManager:sharedManager()
    local userName = user:getName()
    local currentCharacter = characterManager:getCurrentCharacter():getName()
    local rand = math.random(3)
    local text = {userName.."は"..currentCharacter.."にやさしく　ほほえんだ",
                  userName.."はわらっている　「ケロケロッ♪」",
                  userName.."「ケ〜ロ〜ロ〜　ケ〜ロ〜ロ〜」"}
    mManager:pushMessage(text[rand])
  end
}
return EnemySkill
