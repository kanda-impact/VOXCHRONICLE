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
    return {}
  end,
  onFinishPlaying = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    local layer = EffectLayer:sharedLayer()
    if level == 4 then
      local popuped = self.__IRegister__:getBool("popuped") -- ポップアップしたかフラグ
      if enemyManager:getEnemies():count() == 1 and not popuped then
        self.__IRegister__:setBool("popuped", true)
        -- 前の裏拍で敵が出現したあと、ポップアップを出します
        local popup = layer:addPopupWindow(1)
        popup:setText(0, "ダッシュで敵が出現", [[あ、見てみて！敵が見えてきたよ
        
        うっかりダッシュしすぎると敵がすぐ目の前でどうしようなんてなっちゃうから、最初のうちは焦らずにゆったり構えている方がいいかもね。
        ]])
      end
    end
  end,
  onBack = function(self, characterManager, enemyManager)
    math.random(100)
    local layer = EffectLayer:sharedLayer()
    local preHP = self.__IRegister__:getRegister("preHP", characterManager:getHP())  
    local level = characterManager:getLevel()
    local enemies = enemyManager:getEnemies()
    local enemyCount = 0
    if not (enemies == nil) then
      enemyCount = enemies:count()
    end
    if level == 1 then
      -- 敵が1体もいなくなったらモンスター生成
      if enemyCount == 0 then
        enemyManager:popEnemyAt("T_slime30", 3, 1)
      end
    elseif level == 2 then
      if enemyCount == 0 then
        enemyManager:popEnemyAt("T_flower", 5, 1)
      end
    elseif level == 3 then
      if enemyCount == 0 then
        local killedEnemyCount = self.__IRegister__:getRegister("enemyCount", 0)
        local enemies = {"T_leaf", "T_ginet", "T_flower", "T_tnt", "T_slime30"}
        if killedEnemyCount > 4 then
          enemyManager:popEnemyAt("T_slime30", 5, 1)
        else
          enemyManager:popEnemyAt(enemies[killedEnemyCount + 1], 4, 1)
        end
        self.__IRegister__:setRegister("enemyCount", killedEnemyCount + 1)
      end
      if characterManager:getHP() < preHP then -- ダメージ受けた
        local popup = layer:addPopupWindow(1)
        popup:setText(0, "ぶつかるとダメージ！", [[ぎゃあん！！倒しきれなくて、敵にぶつかっちゃうと
        自分の体力（HP）が減っちゃうの！体力（HP）が0になるとゲームオーバーで、そのステージからやり直しになっちゃうから気を付けてね！]])
      end
    elseif level == 4 then
      local lastSkill = characterManager:getLastSkill()
      local runCount = self.__IRegister__:getRegister("runCount", 0)
      if lastSkill and lastSkill:getIdentifier() == "run" then -- 前に使った技がrunの時
        runCount = runCount + 1
        self.__IRegister__:setRegister("runCount", runCount)
      end
      if runCount >= 2 and enemyManager:getEnemies():count() == 0 then -- 走り行動を2回行っていたとき、かつ敵がいないとき
        enemyManager:popEnemyAt("T_slime12", 3, 1)  
      end
    elseif level == 5 then
      if enemyCount == 0 then
        local killedEnemyCount = self.__IRegister__:getRegister("enemyCount", 0)
        local enemies = {"T_slime12", "T_ginet", "T_flower",}
        if killedEnemyCount >= 3 then
          enemyManager:popEnemyAt("T_slime30", 5, 1)
        else
          enemyManager:popEnemyAt(enemies[killedEnemyCount + 1], 4, 1)
        end
        self.__IRegister__:setRegister("enemyCount", killedEnemyCount + 1)
      end
    elseif level == 6 then
      local killedEnemyCount = self.__IRegister__:getRegister("enemyCount", 0)
      if killedEnemyCount > 0 then -- 1体目倒したあと、雑魚を毎ターン生成。次のレベル用に溜めておく
        enemyManager:popEnemyAt("T_moth", MAX_ROW - 1, enemyCount % 3)
      end
      if enemyCount == 0 then
        enemyManager:popEnemyAt("T_tetufez", 5, 1)
        self.__IRegister__:setRegister("enemyCount", killedEnemyCount + 1)
      end
    elseif level == 7 then
      local isAnnihilation = self.__IRegister__:getBool("isAnnihiration")
      if isAnnihilation and enemyCount == 0 then
        enemyManager:popEnemyAt("T_moth7", MAX_ROW - 1, enemyCount % 3) -- 全滅済みなら毎ターン雑魚を後ろに出す
      end
      if enemyCount == 0 then
        if not isAnnihilation then
          self.__IRegister__:setBool("isAnnihiration", true) -- 最初からいる敵が全滅した
          local popup = layer:addPopupWindow(1)
          popup:setText(0, "『オクススラッシュ』炸裂！！", [[
やったね、オクス！一度にたくさんの敵を倒すことができたよ！
でも、『オクススラッシュ』の攻撃範囲は一番手前の敵から後ろ4列の敵まで。
だから、あんまり後ろにいる敵には攻撃が届かないから要注意だね
          ]])
          enemyManager:popEnemyAt("T_moth7", 2, 0)
          enemyManager:popEnemyAt("T_moth7", 2, 1)
          enemyManager:popEnemyAt("T_moth7", 2, 2)
          enemyManager:popEnemyAt("T_moth7", MAX_ROW - 1, 0)
          enemyManager:popEnemyAt("T_moth7", MAX_ROW - 1, 1)
          enemyManager:popEnemyAt("T_moth7", MAX_ROW - 1, 2)
        end
      end
    elseif level == 8 then
      local maxHP = characterManager:getMaxHP()
      local enemies = enemyManager:getEnemies()
      local popup = layer:getPopupWindow()
      local enemyCount = enemies:count()
      local lastSkill = characterManager:getLastSkill()
      if enemyCount == 0 then --敵がいなくて、
        if lastSkill:getIdentifier() == "shield" then --前回が盾の時
          enemyManager:popEnemyAt("acorn1A0",5,1)
        else --前回が盾でない時
          enemyManager:popEnemyAt("moth2A0",5,1)
        end
      end
      if characterManager:getHP() <= maxHP then
        characterManager:addHP(maxHP) --ダメージを受けているはずなので全快させる
      end
    end
    self.__IRegister__:setRegister("preHP", characterManager:getHP())
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    self.__IRegister__:clearRegister()
    local level = characterManager:getLevel()
    local layer = EffectLayer:sharedLayer()
    if level == 1 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "さあ！たたかいの始まりだ！", [[
私はラスカ！オクス（あなた）のパートナー！
これからこのゲームについて説明していくよ！

タイトルで少しの間待っているとストーリーの
デモも流れるのでそちらもよろしくね！
]])
      popup:setText(1, "コレってどんなゲーム？", 
      [[
このゲームは、画面奥から自分に向かって近づいて
くるモンスターをやっつけていくゲームよ。

音楽が気持ちいいから、
音量を上げてノリノリでプレイしてみてね。]])
      popup:setText(2, "音楽にあわせて行動しよう！", [[
下にあるタイムマーカーが一周するごとに、
あなたは自分で選んだ行動（ワザ）をするわ。

まずは 剣 のマークをタッチして
『アタック』 のこうげきワザを試しましょ！]])
    elseif level == 2 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "レベルアップで強くなろう！", 
