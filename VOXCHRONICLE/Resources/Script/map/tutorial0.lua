Map = {
  name = "Lesson1",
  wayMusic = "chabo",
  bossMusic = "",
  backgroundImage = "simple_background.png",
  skin = "skinA",
  ending = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    return {slime0 = 1}
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 1 then
      local layer = EffectLayer:sharedLayer()
      local popup = layer:addPopupWindow(3)
      local node = popup:getPage(0)
      popup:setText("Hello VOXCHRONICLE", [[
さあ！攻撃だ！
剣のコマンドを押すんだ！ざしゅ！！攻撃キター！！！！こうげききたー！
みろよ！スライムが！無残に粉砕！ひゃっほう。
]])
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
