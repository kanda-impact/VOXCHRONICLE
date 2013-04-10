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
        popup:setText(0, "ダッシュは計画的に", [[
あ、見てみて！モンスターが見えてきたよ。

急いでいるときには便利だけど、モンスターの
いないうちにこうげき準備していた方が良いこと
も多いから、ご利用は計画的に．．．ね？
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
        popup:setText(0, "ぶつかるとダメージ！", [[
ぎゃあん！いったーい！！
モンスターを倒しきれなくてぶつかっちゃうと
わたしたちの体力（HP）がへっちゃうの！

体力（HP）が0になるとゲームオーバー。
やり直しになっちゃうから気をつけてね！]])
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
やったね、オクス！一度にたくさんのモンスターを
倒すことができたよ！

でも、『オクススラッシュ』のこうげきは、
いちばん手前のモンスターから後ろ4列分まで
しか届かないから、注意してね！
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
くるモンスターを倒していくゲームよ。

音楽が気持ちいいから、
音量を上げてノリノリでプレイしてみてね。]])
      popup:setText(2, "音楽にあわせて行動しよう！", [[
下にあるタイムマーカーが一周するごとに、
あなたは自分で選んだ行動（ワザ）をするわ。

まずは 剣 のマークをタッチして
『アタック』 のワザを試しましょ！]])
    elseif level == 2 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "レベルアップで強くなろう！", 
[[
そう！こんなカンジでモンスターをどんどん倒して
いくと、今みたいに 『レベルアップ』 するよ！

１０レベルごとに次のステージに行けるんだ！
３０レベルまでたどり着くとゲームクリアだよ！！]])
      popup:setText(1, 
"こうげきは、近くの敵から", 
[[
あとね。こうげきは基本的に一番近くの敵に当た
るよ。モンスターの上にマーカーも表示される
から、さんこうにしてね！

モンスターが現われたら、バシバシ攻撃して
どんどんやっつけていこう！]]
)
      popup:setText(2, 
"『連続こうげき』してみよう！", 
[[
ちなみに 『アタック』 は、連続してだすことで
『連続こうげき』になるよ！

『連続こうげき』することで攻撃力と音楽が変化
するよ！気持ちイイのでぜひ試してみてね！
]]
)
    elseif level == 3 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "モンスターの色", 
[[
モンスターをこうげきしてた時、モンスターの
色が変わっていったことには気づいたかな？　

そう！モンスターの体力は色でわかるんだ！
あいての顔色をよくカンサツすることが大切よ！
]])
    elseif level == 4 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "新しい行動（ワザ）！", 
[[
レベルアップすると新しい行動（ワザ）をおぼえる
ことがあるよ！やったね！

どんどんレベル上げて、新しいワザをおぼえよう！
そして、おぼえたワザはさっそく試してみよう！
]])
      popup:setText(1, "攻めこめ！『ダッシュ』", 
[[
今回できるようになったワザは『ダッシュ』！
モンスターとのキョリをちぢめることができるよ！

モンスターが遠くて見えないときには
ダッシュ のマークにタッチして近づいてみよう！
]])
    elseif level == 5 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "ためよう！『パワーチャージ』！", 
[[
『パワーチャージ』おぼえたね！これは大事だよー

パワーチャージ マークをタッチすると文字通り
 『パワー』 をためることができるんだ。
]])
      popup:setText(1, "ためよう！『パワーチャージ』！", 
[[
『パワー』 をためると次のワザの効果がアップ！

『アタック』なら、3回攻撃しないと倒せない
モンスターも１回で倒せちゃったりするよ！
]])
      popup:setText(2, "『パワー』は使いきり！", [[
でもね『パワー』 は、ワザを使うと、すぐに
使いきっちゃうから気を付けて！

モンスターの強さをよーくみきわめて、そのまま
たたかうか、『パワーチャージ』で強力な一撃にするか
状況をじょうずに判断して使いわけていこう！
]])
    elseif level == 6 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "最大『パワー』ですごい一撃", [[
気づいたかもしれないけど、じつは『パワー』は
4回までためることができるんだ。

ためればためるほど、次に使うワザの効果がアップ
していくよ！余裕をつくってためまくって、
体力の高いモンスターも一撃で倒そう！！
]])
    elseif level == 7 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "必殺『オクススラッシュ』！", [[
わ！モンスター倒すのに時間かかってたら、
いつの間にか目の前がモンスターでいっぱい！

でも大丈夫！こんな時こそ
必殺の『オクススラッシュ』！！]])
      popup:setText(1, "必殺『オクススラッシュ』！", [[
『オクススラッシュ』は複数のモンスターを
同時にこうげきできる強力なワザだよ！

強力だから、『パワー』が1回以上たまって
いないと使えないけれど、モンスターの軍団も
一気に倒すことができちゃうよ！
]])
    elseif level == 8 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "ピンチのときは『ガード』", [[
んん！？あの敵はオクスの『アタック』がきかない
やつだね。私なら何とか出来るけど、今は
とりあえず『ガード』で防ごうか。

『ガード』のワザは 盾 のマークをタッチ！
盾を構えて『ガード』状態になるよ。]])

local popup = layer:addPopupWindow(2)--ＴＡＷＡＳＩ「盾で防げたらの条件を追加してちょ」
      popup:setText(0, "『ガード』の注意点", [[
よし！防げた！『ガード』状態はモンスターの
どんなこうげきも防ぐことができるよ！

でも『ガード』状態はモンスターのこうげきを防ぐか
ほかの行動をとると解除されちゃうから気をつけて！　
]])
popup:setText(1, "『ガード』の注意点", [[
あと『ガード』は無敵になれるけど、こうげきを
防いだあとすぐに、もういちど『ガード』する
ことはできないから、タイミングを考えようね。

モンスターの中には、わたしたちにぶつからないで
手前で立ち止まっちゃう奴とかもいるしね！
]])
    elseif level == 9 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "特殊ワザ『ノックバック』", [[
今おぼえたワザは、オクス専用のワザ
『ノックバック』だよ！
たつまきマークをタッチして使おう。

『ノックバック』はモンスターを１匹、後ろに
ふっとばすことができるんだ。使いドコロが
難しいけど、使いこなすと戦いが楽になるよ
]])
    elseif level == 10 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "免許皆伝！？", [[
これでオクス君の戦い方は一通りマスター
出来たはずよ！あとは練習に満足したら、
『ポーズ』ボタンにタッチして
チュートリアルを終わってね。
]])
      popup:setText(1, "免許皆伝！？", [[
ああ！でもちょっとまって！まだ大事なワザを
説明してないじゃない！今作の目玉なのに！

このゲーム真の主役、私、ラスカへの
『キャラチェンジ』については次の『レッスン２』
でしっかりレクチャーするわ！
じゃ、次回もよろしくね！バイバイ！
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
