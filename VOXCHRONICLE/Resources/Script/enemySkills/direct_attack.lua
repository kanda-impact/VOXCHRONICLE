-- 直接攻撃
EnemySkill = {
  name = "直接攻撃",
  performSkill = function(self, user, characterManager, enemyManager)
    local power = user:getAttack()
    characterManager:damage(power) -- ダメージを与える  
  end
}
return EnemySkill
