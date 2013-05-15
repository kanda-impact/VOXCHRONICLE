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
    if 24 <= level and level <= 25 then
      return {leaf1A0 = 1, slime1A0 = 1 }
    elseif 28 <= level and level <= 29  then
      return {leaf1A0 = 5, acorn1A0 = 2 }
    elseif level == 30 then
      return {slime1A0 = 1, acorn1A0 = 2, T_tomezora23 = 1, T_tetufez2 = 2, T_geek2 = 1, T_leaf2 = 1, T_flower2 = 1}
    end
    return {}
  end,
  onLoad = function(self, characterManager, enemyManager)
    enemyManager:loadEnemyTextureAsync("ragasoowa.png")
    enemyManager:loadEnemyTextureAsync("knight.png")
  end,
  onBack = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    local layer = EffectLayer:sharedLayer()
    if level == 21 then
    elseif level == 22 then
      local preHP = self.__IRegister__:getRegister("preHP", characterManager:getHP())
      local shieldState = self.__IRegister__:getBool("shieldState")
      if characterManager:getHP() < preHP then
        local popup = layer:addPopupWindow(1)
        popup:setText(0, "遠距離攻撃にご用心", [[
きゃぁ！遠距離攻撃を食らっちゃった！

ボスモンスターの遠距離攻撃は強力だから注意
攻撃前には前兆があるから、良く見極めて
タイミング良く盾で『ガード』してね
]])
        popup:addImage(0, "tutorial8_1.png")
        characterManager:addHP(characterManager:getMaxHP())
      elseif shieldState and not characterManager:getShield() then -- シールド成功した場合
        local popup = layer:addPopupWindow(1)
        popup:setText(0, "『遠距離攻撃』には『ガード』", [[
おみごと！

ボスモンスターの攻撃は強力だから
うまく『ガード』を使いこなしてね
]])
        local boss = enemyManager:getEnemies():objectAtIndex(0)
        boss:setHP(3)
        boss.__IRegister__:setBool("isGuarded", true)        
      end
      
      self.__IRegister__:setRegister("preHP", characterManager:getHP())
      local preHP = self.__IRegister__:getRegister("preHP", characterManager:getHP())
      local shieldState = self.__IRegister__:getBool("shieldState")
    elseif level == 23 then
      local exp = characterManager:getExp()
      local next = 60 * 24
      local sub = next - exp
      local tomezoraExp = 10
      local count = math.floor(sub / tomezoraExp)
      local enemyCount = 0
      if enemyManager:getEnemies() then
        enemyCount = enemyManager:getEnemies():count()
      end
      if enemyCount < math.min(count, 2) and not layer:getPopupWindow() then -- ポップアップが出ているときは出さない
        local enemy = enemyManager:popEnemyAt("T_tomezora23", 2, enemyCount % 3)
        enemy:setMaxHP(10)
        enemy:setExp(20)
        enemy:setAttack(1)
      end
    elseif level == 26 or level == 27 then
      local turn = self.__IRegister__:getRegister("currentTurn", 0)
      if not enemyManager:getEnemies() or enemyManager:getEnemies():count() < 3 then
        local enemyName = "T_geek"
        if turn % 3 == 0 then
          enemyName = "T_tnt24"
        elseif turn % 3 == 1 then
          enemyName = "T_tomezora23"
        end
        local enemy = enemyManager:popEnemyAt(enemyName, 5, math.random(3) - 1)
        enemy:setExp(15)
        enemy:setAttack(1)
      end
      turn = turn + 1
      self.__IRegister__:setRegister("currentTurn", turn)
    else -- その他のレベルの時
      if enemyManager:getEnemies() then
        for i=0, enemyManager:getEnemies():count() - 1 do
          local enemy = enemyManager:getEnemies():objectAtIndex(i)
          if enemy:getRow() >= 5 then
            enemy:setRow(4) -- 後ろにいすぎる敵を強制的に前に
          end
        end
      end
    end
  end,
  onFinishPlaying = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 22 then
