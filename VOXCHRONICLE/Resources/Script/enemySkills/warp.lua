-- ラスボスワープ
EnemySkill = {
  name = "warp",
  performSkill = function(self, user, characterManager, enemyManager)
    math.random(100)
    local rand = math.random(100)
    if rand < 30 then
      user:setRow(0)
      user:setCol(1)
    else
      local row = math.random(MAX_ROW - 4)
      local col = math.random(3) - 1
      user:setRow(row)
      user:setCol(col)
    end
    SimpleAudioEngine:sharedEngine():playEffect("menu_cancel.mp3")
  end
}
return EnemySkill