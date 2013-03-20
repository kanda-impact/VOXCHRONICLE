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
    local level = characterManager:getLevel()
    if level == 1 then
      local layer = EffectLayer:sharedLayer()
      local popup = layer:addPopupWindow(3)
      local node = popup:getPage(0)
      print(node)
      local dimensions = CCSizeMake(380, 280)
      node:setAnchorPoint(ccp(0.5, 0.5))
      local hoge = [[
さあ！攻撃だ！
剣のコマンドを押すんだ！ざしゅ！！攻撃キター！！！！こうげききたー！
みろよ！スライムが！無残に粉砕！ひゃっほう。
      ]]
      local text = CCLabelTTF:create(hoge, "Helvetica", 22, dimensions, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop)
      local shadow = CCLabelTTF:create(hoge, "Helvetica", 22, dimensions, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop)
      text:setColor(ccc3(220, 220, 220))
      shadow:setColor(ccc3(33, 33, 33))
      text:setPosition(ccp(200, 150))
      shadow:setPosition(ccp(202, 148))
      node:addChild(shadow)
      node:addChild(text)
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
