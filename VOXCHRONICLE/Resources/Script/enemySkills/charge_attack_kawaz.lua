-- 直接攻撃(かわずたん用)
EnemySkill = {
  name = "直接攻撃",
  performSkill = function(self, user, characterManager, enemyManager)
    local key = "skillCharge"
    local layer = EffectLayer:sharedLayer()
    local turn = user:getRegister(key, 0) -- 溜めているターンを取得
    local mManager = MessageManager:shaderManager()
    if user:getType() == SkillTypeMagical then
      if turn <= 1 then
        -- 溜め初回ターンの時
        user:setAnimationClip("attack", 1, true) -- グラを変更する
        user:setRegister(key, turn + 1) -- ターンを+1する
        -- 点滅させる処理を入れる
        local actions = CCArray:create()
        actions:addObject(CCFadeTo:create(0.05, 128))
        actions:addObject(CCFadeTo:create(0.05, 255))
        local sequence = CCSequence:create(actions)
        user:runAction(CCRepeat:create(sequence, 10))
      elseif turn == 2 then
        -- 溜めターンが2ターンに到達したら溜め攻撃発動
        characterManager:damage(8) -- ダメージを与える
        user:setRegister(key, 0) -- 溜めターンをリセット
        user:setDefaultAnimationClip() -- グラを元に戻す
        layer:addEffectOnEnemy(nil, "thunder", 6, CCRectMake(0, 0, 120, 80)):setColor(ccc3(255, 1, 78))
        local text = {
          user:getName().."は　強力な　魔法を　放った",
          user:getName().."の　スーパー　マジカル！",
          user:getName().."の　ちょう　ひっさつ　まほう！",
          "ひっさつ　じゅもんを　くらうケロー！",
          "ケロケロケロリン　ピリピリピーン！"
        }
        local rand = math.random(#text)
        mManager:pushMessage(text[rand])
      end
    else
      if turn == 0 then
        -- 溜め初回ターンの時
        user:setAnimationClip("attack", 1, true) -- グラを変更する
        user:setRegister(key, turn + 1) -- ターンを+1する
        -- 点滅させる処理を入れる
        local actions = CCArray:create()
        actions:addObject(CCFadeTo:create(0.05, 128))
        actions:addObject(CCFadeTo:create(0.05, 255))
        local sequence = CCSequence:create(actions)
        user:runAction(CCRepeat:create(sequence, 10))
      elseif turn == 1 then
        -- 溜めターンが1ターンに到達したら溜め攻撃発動
        if user:getType() == SkillTypeNormal then
          characterManager:damage(1)
        end
        characterManager:damage(1)
        characterManager:damage(1) -- ダメージを与える
        user:setRegister(key, 0) -- 溜めターンをリセット
        user:setDefaultAnimationClip() -- グラを元に戻す
        layer:addEffectOnEnemy(nil, "attack", 4, CCRectMake(0, 0, 50, 50)):setColor(ccc3(0, 255, 230))

        local text = {
          user:getName().."は　すばやく　切りかかってきた",
          user:getName().."は　おもいきり　きりつけてきた",
          user:getName().."は　きょうきを　ふりまわした",
          user:getName().."がむしゃらに　けんを　ふりまわす",
          "ひっさつけんを　くらうケロ～！"
        }
        local rand = math.random(#text)
        mManager:pushMessage(text[rand])

      end
    end
  end
}
return EnemySkill
