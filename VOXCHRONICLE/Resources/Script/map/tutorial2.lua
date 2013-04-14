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

じゃあとりあえず大切な内容からいってみよう！
]])
    elseif level == 22 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "『遠距離攻撃』には『ガード』", [[
レベル30まで到達すると出現するボスモンスター
には、ぶつかってくるだけじゃなく『遠距離攻撃』を
してくるやつもいるよ！
]])
      popup:setText(1, "『遠距離攻撃』には『ガード』", [[
『遠距離攻撃』は『ガード』で防ぐしかないんだ。
『遠距離攻撃』の前には前兆があるから、
上手く見極めてガードしてね！
]])
   elseif level == 23 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "『貼りつきモンスター』に注意", [[
モンスターには、『耐性』などのほかに
トクベツな行動をしてくるヤツもいるわ！

要注意なのが『貼りつきモンスター』ね。
こいつはわたしたちに激突してこないで
手前でずっと攻撃してくるわ
]])
    elseif level == 24 then
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
    elseif level == 25 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "『パワー』の保持！", [[
そういえば、ためた『パワー』は、
そのまま待っていたり、『ダッシュ』を使うときは
消費しないのよ。

逆に『チェンジ』を使うと
キャンセルされちゃうから覚えておいてね！
]])
 
    elseif level == 26 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "モンスターの速さ", [[
モンスターには足の速いモンスターや
遅いモンスターがいるのは気づいたかしら？

わたしたちの攻撃は手前のモンスターを
優先的に攻撃するので、追い越してくる
モンスターがいるときには気を付けたほうがいいかも。
]])
    elseif level == 27 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "同じ位置への攻撃！", [[
もし速度の違うモンスターが手前の
モンスターを追い越そうとして同じ位置に
かさなっているときには一回の攻撃で
２体同時に攻撃できるよ

タイミングを見極めよう！
]])
    elseif level == 28 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "ステージの分岐", [[
ステージをクリアすると分かれ道が
現われるのよ。右に進むほど
むずかしくなっていくのよ。

難易度別に4つの
エンディングがあるから、
是非全てのステージをプレイしてみてね！
]])


    elseif level == 29 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "最小ターンクリアへの道", [[
ゲームを最後までクリアすると
かかったターン数が表示されるよ。

ゲームになれてきたら、より少ないターン
でのクリアに挑戦してみると面白いわよ！
]])
    elseif level == 30 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "さらなるテクニックは君の手で！", [[
プレイテクニックは、大体こんなところかなぁ。
他にも色々とコツはあるはずだから、
君の手でプレイしながらみつけてみてね。
]])
      popup:setText(1, "オクスクロニクルをしゃぶりつくせ！", [[
オクスクロニクルには
実績機能やモンスター図鑑
なんかもついてるから、気に入ってくれた人は
骨の髄までオクスクロニクルを楽しんでくれると嬉しいな！
以上、ラスカによるテクニック解説でした～！
じゃ～ね～
]])


    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
