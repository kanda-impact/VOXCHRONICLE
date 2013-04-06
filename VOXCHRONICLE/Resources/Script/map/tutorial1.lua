Map = {
  name = "Lesson2",
  wayMusic = "chabo",
  bossMusic = "",
  backgroundImage = "simple_background.png",
  skin = "skinA",
  ending = "",
  nextMaps = {},
  initialLevel = 11,
  maxLevel = 21,
  getEnemyTable = function(level)
    return {slime0 = 1}
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    self.__IRegister__:clearRegister()
    local level = characterManager:getLevel()
    local layer = EffectLayer:sharedLayer()
    if level == 11 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "ラスカにチェンジ！", [[
さぁ！ラスカちゃんに注目が集まるチュートリアルBよ！そろそろオクス君も疲れたでしょうから、私とタッチ交代してみて。新しくチェンジコマンドが追加されてるからタッチして私に交代してちょうだい。音楽も変わって気分一新よ！

私、ラスカは魔法使い。オクス君は剣だけど私は杖で氷結魔法を使って攻撃するわ。基本はオクス君と操作は変わらないから色々試してみてね！
]])
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
