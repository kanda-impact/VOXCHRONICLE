Map = {
  name = "Lesson3",
  wayMusic = "chabo",
  bossMusic = "",
  backgroundImage = "tutorial_background.png",
  skin = "skinA",
  ending = "",
  nextMaps = {},
  initialLevel = 21,
  maxLevel = 30,
  getEnemyTable = function(level)
    return {T_moth7 = 15}
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    self.__IRegister__:clearRegister()
    local level = characterManager:getLevel()
    local layer = EffectLayer:sharedLayer()
    if level == 21 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "テクニック編開始！", [[
めざせ！オクス上級者！テクニック編へようこそ～。
解説は引き続き、私、ラスカが担当させて
頂きま～す♪

じゃあとりあえず肩慣らしからいってみよう！
]])
    elseif level == 22 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "『パワーチャージ』を極めよう！", [[
このゲームで大切なのはムダな行動を
しないこと！難しいトコロではよけいな
行動はできるだけ減らしていきましょ。

たとえば、『パワーチャージ』。
うっかりためすぎちゃったりしてない？
]])
      popup:setText(1, "『パワーチャージ』を極めよう！", [[
『パワー』でふえる攻撃力はワザごとに
決まっているの。

モンスターの体力（色）に合わせて
『パワー』の回数を調整できるようになると
効率的に戦えるようになるわよ！
]])
    elseif level == 23 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "『パワー』の保持！", [[
そういえば、ためた『パワー』は、
そのまま待っていたり、『ダッシュ』を使うときは
消費しないのよ。

逆に『チェンジ』を使うと
キャンセルされちゃうから覚えておいてね！
]])
    elseif level == 24 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "", [[

    elseif level == 25 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "遅い敵・早い敵", [[
敵の中にはどんどん近づいてきたり、逆にゆっくり近づいてくる奴がいるよ！また、接近するにも一気に何歩も近づいてきたりするので気をつけてね。
]])
    elseif level == 26 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "同じ位置の敵へ一気に攻撃！", [[
たまーにだけれど、同じ位置に2体以上敵がいるときがあるんだ。そういうときは攻撃を両方に当てられるからラッキー！テンション最大での攻撃とか当てられると効果的だよ。
]])
    elseif level == 27 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "ボーナスモンスター", [[
まれに接近してこないで引っ込んじゃう敵がいるんだけれど、そいつは経験値が超豊富！倒せた時はさっさと次のレベルに進めるよ。魔法弓や範囲攻撃を上手く使いこなせば倒せるから狙ってみよう！
]])

    elseif level == 28 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "中距離攻撃にはガード", [[
レベル30まで到達すると出現するボスは、体当たり以外にも中距離攻撃を仕掛けてきたりするよ！結構強力な攻撃だったりするから、食らうと一気に追い込まれちゃうよ。でも中距離攻撃には攻撃の前兆があるから、上手く見極めてガードしてね！
]])
    elseif level == 29 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "最小ターンクリアへの道", [[
このゲームってクリアするとかかったターン数が表示されるのよね。ゲームになれてきたら、より少ないターンでのクリアに挑戦してみると面白いわよ！

ターン数の縮め方としては、出来るだけ範囲攻撃で一網打尽にするとかかなー。色々試してみてね！
]])
    elseif level == 30 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "さらなるテクニックは君の手で！", [[
プレイテクニックは、大体こんなところかなぁ。他にも色々とコツはあるはずだから、君の手でプレイしながらみつけてみてね。
]])
      popup:setText(1, "オクスクロニクルをしゃぶりつくせ！", [[
オクスクロニクルは4つのエンディングがあるから、是非全てのステージをプレイしてみてね！実績機能も付いてるから、骨の髄までオクスクロニクルを楽しんでくれると嬉しいな！

以上、ラスカによるテクニック解説でした～！
]])


    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
