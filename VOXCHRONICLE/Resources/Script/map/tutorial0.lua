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
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "さあ！戦いの始まりだ！", [[
やあやあ！私はラスカ。オクス君（あなた）のパートナーよ。細かい説明は省くけど、これからゲームについて説明していくよ。タイトルで少しの間待っているとストーリーのデモが流れるのでそちらも宜しくね！
]])
      popup:setText(1, "オクスクロニクルってどんなゲーム？", [[
オクスクロニクルは主観視点、画面奥から自分に近づいてくる敵をやっつけていくゲームよ。音量を上げてノリノリでプレイしてみてね。下にあるタイムマーカーが一周する毎に選択していたコマンドが行われるわ。まずは剣のマークをタッチして攻撃コマンドを試してみましょ。
]])
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
