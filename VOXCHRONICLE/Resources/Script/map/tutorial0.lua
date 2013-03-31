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
        popup:setText(0, "ぶつかるとダメージ！", [[迫ってくる敵は倒しきれないとオクス君にぶつかっちゃうよ！
        ぶつかると自分の体力（HP）が減っちゃうから気をつけて！HPが0になるとゲームオーバーだからね。そのステージからやり直しだよ！]])
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
          popup:setText(0, "炸裂、オクスラッシュ！", [[
やったね！オクス。一度にたくさんの敵を攻撃できたよ
オクススラッシュの攻撃範囲は一番手前の敵から後ろ4列の敵まで
あんまり後ろにいる敵には攻撃が届かないから要注意だね
          ]])
          enemyManager:popEnemyAt("T_moth7", 2, 0)
          enemyManager:popEnemyAt("T_moth7", 2, 1)
          enemyManager:popEnemyAt("T_moth7", 2, 2)
          enemyManager:popEnemyAt("T_moth7", MAX_ROW - 1, 0)
          enemyManager:popEnemyAt("T_moth7", MAX_ROW - 1, 1)
          enemyManager:popEnemyAt("T_moth7", MAX_ROW - 1, 2)
        end
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
      popup:setText(0, "さあ！戦いの始まりだ！", [[
やあやあ！私はラスカ。オクス君（あなた）のパートナーよ。細かい説明は省くけど、これからゲームについて説明していくよ。タイトルで少しの間待っているとストーリーのデモが流れるのでそちらも宜しくね！
]])
      popup:setText(1, "オクスってどんなゲーム？", "オクスクロニクルは主観視点、画面奥から自分に近づいてくる敵をやっつけていくゲームよ。音量を上げてノリノリでプレイしてみてね。")
      popup:setText(2, "音楽に合わせて行動しよう！", "下にあるタイムマーカーが一周する毎に選択していたコマンドが行われるわ。まずは剣のマークをタッチして攻撃コマンドを試してみましょ。")
    elseif level == 2 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "レベルアップで次のステージ！", "こんな調子で敵をどんどん倒していくと今みたいにレベルアップするよ！レベルが30になればステージクリア")
      popup:setText(1, "近くの敵を狙い撃ち", "攻撃は一番近くの敵に当たるから、「近づく敵は全て切る！」って感じにどんどん倒していっちゃおう！")
      popup:setText(2, "攻撃を繋げて威力アップ！", "ちなみに連続で攻撃していると、4連撃までは攻撃力が上がっていくよ。サービスサービスぅ！")
    elseif level == 3 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "敵の体力は色で判断！", [[
さっきの敵はなかなか倒れなかったけれど、体の色が違ったことには気付いたかな？　敵の残り体力があとどのくらいかっていうのは敵の色で分かるんだ！攻撃する前には敵の顔色はよ～くうかがっておこう！
]])
    elseif level == 4 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "レベルアップで能力解禁！", [[
おおっと！今のレベルアップで新しい行動ができるようになったよ！！やるねぇオクス君、成長期だ！どんどんレベルを上げて新しいワザ、身につけよう！
]])
      popup:setText(1, "ダッシュでどんどん攻め込もう！", [[
今回出来るようになったのはダッシュ！ダッシュコマンドにタッチして敵にどんどん近づいてみよう。敵がまだ見えてこないで暇なときは、ダッシュして近づいて攻撃しよう。
]])
    elseif level == 5 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "テンションチャージで強力な一撃！", [[
今度はテンションチャージが出来るようになったよ！テンションコマンドをタッチするとテンションを溜めることができるよ。テンションが溜まってると攻撃の威力がパワーアップ！通常だと3度も攻撃しないと倒せない敵でも1発で倒せるよ。
]])
      popup:setText(1, "テンションを使いこなせ！", [[
ただし、テンションは溜めた後に1度行動すると溜めたテンションが消費されちゃうから要注意。敵の色をよーく見極めて、通常攻撃で連撃していくか、テンション溜めて強力な一撃をかますか、状況を上手く把握して使い分けていこう！
]])
    elseif level == 6 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "テンションMAXで渾身の一撃！", [[
テンションは実は4段階まで溜めることができるんだ。溜めれば溜めるほど次に放つ一撃の威力がアップしていくよ。テンションを溜めて溜めて溜めまくって、体力の高い敵も一撃で粉砕だ！テンション溜めてる間に敵が近づいてハラハラするけど、その分一気に反撃しちゃえ！！
]])
    elseif level == 7 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "敵を一掃！必殺オクススラッシュ！！", [[
うわぁ！固い敵に手間取っていたらいつの間にか目の前が敵で一杯だよ！　でも大丈夫。こんな時は必殺オクススラッシュ！！

オクススラッシュはテンションが1段階以上溜まっていないと放てないけれど、複数の敵を同時に攻撃できる強力な技だよ

敵の軍団も一気に一掃しちゃおう！
]])
    elseif level == 8 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "ピンチのときはガードでしのごう", [[
あ、次来る敵はオクス君の剣では攻撃が全く通らないやつだ！　私なら何とか出来るんだけれども、オクス君はとりあえずガードで対応しといてね。ガードコマンドをタッチすると、ガード状態になるよ。ガード状態なら敵とぶつかってもダメージは0で済むからへっちゃらだよ。ガードで無効化するか他のコマンドをタッチするかするとガード状態は解かれるから気をつけて！　ガードで敵の攻撃をずっと無効化し続けるっていうのは出来ないから要所要所で使ってね。
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
    end
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
  }
}
