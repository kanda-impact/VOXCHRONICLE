Map = {
  name = "Lesson1",
  wayMusic = "chabo",
  bossMusic = "",
  backgroundImage = "simple_background.png",
  skin = "skinA",
  ending = "",
  nextMaps = {},
  initialLevel = 4,
  maxLevel = 10,
  getEnemyTable = function(level)
    return {}
  end,
  onFinishPlaying = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    local enemies = enemyManager:getEnemies()
    local enemyCount = 0
    if not (enemies == nil) then
      enemyCount = enemies:count()
    end
    if level == 1 or level == 2 then
      -- 敵が1体もいなくなったらモンスター生成
      if enemyCount == 0 then
        enemyManager:popEnemyAt("slime0", MAX_ROW - 1, 1)
      end
    elseif level == 3 then
      if enemyCount == 0 then
        local killedEnemyCount = self.__IRegister__:getRegister("enemyCount", 0)
        -- if killedEnemyCount == 0 then
        -- end
        enemyManager:popEnemyAt("slime0", MAX_ROW - 1, 1)
        self.__IRegister__:setRegister("enemyCount", killedEnemyCount + 1)
      end
    elseif level == 4 then
      local lastSkill = characterManager:getLastSkill()
      local runCount = self.__IRegister__:getRegister("runCount", 0)
      if lastSkill and lastSkill:getIdentifier() == "run" then -- 前に使った技がrunの時
        self.__IRegister__:setRegister("runCount", runCount + 1)
      end
      if runCount > 2 then -- 走り行動を3回以上行っていたとき
        enemyManager:popEnemyAt("slime0", MAX_ROW - 1, 1)
      end
    end
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    local layer = EffectLayer:sharedLayer()
    if level == 1 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "さあ！戦いの始まりだ！", [[
やあやあ！私はラスカ。オクス君（あなた）のパートナーよ。細かい説明は省くけど、これからゲームについて説明していくよ。タイトルで少しの間待っているとストーリーのデモが流れるのでそちらも宜しくね！
]])
      popup:setText(1, "オクスってどんなゲーム？", [[
オクスクロニクルは主観視点、画面奥から自分に近づいてくる敵をやっつけていくゲームよ。音量を上げてノリノリでプレイしてみてね。下にあるタイムマーカーが一周する毎に選択していたコマンドが行われるわ。まずは剣のマークをタッチして攻撃コマンドを試してみましょ。
]])
    elseif level == 2 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "レベルアップで次のステージ！", [[
こんな調子で敵をどんどん倒していくと今みたいにレベルアップするよ！レベルが30になればステージクリア。ちなみに攻撃は一番近くの敵に当たるから、「近づく敵は全て切る！」って感じにどんどん倒していっちゃおう！ちなみに連続で攻撃していると、4連撃までは攻撃力が上がっていくよ。サービスサービスぅ！
]])
    elseif level == 3 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "敵の体力は色で判断！", [[
さっきの敵はなかなか倒れなかったけれど、体の色が違ったことには気付いたかな？　敵の残り体力があとどのくらいかっていうのは敵の色で分かるんだ！攻撃する前には敵の顔色はよ～くうかがっておこう！
]])
      popup:setText(1, "ぶつかるとダメージ！", [[
迫ってくる敵は倒しきれないとオクス君にぶつかっちゃうよ！ぶつかると自分の体力（HP）が減っちゃうから気をつけて！HPが0になるとゲームオーバーだからね。そのステージからやり直しだよ！
]])
    elseif level == 4 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "レベルアップで能力解禁！", [[
おおっと！今のレベルアップで新しい行動ができるようになったよ！！やるねぇオクス君、成長期だ！どんどんレベルを上げて新しいワザ、身につけよう！
]])
      popup:setText(1, "ダッシュでどんどん攻め込もう！", [[
今回出来るようになったのはダッシュ！ダッシュコマンドにタッチして敵にどんどん近づいてみよう。敵がまだ見えてこないで暇なときは、ダッシュして近づいて攻撃しよう。うっかりダッシュしすぎると敵がすぐ目の前でどうしようなんてなっちゃうから、最初のうちは焦らずにゆったり構えている方がいいかもね。
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
      うわぁ！固い敵に手間取っていたらいつの間にか目の前が敵で一杯だよ！　でも大丈夫。こんな時は必殺オクススラッシュ！！　オクススラッシュコマンドはテンションが1段階以上溜まっていないと放てないけれど、一番手前から後ろ4列の敵まで一度に攻撃できる協力な範囲攻撃技だよ！敵の軍団も一気に一掃してしちゃおう！
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
