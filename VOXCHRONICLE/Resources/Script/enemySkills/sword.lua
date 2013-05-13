-- ナイト用溜め攻撃
EnemySkill = {
  name = "強攻撃",
  performSkill = function(self, user, characterManager, enemyManager)
    local key = "swordTurn"
    local turn = user:getRegister(key, 0) -- 溜めているターンを取得
    local mManager = MessageManager:sharedManager()
    if turn == 0 then
      -- 溜め初回ターンの時
      user:setAnimationClip("attack", 1, true) -- グラを変更する
      user:setRegister(key, turn + 1)
      local text = {
        user:getName().."は　けんを　かまえた",
        user:getName().."は　はきを　はなっている",
        user:getName().."は　ちからを　ためている"
      }
      local rand = math.random(#text)
      mManager:pushMessage(text[rand])


    elseif turn == 1 then
      user:setRegister(key, turn + 1) -- ターンを+1する
      -- 点滅させる処理を入れる
      local actions = CCArray:create()
      actions:addObject(CCFadeTo:create(0.05, 128))
      actions:addObject(CCFadeTo:create(0.05, 255))
      local sequence = CCSequence:create(actions)
      user:runAction(CCRepeat:create(sequence, 10))
    elseif turn == 2 then
      -- 溜めターンが1ターンに到達したら溜め攻撃発動
      local power = user:getAttack()
      characterManager:damage(power) -- ダメージを与える
      user:setRegister(key, 0) -- 溜めターンをリセット
      user:setDefaultAnimationClip() -- グラを元に戻す
      local text = {
        user:getName().."は　きょうりょくな　いちげきを　はなった！",
        user:getName().."の　こんしんの　いちげき！",
        user:getName().."の　あっとうてきな　けんげき！",
        user:getName().."は　けんを　おもいきり　ふりおろした"
      }
      local rand = math.random(#text)
      mManager:pushMessage(text[rand])
    end
  end
}
return EnemySkill