[[
そう！こんなカンジでモンスターをどんどん倒して
いくと、今みたいに 『レベルアップ』 するよ！

さらに、１０レベルごとに次のステージに行けるよ！
３０レベルまでたどり着くとゲームクリアだよ！！]])
      popup:setText(1, 
"こうげきは、近くの敵から", 
[[
あとね。こうげきは基本的に一番近くの敵に
当たるよ。モンスターの上にマーカーも表示
されるから、さんこうにしてね！

モンスターが現われたら、バシバシ攻撃して
どんどんやっつけていこう！]]
)
      popup:setText(2, 
"『連続こうげき』してみよう！", 
[[
ちなみに 『アタック』 は、連続してくりだすことで
『連続こうげき』になるよ！

『連続こうげき』することで攻撃力と音楽が変化
するよ！気持ちイイのでぜひ試してみてね！
]]
)
    elseif level == 3 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "モンスターの色", 
[[
さっきモンスターをこうげきしてた時、モンスターの
色が変わっていったことには気付いたかな？　

そう！モンスターの体力は色でわかるんだ！
あいての顔色をよく観察することがたいせつよ！
]])
    elseif level == 4 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "新しい（コマンド）！", 
[[
レベルアップすると新しい行動（ワザ）を
おぼえることがあるよ！やったね！

どんどんレベルを上げて、新しいワザを身につけよう！
そして、おぼえたワザはさっそく試してみよう！
]])
      popup:setText(1, "せめこめ！『ダッシュ』", 
[[
今回できるようになったワザは『ダッシュ』！
モンスターとの距離をちぢめることができるよ！

モンスターが遠くて見えないときには
ダッシュ のマークにタッチして近づいてみよう！
]])
    elseif level == 5 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "溜めよう！『パワーチャージ』！", 
