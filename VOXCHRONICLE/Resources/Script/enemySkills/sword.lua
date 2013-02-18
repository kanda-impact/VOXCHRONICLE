-- ナイト用溜め攻撃
EnemySkill = {
  name = "強攻撃",
  performSkill = function(self, user, characterManager, enemyManager)
    local key = "swordTurn"
    local turn = user:getRegister(key, 0) -- 溜めているターンを取得
    if turn == 0 then
      -- 溜め初回ターンの時
      user:setAnimationClip("sword", 1, true) -- グラを変更する
      user:setRegister(key, turn + 1)
      MessageManager:sharedManager():pushMessage(user:getName().."は　ちからを　ためている")
    elseif turn == 2 then
      -- 溜めターンが1ターンに到達したら溜め攻撃発動
      characterManager:damage(20) -- ダメージを与える
      user:setRegister(key, 0) -- 溜めターンをリセット
      user:setDefaultAnimationClip() -- グラを元に戻す
      MessageManager:sharedManager():pushMessage(user:getName().."は　きょうりょくな　いちげきを　はなった！")
    else
      user:setRegister(key, turn + 1) -- ターンを+1する
    end
  end
}
return EnemySkill
