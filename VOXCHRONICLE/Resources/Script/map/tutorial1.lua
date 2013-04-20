Map = {
  name = "Lesson2",
  wayMusic = "chabo",
  bossMusic = "",
  backgroundImage = "tutorial_background.png",
  skin = "skinA",
  ending = "",
  nextMaps = {},
  initialLevel = 11,
  maxLevel = 21,
  getEnemyTable = function(level)
    if level == 20 then
      return {T_tomezora2 = 1, T_tetufez2 = 2, T_geek2 = 1, T_leaf2 = 1, T_flower2 = 1}
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
    if level == 11 then
      -- ラスカにチェンジしないと先には進めない
      if characterManager:getCurrentCharacter():getCharacterType() == CharacterTypeLaska then
        -- ラスカにチェンジ済なので、敵が1体もいなくなったらモンスター生成
        if enemyCount == 0 then
          local slime = enemyManager:popEnemyAt("T_slime30", 3, 1)
          slime:setExp(30) -- 経験値30
        end
      end
    elseif level == 12 then
      -- 敵が1体もいなくなったらモンスター生成
      if enemyCount == 0 then
        enemyManager:popEnemyAt("T_moth", 4, 0)
        enemyManager:popEnemyAt("T_tnt", MAX_ROW - 1, 1):setExp(60)
        enemyManager:popEnemyAt("T_moth", 4, 2)
      end
    elseif level == 13 then
      -- 敵が1体もいなくなったらモンスター生成
      if enemyCount == 0 then
        -- 経験値は全員10固定

        for i = 0, 2 do
          local geek = enemyManager:popEnemyAt("T_geek", 6, i)
          geek:setExp(10)
          geek:setHP(3)
          enemyManager:popEnemyAt("T_tomezora", 5, i):setExp(10)
        end
      end
    elseif level == 14 then
      local isNotFirstTurn = self.__IRegister__:getBool("isNotFirstTurn")
      local isGotDamage = self.__IRegister__:getBool("isGotDamage")
      local usedCure = self.__IRegister__:getBool("usedCure")
      local lastSkill = characterManager:getLastSkill()
      local waitTurn = self.__IRegister__:getRegister("waitTurn", 0)

      -- 新たにダメージ受けたらポップアップを出す
      if characterManager:getHP() < preHP and not isGotDamage then
        self.__IRegister__:setBool("isGotDamage", true)
        local popup = layer:addPopupWindow(1)
        popup:setText(0, "いのちをだいじに", [[
きゃあ！いつの間にか体力(HP)がピンチに！
モンスターもいないし
この辺でHPの回復をしましょ？

ハートのマークをタッチで『HPヒーリング』。
いやしの魔法でHPが回復するわ。
]])
      end
      -- 回復スキルの使用判定を行う
      if lastSkill and lastSkill:getIdentifier() == "cure" and not usedCure then
        local popup = layer:addPopupWindow(2)
        popup:setText(0, "いのちをだいじに", [[
上手く回復できたわね
体力がなくなっちゃうとやられちゃうから
こまめな回復を心がけてね
]])        
        popup:setText(1, "いのちをだいじに", [[
そうそう、忘れられがちだけど、
『パワーチャージ』でためたパワーは、
『HPヒーリング』でも有効よ！

消費する魔力(MP)は変わらずに回復量が
ぐぐーんと増えちゃうからおトクなの
]])
        usedCure = true
        self.__IRegister__:setBool("usedCure", usedCure)
      elseif not layer:getPopupWindow() and self.__IRegister__:getBool("isGotDamage") and not self.__IRegister__:getBool("usedCure") then -- ダメージ受けた後かつ、回復使用前
        waitTurn = waitTurn + 1
        if waitTurn == 5 then -- 5ターン何にもしなかったら怒る
          local popup = layer:addPopupWindow(1)
          popup:setText(0, "いのちをだいじに", [[
オクス、ダメージを喰らっちゃったから
体力(HP)を回復してみてよー

『HPヒーリング』を使うには
ハートのマークをタッチよ！
]])
          waitTurn = 0
        end
        self.__IRegister__:setRegister("waitTurn", waitTurn)
      end

      -- 敵が1体もいなくなったらモンスター生成
      if enemyCount == 0 then
        -- とてもわかりにくいけど最初のターン以外の場合
        if isNotFirstTurn and usedCure then
          enemyManager:popEnemyAt("T_moth7", 3, 1):setExp(30)
        elseif not isNotFirstTurn then
          self.__IRegister__:setBool("isNotFirstTurn", true)
          enemyManager:popEnemyAt("flame2C2", 0, 1)
        end
      end
    elseif level == 15 then
      local lastSkill = characterManager:getLastSkill()
      local changedVox = self.__IRegister__:getBool("changedVox")
      local healedMp = self.__IRegister__:getBool("healedMp")
      if not changedVox and characterManager:getCurrentCharacter():getName() == "オクス" then
        -- 初回限定でオクスにチェンジしたらポップアップを表示する
        self.__IRegister__:setBool("changedVox", true)
        local popup = layer:addPopupWindow(2)
        popup:setText(0, "『MPリカバリー』を使おう", [[
魔力(MP)はオクスじゃないと回復できないの
オクスに『チェンジ』したら
宝石のマークをタップ！
『MPリカバリー』 が使えるわ！

これで魔力(MP)が回復するのよ！
]])
        popup:setText(1, "HPはラスカ、MPはオクス", [[
つまり、オクスはMP。私、ラスカはHP回復
ってカンジにそれぞれ回復できるものが
ちがうから、じょうずに『チェンジ』して
回復していってね！！
]])
        --＊魔力回復の後の敵１セットでＯＫ
      end
      -- オクスが回復スキル使ったら敵を出すようにフラグを立てる
      if lastSkill and lastSkill:getIdentifier() == "charge" then
        healedMp = true
        self.__IRegister__:setBool("healedMp", healedMp)
      end
      -- 回復スキル使用フラグが立っていて敵がいなかったら敵を出す
      if enemyCount == 0 and healedMp then
        enemyManager:popEnemyAt("T_geek", 3, 1):setExp(60)
      end
    elseif level == 16 or level == 17 or level == 18 or level == 19 then
      -- 敵が1体もいなくなったらモンスター生成
      if enemyCount == 0 then
        if level == 16 then
          local enemy = enemyManager:popEnemyAt("T_flower", 3, 1)
          enemy:setExp(60)
          enemy:setHP(18)
          enemy:setSkillType(SkillTypeMagical)
        elseif level == 17 then
          local enemy = enemyManager:popEnemyAt("T_slime12", 3, 1)
          enemy:setExp(60)
          enemy:setHP(22)
          enemy:setSkillType(SkillTypePhysical)
        elseif level == 18 then
          local enemy = enemyManager:popEnemyAt("T_flower", 3, 1)
          enemy:setExp(60)
          enemy:setHP(12)
          enemy:setItem(EnemyItemBarrier)
        elseif level == 19 then
          local enemy = enemyManager:popEnemyAt("T_leaf", 3, 1)
          enemy:setExp(60)
          enemy:setHP(12)
          enemy:setItem(EnemyItemShield)
        end
      end
    elseif level == 20 then
      -- 何もしない
    end
    self.__IRegister__:setRegister("preHP", characterManager:getHP())
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    self.__IRegister__:clearRegister()
    local level = characterManager:getLevel()
    local layer = EffectLayer:sharedLayer()
    if level == 11 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "ラスカに『チェンジ』！", [[
さぁ！私、ラスカが大活躍のレッスン2よ！
そろそろオクス君もつかれたでしょうから、
『チェンジ』マークにタッチして
私に交代してちょうだい。

音楽もかわって気分一新よ！]])
      popup:setText(1, "ラスカに『チェンジ』！", [[
オクス君は剣士だけど、私、ラスカは魔法使い
私は魔法をつかって攻撃するわ。

オクスの時と操作はかわらないから
いろいろ試してみてね！
]])
      --＊後ろにＨＰの高い敵を１体
      --手前にＨＰ低い敵２体（ジクー）
    elseif level == 12 then
      local popup = layer:addPopupWindow(2)
      popup:setText(0, "弓で『スナイプ』！", [[
オクス君は『ノックバック』が使えるけどかわりに
私、ラスカは 弓 での『スナイプ』が使えるわ。

『スナイプ』だと、今いる中で一番HPの高い
モンスターにいきなり攻撃できるの！
]])
      popup:setText(1, "弓で『スナイプ』！", [[
試しに後ろから体力が高いヤツが迫ってくるとき
そいつを『スナイプ』連発で狙ってみて！
]])
    elseif level == 13 then
      enemyManager:removeAllEnemies() -- 前のレベルで残った敵を全滅
      local popup = layer:addPopupWindow(4)
      popup:setText(0, "弓で『スナイプ』！", [[
『スナイプ』の使い方はわかったかしら？

『スナイプ』は次に攻撃が当たるモンスターが
表示されないから使いにくいワザだけど
その分威力は絶大！
使いこなせれば上級者の仲間入りよ
]])
      --＊よわめのジクー＋トメゾラで６体ほど
      --モンスターを倒さなかった場合ループのまま
      --サンダー１回でレベルアップ
      popup:setText(1, "奥義！『ラスカサンダー』！", [[
さて、モンスターの軍団が攻めてくるわ！
そんな時は『ラスカサンダー』！雷のマークよ。

これは『オクススラッシュ』と同じように
『パワー』をためないと使えないけど
モンスターをまとめて攻撃できる強力なワザよ！
]])
      popup:setText(2, "魔力（MP）に注意！", [[
言い忘れたけど、私、ラスカの行動（ワザ）
では、魔力(MP)を消費しちゃうものがあるの。

『ラスカサンダー』は『オクススラッシュ』
とは違って、魔力(MP)を2ポイント使っちゃうの
のこり魔力(MP)には注意してね！
]])
      popup:setText(3, "奥義！『ラスカサンダー』！", [[
魔力を消費しちゃう分、回数には限りがあるけど
その分、高威力だしモンスター全体を
こうげきできるから、上手に使い分けてね！
]])
      characterManager:addMP(characterManager:getMaxMP())
      --＊サンダーで敵を倒した後　火の玉を近くにポップアップ
      --速攻でオクスにぶつけ死なない程度に傷を負わせる
      --↓で回復するまで敵出さずに放置
    elseif level == 15 then
      enemyManager:removeAllEnemies() -- 前のレベルで残った敵を全滅
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "魔力(MP)を回復しよう！", [[
ちょっと、オクス！私に任せてばっかりだと
魔力(MP)がなくなっちゃうよ！
こんな時は、いったん『チェンジ』！

いちどオクスに交代してね！
]])
    elseif level == 16 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "れんけいプレイ！", [[
･･････ふう。これで全てのワザを
説明したかな？じゃあ、そろそろふたりの
れんけいプレイと行ってみようか！

『チェンジ』を使ってモンスターをうまく倒す
ためには覚えておいてほしいことがあるの。
]])
      popup:setText(1, "物理ワザと魔法ワザ", [[
実は、わたしたちのワザには『属性』があるの。
オクスは剣だから『物理』属性、
私、ラスカは魔法だから『魔法』属性。

モンスターにはどちらかのこうげきが効きにくい
『耐性』をもったモンスターもいるのよ。
]])
      popup:setText(2, "赤い敵には青いこうげき", [[
赤く光るモンスターは『魔法耐性』。
私、ラスカのこうげきワザが効きにくいの。

オクスにチェンジしてこうげきを当ててみて
]])
      --＊バリアーもちの敵を出す。
      --赤の敵を先に出す
    elseif level == 17 then
      local popup = layer:addPopupWindow(1)
      popup:setText(0, "青い敵には赤いこうげき", [[
お次は青く光る敵ね
こいつはオクスのこうげきワザが効きにくいの

私、ラスカにチェンジして
こうげきをお見舞いしちゃえ！
]])
    elseif level == 18 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "青には赤、赤には青", [[
『耐性』は理解できたかな？
なるべく『チェンジ』して戦わないと、
いつの間にか追いつめられちゃうわ！

青く光る敵には赤のラスカ
赤い敵には青のオクスって覚えてね

]])   
      popup:setText(1, "モンスターの装備『魔鏡』", [[
次はあのモンスターが持ってる装備に注目して！
あれは『魔境』といって、私のこうげきが
一切きかないの！

『耐性』もかなりやっかいだけど、
この『魔鏡』はもっとやっかいよ！
]])
      popup:setText(2, "モンスターの装備『魔鏡』", [[
『魔境』を破るには
オクスのこうげきが絶対に必要！
こうげきが効かないときはすぐ『チェンジ』して
オクスで戦ってね！
]])
    elseif level == 19 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "モンスターの装備『魔鏡』", [[
おみごと！
モンスターの装備は一度破壊するとあとは
普通にこうげきが通るようになるわ
]])
      popup:setText(1, "モンスターの装備『大盾』", [[
今度のアイツは『大盾』を持っているわね
『大盾』は『魔鏡』の反対
オクスのこうげきが一切効かないの
そんなときはラスカに交代して倒してね
]])
      popup:setText(2, "『魔鏡』と『大盾』", [[
モンスターの装備も『耐性』と同じ

反対の色の攻撃を当てれば
破壊できるって覚えて！
]])
    elseif level == 20 then
      local popup = layer:addPopupWindow(3)
      popup:setText(0, "ラスカ編完了！", [[
さって、『チェンジ』関係の話はこんなトコロねー。
強敵も多いけど、わたしたち２人が上手く力を
合わせていければ恐い物なしなんだから！
がんばりましょ！
]])
      popup:setText(1, "これにて免許皆伝！", [[
伝えられることは全部伝えたから
これで安心してグランエターナをめざせるわね！
とはいえちょっと一辺に説明しすぎたかしら．．．

不安だったらここで練習していってね。
チュートリアルはポーズからやめられるわよ！
]])
      --盾のモンスターも出す
      popup:setText(2, "これにて免許皆伝！", [[
あとは、ラスカちゃん直伝！虎の子の
レッスン３『戦いのテクニック編』もあるから

なんか変なモンスターとか見かけたり、
むずかしい～～！！ってなったら
ぜひ参考にしてみてね。じゃ、バイバ～イ！
]])
      data:unlockAchievement("clearTutorialB") -- 実績アンロック
      data:setClearedForMap("fp_tutorial") -- フリープレイ
    end
  end,
  onFinishPlaying = function(self, characterManager, enemyManager)
    local level = characterManager:getLevel()
    if level == 13 or level == 14 then -- MPが0になったら強制的に全回復してあげる
      if characterManager:getMP() == 0 then
        characterManager:setMP(characterManager:getMaxMP())
      end
    end
  end,
  getEnemyPopRate = function(level)
    if level == 20 then
      return 0.4
    end
    return 0
  end,
  fixedEnemies = {
  }
}