[[
お！『パワーチャージ』を覚えたね！これは重要だよー。『パワーチャージ』コマンドをタッチすると文字通り『パワー』を溜めることができるんだ。『パワー』をチャージすると次の行動（コマンド）の効果がアップ！『攻撃』なら、ふつうだと3回攻撃しないと倒せない敵でも１回で倒せたりするよ！
]])
      popup:setText(1, "『パワーチャージ』を使いこなせ！", [[
ただ、『パワー』は、チャージした後に1度行動するとすぐ使い切っちゃうから要注意。敵の色から相手の強さをよーく見極めて、普通に攻撃を重ねるか、『パワーチャージ』で強力な一撃をかますか、状況を上手に把握して使い分けていこう！
]])
    elseif level == 6 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "最大『パワー』で渾身の一撃！", [[
気づいたかもしれないけど、実は『パワー』は最大4回まで溜めることができるんだ。溜めれば溜めるほど次に放つ行動（コマンド）の効果がアップしていくよ！余裕を作って溜めまくって、体力の高い敵も一撃で粉砕だー！！
]])
    elseif level == 7 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "敵を一掃！必殺『オクススラッシュ』！！", [[
わ！固い敵に手間取っていたらいつの間にか目の前が敵で一杯に！　でも大丈夫。こんな時こそ必殺の『オクススラッシュ』！！

『オクススラッシュ』は強力だから『パワー』が1段階以上溜まっていないと放てないけれど、複数の敵を同時に攻撃できる強力な技だよ！

敵の軍団も一気に一掃しちゃおう！
]])
    elseif level == 8 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "ピンチのときは『ガード』でしのごう", [[
んん！？あの敵はオクスの剣だと攻撃が全く通らないやつだ！　私なら何とか出来るけど、今はとりあえず『ガード』で防ごうか。『ガード』コマンドをタッチすると、盾を構えて『ガード』状態になるよ。

よし！防げた！『ガード』状態なら敵とぶつかってもダメージは0で済むからへっちゃらだよ！『ガード』は敵の攻撃を防ぐか、他の行動をとると解除されちゃうから気を付けて！　

『ガード』は無敵で強力だけど、わたしたちの手前で立ち止まっちゃう敵には意味ないし、『ガード』で敵を防いでばっかりだと、いつまでもレベル上がらないからほどほどにね。
]])
    elseif level == 9 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "ノックバックで器用に戦え", [[
今取得した技はオクス君の専用技、ノックバックだよ！敵が目の前まで迫ってきてしまったらば、これで一番奥まで吹っ飛ばして距離を取ってしまおう！倒しきれなかったらとりあえず遠くに飛ばして、次来るまでには倒してしまおう。他にも、一番近い敵を代えるのに使えたりと、色々応用の利くテクニック技だよ！
]])
    elseif level == 10 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "免許皆伝！？", [[
これでオクス君は戦い方を一通りマスター出来たはずよ！あとはちょっとココで練習してから、ポーズボタンにタッチしてチュートリアルを抜けてね。そしたら、目指せグランエターナ！平和への戦いへ挑みに行こう！
]])
      popup:setText(1, "免許皆伝！？", [[
…
……
…………といいたいけれど、もうちょっとだけ続くんじゃ。
オクスクロニクルの真の主役は実は私、ラスカなのよ。前作オクスクエストから1年くらい、続編の今作はキャラチェンジシステムが最大の目玉！！そもそもまだ説明していないコマンドが残ってるじゃない。「キャラチェンジシステムとはいったいなんなのか！そしてオクスを待ち受けるさらなる試練とは！！……to be continued.」
]])
    --if get == nil then
    
    local data = SaveData:sharedData()
    data:unlockAchievement("clearTutorialA")
    
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
