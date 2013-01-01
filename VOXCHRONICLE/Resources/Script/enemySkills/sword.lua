-- ナイト用溜め攻撃
EnemySkill = {
  name = "強攻撃",
  performSkill = function(self, user, characterManager, enemyManager)
    row = user:getRow()
    col = user:getCol()
    math.random(100)
    i = 1 - ((math.random(2) - 1) * 2) -- iは-1か1になるはず
    enemyManager:popEnemyAt("iron", row, col + i) -- 自分の左か右に鉄球を生成
  end
}
return EnemySkill