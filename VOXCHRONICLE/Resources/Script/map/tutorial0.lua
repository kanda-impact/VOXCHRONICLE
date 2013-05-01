Map = {
  name = "Lesson1",
  wayMusic = "chabo",
  bossMusic = "",
  backgroundImage = "tutorial_background.png",
  skin = "skinA",
  ending = "",
  nextMaps = {},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level == 10 then
      return {T_moth = 3, T_flower = 1, T_ginet = 1, T_leaf = 1, T_geek = 1}
    end
    return {}
  end,
  onFinishPlaying = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 10 then
      characterManager:setExp(characterManager:getExpWithLevel(10))
    end
    local layer = EffectLayer:sharedLayer()
    if level == 4 then
      local popuped = self.__IRegister__:getBool("popuped") -- ポップアップしたかフラグ
      if enemyManager:getEnemies():count() == 1 and not popuped then
        local enemy = enemyManager:getEnemies():lastObject() -- モンスター取り出す
        if enemy:getRow() < 5 then
          self.__IRegister__:setBool("popuped", true)
          -- 前の裏拍で敵が出現したあと、ポップアップを出します
          local popup = layer:addPopupWindow(1)
          popup:setText(0, "ダッシュは計画的に", [[
あ、見てみて！モンスターが見えてきたよ。

急いでいるときには便利だけど、モンスターの
いないうちにこうげき準備していた方が良いこと
も多いから、ご利用は計画的に･･････ね？
        ]])
        end
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
        local enemy = enemyManager:popEnemyAt("T_slime30", 3, 1)
        enemy:setExp(30)
      end
    elseif level == 2 then
      if enemyCount == 0 then
        local enemy = enemyManager:popEnemyAt("T_flower", 5, 1)
        enemy:setExp(30)
      end
    elseif level == 3 then
      if enemyCount == 0 then
        local killedEnemyCount = self.__IRegister__:getRegister("enemyCount", 0)
        local enemies = {"T_leaf", "T_ginet", "T_tnt", "T_slime30"}
        local attacks = {0, 0, 1, 0}
        local exps = {0, 0, 0, 60}
        local index = math.min(killedEnemyCount + 1, 4)
        local enemy = enemyManager:popEnemyAt(enemies[index], 3, 1)
        enemy:setAttack(attacks[index])
        enemy:setExp(exps[index])
        self.__IRegister__:setRegister("enemyCount", killedEnemyCount + 1)
      end
      local popuped = self.__IRegister__:getBool("popuped") -- ポップアップしたかフラグ
      if characterManager:getHP() < preHP and not popuped then -- ダメージ受けた
        local popup = layer:addPopupWindow(1)
        popup:setText(0, "ぶつかるとダメージ！", [[
ぎゃあん！いったーい！！
モンスターを倒しきれなくてぶつかっちゃうと
わたしたちの体力(HP)がへっちゃうの！

体力(HP)が0になるとゲームオーバー。
やり直しになっちゃうから気をつけてね！]])
      popup:addImage(0, "tutorial3_2.png")
        self.__IRegister__:setBool('popuped', true)
      end
    elseif level == 4 then
      local lastSkill = characterManager:getLastSkill()
      local runCount = self.__IRegister__:getRegister("runCount", 0)
      if lastSkill and lastSkill:getIdentifier() == "run" then -- 前に使った技がrunの時
        if enemyManager:getEnemies():count() == 0 then -- 敵がいないとき
          local enemy = enemyManager:popEnemyAt("T_moth", 5, 1)
          enemy:setMaxHP(18)
          enemy:setExp(60)
        end
      end
    elseif level == 5 then
      if enemyCount == 0 then
        local killedEnemyCount = self.__IRegister__:getRegister("enemyCount", 0)
        local enemies = {"T_ginet", "T_flower"}
        local index = math.min(killedEnemyCount + 1, 2)
        local enemy = enemyManager:popEnemyAt(enemies[index], 5, 1)
        enemy:setAttack(0)
        if index == 2 then
          enemy:setExp(60)
        else
          enemy:setExp(0)
        end
        enemy:setAttack(0)
        self.__IRegister__:setRegister("enemyCount", killedEnemyCount + 1)
      end
    elseif level == 6 then
      local killedEnemyCount = self.__IRegister__:getRegister("enemyCount", 0)
      if killedEnemyCount > 0 then -- 1体目倒したあと、雑魚を毎ターン生成。次のレベル用に溜めておく
        local enemy = enemyManager:popEnemyAt("T_moth", MAX_ROW - 1, enemyCount % 3)
        enemy:setExp(0)
      end
      if enemyCount == 0 then
        local enemy = enemyManager:popEnemyAt("T_tetufez", 5, 1)
        enemy:setExp(60)
        self.__IRegister__:setRegister("enemyCount", killedEnemyCount + 1)
      end
    elseif level == 7 then
      local isAnnihilation = self.__IRegister__:getBool("isAnnihiration")
      if isAnnihilation and enemyCount == 0 then
        local enemy = enemyManager:popEnemyAt("T_moth", MAX_ROW - 1, enemyCount % 3) -- 全滅済みなら毎ターン雑魚を後ろに出す
        enemy:setExp(10)
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
          enemyManager:popEnemyAt("T_moth7", 1, 0):setExp(10)
          enemyManager:popEnemyAt("T_moth7", 1, 1):setExp(10)
          enemyManager:popEnemyAt("T_moth7", 1, 2):setExp(10)
          enemyManager:popEnemyAt("T_moth7", MAX_ROW - 1, 0):setExp(10)
          enemyManager:popEnemyAt("T_moth7", MAX_ROW - 1, 1):setExp(10)
          enemyManager:popEnemyAt("T_moth7", MAX_ROW - 1, 2):setExp(10)
        end
      end
    elseif level == 8 then
      local maxHP = characterManager:getMaxHP()
      local enemies = enemyManager:getEnemies()
      local popup = layer:getPopupWindow()
      local enemyCount = enemies:count()
      local lastSkill = characterManager:getLastSkill()
      local isShield = self.__IRegister__:getBool("lastShieldState")
      local popuped = self.__IRegister__:getBool("popuped") -- ポップアップしたかフラグ
      if enemyCount == 0 then --敵がいなくて、
        if popuped then -- ポップアップ後
          if isShield then
            local popup = layer:addPopupWindow(1) --2回目も盾で防いだら隠しメッセージ
            popup:setText(0, "『ガード』の使いすぎ注意", [[
盾で防ぐのは倒しきれないモンスターだけ
のほうがよいわよ。

敵を盾で防いでばかりだと、レベルが上がらず先に進めないからどんどん倒して先に進んでいって
]])
          end
          local slime = enemyManager:popEnemyAt("T_slime60",5,1) -- スライム再生成
          slime:setExp(60)
        else -- ポップアップ前
          if isShield or (characterManager:getLastSkill() and characterManager:getLastSkill():getIdentifier() == "shield") then --前に盾状態だったら
            self.__IRegister__:setBool("popuped", true) -- ポップアップフラグ立てる
            local popup = layer:addPopupWindow(2)--ＴＡＷＡＳＩ「盾で防げたらの条件を追加してちょ」
            popup:setText(0, "『ガード』の注意点", [[
よし！防げた！『ガード』状態はモンスターの
どんなこうげきも防ぐことができるよ！

でも『ガード』じょうたいはモンスターのこうげきを防ぐか、ほかの行動をとると解除されちゃうから気をつけて！　
]])
            popup:setText(1, "『ガード』の注意点", [[
あと『ガード』は無敵になれるけど、こうげきを
防いだあとすぐに、もういちど『ガード』する
ことはできないから、タイミングを考えようね。
]])
            enemyManager:popEnemyAt("T_slime60",5,1)
          else --前に使ったスキルが盾でない時
            local popup = layer:addPopupWindow(1)
            popup:setText(0, "ピンチのときは『ガード』", [[
失敗しちゃったね
『ガード』のワザは 盾 のマークをタッチ！
使ってからこうげきを食らうまでは、
落ち着いて相手が来るのを待ってみて

回復してあげるからもう一回頑張ってね
]])
            popup:addImage(0, "tutorial8_1.png")
            local enemy = enemyManager:popEnemyAt("T_tnt", 3, 1) -- 盾持ちを生成すると混同しちゃうからHPの高いヤツを出す
            enemy:setExp(0)
            local maxHP = characterManager:getMaxHP()
            if characterManager:getHP() <= maxHP then
              characterManager:addHP(maxHP) -- ダメージを受けているはずなので全快させる
            end
          end
        end
      end
      self.__IRegister__:setBool("lastShieldState", characterManager:getShield())
    elseif level == 9 then

      local poped = self.__IRegister__:getBool("knockbackPoped")
      if enemyCount == 0 and poped then -- ポップアップ後
        local popup = layer:addPopupWindow(1)
        popup:setText(0, "特殊ワザ『ノックバック』", [[
オクス！倒しきれない体力の高いモンスターには
『ノックバック』を使ってみて
このワザは敵を遠くまで吹き飛ばせちゃうの

上手く使って体力の高い奴もやっつけちゃえ！
]])
            popup:addImage(0, "tutorial9_1.png")
        local enemy = enemyManager:popEnemyAt("T_tnt9", 4, 1)
        enemy:setExp(60)
        enemy:setHP(25)
        local maxHP = characterManager:getMaxHP()
        if characterManager:getHP() <= maxHP then
          characterManager:addHP(maxHP) -- ダメージを受けているはずなので全快させる
        end
        characterManager:addTension(-characterManager:getTension()) -- 萎えさせる
      end
    elseif level == 10 then
    -- 10面は特に何もしない
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
オクスクロニクルの世界へようこそ！！
私はラスカ！オクス（あなた）のパートナー！
これからこのゲームについて説明していくよ！

タイトルで少しの間待っているとストーリーの
デモも流れるのでそちらもよろしくね！
]])
      popup:setText(1, "コレってどんなゲーム？",
      [[
近づいてくるモンスターを倒しながら画面奥にどんどん進んでいくゲームよ。

自分の行動に合わせて音楽が変わるのが
このゲーム最大のウリなので、ぜひ音量を上げて
ノリノリでプレイしてみてね。]])
      popup:addImage(1, "tutorial1_2.png")
      popup:setText(2, "音楽にあわせて行動しよう！", [[
行動するときは画面下左右のワザアイコンをタッチ！タイムマーカーが一周するごとにワザが実行されるわ。

行動（ワザ）は先にえらんでおいて大丈夫よ！
まずは 剣 のマークをタッチして『アタック』 を
試しましょ！]])
      popup:addImage(2, "tutorial1_3.png")
    elseif level == 2 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "レベルアップで強くなろう！",
      [[
そう！こんなカンジでモンスターをどんどん倒して
いくと、今みたいに 『レベルアップ』 するよ！

10レベルごとに次のステージに行けるんだ！
30レベルまでたどり着くとゲームクリアだよ！！]])
      popup:addImage(0, "tutorial2_1.png")
      popup:setText(1,
      "こうげきは、近くの敵から",
      [[
あとね。こうげきは基本的に一番近くの敵に当た
るよ。モンスターの上にマーカーも表示される
から、さんこうにしてね！

モンスターが現われたら、バシバシ攻撃して
どんどんやっつけていこう！]])
      popup:addImage(1, "tutorial2_2.png")
      popup:setText(2,
      "『連続こうげき』してみよう！",
      [[
ちなみに 『アタック』 は、連続してだすことで
『連続こうげき』になるよ！

『連続こうげき』することで攻撃力と音楽が変化
するよ！気持ちイイのでぜひ試してみてね！
]])
      popup:addImage(2, "tutorial2_3.png")
    elseif level == 3 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "モンスターの色",
      [[
モンスターをこうげきしてた時、モンスターの
色が変わっていったことには気づいたかな？　

そう！モンスターの体力は色でわかるんだ！
あいての顔色をよくカンサツすることが大切よ！
]])
      popup:addImage(0, "tutorial3_1.png")
    elseif level == 4 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "新しい行動（ワザ）！",
      [[
レベルアップすると新しい行動（ワザ）をおぼえる
ことがあるよ！やったね！

どんどんレベル上げて、新しいワザをおぼえよう！
そして、おぼえたワザはさっそく試してみよう！
]])
      popup:addImage(0, "tutorial4_1.png")
      popup:setText(1, "攻めこめ！『ダッシュ』",
      [[
今回できるようになったワザは『ダッシュ』！
走ってる マークにタッチすることで使えるの。
モンスターとのキョリをちぢめることができるよ！

モンスターを呼びよせる効果もあるから
敵がいなかったり少なかったりしたときには
積極的にダッシュしてみよう！
]])
      popup:addImage(1, "tutorial4_2.png")
    elseif level == 5 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "ためよう！『パワーチャージ』！",
      [[
『パワーチャージ』おぼえたね！これは大事だよー

パワーチャージ マークをタッチすると文字通り
 『パワー』 をためることができるんだ。
]])
      popup:addImage(0, "tutorial5_1.png")
      popup:setText(1, "ためよう！『パワーチャージ』！",
      [[
『パワー』 をためると次のワザの効果がアップ！

『アタック』なら、3回攻撃しないと倒せない
モンスターも1回で倒せちゃったりするよ！
]])
      popup:addImage(1, "tutorial5_2.png")
      popup:setText(2, "『パワー』は使いきり！", [[
でもね『パワー』 は、ワザを使うと、すぐに
使いきっちゃうから気を付けて！

モンスターの強さをよーくみきわめて、そのまま
たたかうか『パワーチャージ』で強力な一撃か
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
      popup:addImage(0, "tutorial6_1.png")
    elseif level == 7 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "必殺『オクススラッシュ』！", [[
わ！モンスター倒すのに時間かかってたら、
いつの間にか目の前がモンスターでいっぱい！

でも大丈夫！こんな時こそ
必殺の『オクススラッシュ』！！]])
      popup:addImage(0, "tutorial7_1.png")
      popup:setText(1, "必殺『オクススラッシュ』！", [[
『オクススラッシュ』は複数のモンスターを
同時にこうげきできる強力なワザだよ！

強力だから、『パワー』が1回以上たまって
いないと使えないけれど、モンスターの軍団も
一気に倒すことができちゃうよ！
]])
      popup:addImage(1, "tutorial7_2.png")
    elseif level == 8 then
      enemyManager:popEnemyAt("T_geekT3",3,1)
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "ピンチのときは『ガード』", [[
わっ！あのモンスターはかなりHPが高いみたいね

今のオクスじゃ太刀打ちできないみたい
ちょっと悔しいけれど、
ここは『ガード』で防いでみようか
]])
      popup:setText(1, "ピンチのときは『ガード』", [[
『ガード』のワザは 盾のマークをタッチ！
盾を構えて『ガード』状態になるよ

『ガード』は次にワザを入力するまでは
ダメージを防ぐまでずっと有効だから
慌てずに使ってみて！
]])
      popup:addImage(1, "tutorial8_1.png")
    elseif level == 9 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "特殊ワザ『ノックバック』", [[
今おぼえたワザは、オクス専用のワザ『ノックバック』だよ！たつまきマークをタッチして使おう。

『ノックバック』はモンスターを1匹、後ろに
ふっとばすことができるんだ。使いドコロが
難しいけど、使いこなすと戦いが楽になるよ
]])
      popup:addImage(0, "tutorial9_1.png")
      enemyManager:popEnemyAt("T_tnt9", 4, 1):setExp(60)
      self.__IRegister__:setBool("knockbackPoped", true)
    elseif level == 10 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "免許皆伝！？", [[
これでオクス君の戦い方は一通りマスター
できたはずよ！あとは練習に満足したら、
『ポーズ』ボタンにタッチして
チュートリアルを終わってね。
]])
      popup:addImage(0, "tutorial10_2.png")
      popup:setText(1, "免許皆伝！？", [[
ああ！でもちょっとまって！まだ大事なワザを
説明してないじゃない！今作の目玉なのに！

このゲーム真の主役、私、ラスカへの
『キャラチェンジ』については次の『レッスン２』
でしっかりレクチャーするわ！
じゃ、次回もよろしくね！バイバイ！
]])
      local data = SaveData:sharedData()
      data:unlockAchievement("clearTutorialA") -- 実績アンロック
      data:setClearedForMap("fp_tutorial") -- フリープレイ
    end
  end,
  getEnemyPopRate = function(level)
    if level == 10 then
      return 0.5
    end
    return 0
  end,
  fixedEnemies = {
  }
}
