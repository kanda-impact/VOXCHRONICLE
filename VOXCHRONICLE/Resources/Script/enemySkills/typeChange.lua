-- 耐性をこちらのキャラの状態で切り替える
EnemySkill = {
  name = "装備",
  performSkill = function(self, user, characterManager, enemyManager)
    local chara = characterManager:getCurrentCharacter():getCharacterType() -- 現在のキャラタイプを取得
    local mManager = MessageManager:sharedManager()
    local rand = math.random(10)
    local userName = user:getName()
    if not user:getType() == SkillTypeNormal and rand <= 2 then
      user:setSkillType(SkillTypeNormal) --耐性なし
      local text = {
        user:getName().."は　ぼうぎょを　といた",
        userName.."は　たいせいを　ととのえた"
      }
      local rand = math.random(#text)
      mManager:pushMessage(text[rand])
    else
      if chara == CharacterTypeVox then -- 物理耐性
        user:setSkillType(SkillTypePhysical)
        local text = {
          userName.."は　まもりを　かためた",
          user:getName().."は　ぼうぎょしょうへきを　てんかいした！",
          "ぼうぎょ　しょうへき　ケロー！"
        }
        local rand = math.random(#text)
        mManager:pushMessage(text[rand])
      elseif chara == CharacterTypeLaska then -- 魔法耐性
        user:setSkillType(SkillTypeMagical)
        local text = {
          user:getName().."は　まほうしょうへきを　てんかいした！",
          user:getName().."の　まほうの　カベ！",
          user:getName().."は　まほうが　ききにくくなった！",
          "まほう　しょうへき　ケローっ！",
          userName.."の　まわりを　見えない霧が　包み込む"
        }
        local rand = math.random(#text)
        mManager:pushMessage(text[rand])
      end
    end
  end
}
return EnemySkill
