-- ラスボスワープ
EnemySkill = {
  name = "warp",
  performSkill = function(self, user, characterManager, enemyManager)
    math.random(100)
    row = math.random(MAX_ROW - 1)
    col = math.random(3)
    user:setRow(row)
    user:setCol(col)
    SimpleAudioEngine:sharedEngine():playEffect("menu_cancel.mp3")
  end
}
return EnemySkill