--      if characterManager:getLastSkill() and characterManager:getLastSkill():getIdentifier() == 'knockback' then
--        local layer = EffectLayer:sharedLayer()
--        local popup = layer:addPopupWindow(1)
--        popup:setText(0, "ノックバックは効かない！", [[
--あいつには『ノックバック』が効かないみたいね
--ボスモンスターのような巨大な敵には
--効かないことがあるの
--
--注意して！
--]])
--      end
      self.__IRegister__:setBool("shieldState", characterManager:getShield()) -- シールド状態をここで監視
    end
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    self.__IRegister__:clearRegister()
    local level = characterManager:getLevel()
    local layer = EffectLayer:sharedLayer()
    enemyManager:removeAllEnemies()
    characterManager:setExp(characterManager:getExpWithLevel(level))
    if level == 21 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "テクニック編開始！", [[
めざせ！オクス上級者！テクニック編へようこそ!
解説は引き続き、私、ラスカが担当させて
頂きま～す♪

じゃあとりあえず大切な内容からいってみよう！
]])
      popup:setText(1, "決戦！ボスモンスター", [[
レベル30まで到達するとボスモンスターが
出現するよ

ボスモンスターは仲間を呼んだり、
強力なワザを使ってきたり
さまざまな攻撃をしてくるの
]])
      popup:addImage(1, "tutorial21_1.png")
    local ragasoowa = enemyManager:popEnemyAt("T_ragasoowa", 3, 1)
    ragasoowa:setExp(60)
    ragasoowa:setMaxHP(30)
    elseif level == 22 then
      enemyManager:removeAllEnemies() -- 敵全滅
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "『遠距離攻撃』には『ガード』", [[
ボスモンスターの中には『遠距離攻撃』を
してくるやつもいるよ！
]])
      popup:addImage(0, "tutorial22_1.png")
      popup:setText(1, "『遠距離攻撃』には『ガード』", [[
『遠距離攻撃』は『ガード』で防ぐしかないんだ。
『遠距離攻撃』の前には前兆があるから、
上手く見極めてガードしてね！
]])
      popup:addImage(1, "tutorial8_1.png")
   local knight = enemyManager:popEnemyAt("T_knight22", 2, 1)
   knight:setExp(60)
   knight:setMaxHP(100)
   elseif level == 23 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "『貼りつきモンスター』に注意", [[
モンスターには、『耐性』などのほかに
トクベツな行動をしてくるヤツもいるわ！

要注意なのが『貼りつきモンスター』ね。
こいつはわたしたちに激突してこないで
手前でずっと攻撃してくるわ
]])
      popup:addImage(0, "tutorial23_1.png")
    elseif level == 24 then
      enemyManager:removeAllEnemies()
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
    popup:addImage(1, "tutorial24_2.png")
    elseif level == 25 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "『パワー』の保持！", [[
そういえば、ためた『パワー』は、
そのまま待っていたり、『ダッシュ』を使うときは
消費しないのよ。

逆にその他の行動を行うと
キャンセルされちゃうから覚えておいてね！
]])
      popup:addImage(0, "tutorial25_1.png")
    elseif level == 26 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "モンスターの速さ", [[
モンスターには足の速いモンスターや
遅いモンスターがいるのは気づいたかしら？

わたしたちの攻撃は手前のモンスターを先に
攻撃するので、追い越してくるモンスターが
いるときには気を付けたほうがいいかも。
]])
    popup:addImage(0, "tutorial26_1.png")
    elseif level == 27 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "同じ位置への攻撃！", [[
もし速度の違うモンスターが手前の
モンスターを追い越そうとして同じ位置に
かさなっているときには一回の攻撃で
２体同時に攻撃できるよ

タイミングを見極めよう！
]])  
      popup:addImage(0, "tutorial27_1.png")
    elseif level == 28 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "ステージの分岐", [[
ステージをクリアするとわかれ道が
あらわれるわよ。右に進むほど
むずかしくなっていくの。

難易度別に4つのエンディングがあるから
是非全てのステージをプレイしてみてね！
]])
      popup:addImage(0, "tutorial28_1.png")
    elseif level == 29 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "最小ターンクリアへの道", [[
ゲームを最後までクリアすると
かかったターン数が表示されるよ。

ゲームになれてきたら、より少ないターン
でのクリアに挑戦してみると面白いわよ！
]])
    popup:addImage(0, "tutorial29_1.png")
    elseif level == 30 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "さらなるテクニックは君の手で！", [[
プレイテクニックは、大体こんなところかなぁ。
他にも色々とコツはあるはずだから、
君の手でプレイしながらみつけてみてね。
]])
      popup:addImage(0, "tutorial30_1.png")
      popup:setText(1, "ほねまでしゃぶりつくそう！", [[
オクスクロニクルには
実績機能やモンスター図鑑なんかも
ついてるから、気に入ってくれた人は
骨の髄までオクスクロニクルを楽しんでくれると
嬉しいな！
]])
      popup:addImage(1, "tutorial30_2.png")
      popup:setText(2, "いざ、冒険の旅！", [[
さて、準備も整ったところで
いざ、冒険の旅にしゅっぱ〜つ！

以上、ラスカによるテクニック解説でした～！
じゃ～ね～
]])
      popup:addImage(2, "tutorial10_2.png")
      local data = SaveData:sharedData()
      data:unlockAchievement("clearTutorialC") -- 実績アンロック
      data:setClearedForMap("fp_tutorial") -- フリープレイ
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
