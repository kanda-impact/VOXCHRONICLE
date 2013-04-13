-- 直接攻撃(ラスボス用)
EnemySkill = {
  name = "直接攻撃",
  performSkill = function(self, user, characterManager, enemyManager)
    local key = "directAttack"
    local turn = user:getRegister(key, 0) -- 溜めているターンを取得
    if turn == 0 then
      -- 溜め初回ターンの時
      -- user:setAnimationClip("attack", 1, true) -- グラを変更する
      user:setRegister(key, turn + 1) -- ターンを+1する
      -- 点滅させる処理を入れる
      local actions = CCArray:create()
      actions:addObject(CCFadeTo:create(0.05, 128))
      actions:addObject(CCFadeTo:create(0.05, 255))
      local sequence = CCSequence:create(actions)
      user:runAction(CCRepeat:create(sequence, 10))
    elseif turn == 1 then
      -- 溜めターンが1ターンに到達したら溜め攻撃発動
      characterManager:damage(8) -- ダメージを与える
      user:setRegister(key, 0) -- 溜めターンをリセット
      user:setDefaultAnimationClip() -- グラを元に戻す
      MessageManager:sharedManager():pushMessage(user:getName().."は　強力な　一撃を　放った")
    end
  end
}
return EnemySkill
