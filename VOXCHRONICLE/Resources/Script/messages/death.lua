require("concat")
require("timezone")
require("variable_expansion")
-- 死亡時メッセージ
return function(map, characterManager, enemyManager)
  chara = characterManager:getCurrentCharacter():getName()
  local mapId = map:getIdentifier()
  local currentTimeZone = getCurrentTimeZone()
  local level = characterManager:getLevel()
  --死亡時（全ステージ共通部分）
  local commonPattern =  {
      _("#{chara}は　とうとう　しんでしまった"),
      _("おお#{chara}よ　しんでしまうとは　なさけない"),
      _("#{chara}は　みちなかばで　おわった"),
      _("うんが　わるかったに　ちがいない"),
      _("むねん　......！"),
      _("ぐわぁぁぁ！"),
      _("ざんねん！　#{chara}のぼうけんは　ここでおわって　しまった"),
      _("#{chara}の　ぼうけんは　ここまでだった"),
      _("CONTINUE?"),
      _("#{chara}は　にどと　おきあがることは　なかった"),
      _("#{chara}の　めのまえは　まっくらになった"),
      _("はいカットー"),
      _("そのご　#{chara}の　すがたを　みたものは　いない"),
      _("#{chara}の　だんまつまが　ひびきわたった"),
      _("#{chara}は　たべられて　しまった"),
      _("ゆうしゃ　#{chara}　ここにねむる"),
      _("こんなに　がんばったのに　......なぜ"),
      _("だめだった"),
      _("あんそくのち　グランエターナは　とおい"),
      _("まわりの　おとが　とおのく　......"),
      _("まものたちの　おたけびを　ききつつ　はてた"),
      _("なぜ　やられてしまったのか　......"),
      _("#{chara}は　ちからつきた......"),
      _("......　ざんねんだったな"),
      _("ざんねん　むねん　もういっかい"),
      _("じんせいの　まくが　とじた"),
      _("#{chara}は　おわって　しまった"),
      _("うんが　わるかったに　ちがいない"),
      _("ぐふっ。"),
      _("#{chara}は　むごたらしく　なった"),
      _("これは　ひどい"),
      _("くちおしい　......ちくしょー！"),
      _("―　Ｋ　Ｏ　―"),
      _("もはや、ここまでか…"),
      _("こんなところで　まけてしまうのか......"),
      _("#{chara}ーーーーーー！"),
      _("#{chara}は　くちはてた"),
      _("そ、そんなバカなぁー！"),
      _("おしいひとを　うしなってしまった"),
      _("どうして　こうなった"),
      _("#{chara}はほろびぬ！　なんどでも　よみがえるさ"),
      _("お　おぼえてろー"),
      _("うわーん"),
      _("だが　だいに　だいさんの　#{chara}が　...かならず"),
      _("こんなところで　くちるなんて　もったいない"),
      _("#{chara}のなきがらは　おいしくいただかれた"),
      _("どういうこと　だってばよ......"),
      _("わがしょうがいに　いっぺんのくい　なし"),
      _("あんたのために　やられたわけじゃないんだからね"),
      _("か......　かてない......　だと"),
      _("もっと　がんばれ！　きみなら　できる"),
      _("ゆだん　たいてき"),
      _("てきは　のこりたいりょくで　いろが　かわるぞ"),
      _("おお......　かみよ......　どうして......"),
      _("どんまい"),
      _("アーッ!"),
      _("しにました"),
      _("どん・まい　❤"),
      _("まだ、まけるわけには　......！"),
      _("な、なんという、ていたらく！"),
      _("おつかれさまでした"),
      _("あ　やられた"),
      _("ざんねーん"),
      _("ヤラレチャッタ"),
      _("ばたんきゅ～......"),
      _("がめおべらー"),
      _("( ﾟдﾟ )"),
      _("そして　でんせつへ"),
      _("#{chara}せんせいの　じかいさくに　ごきたいください"),
      _("うつくしく　はかなく　ちった"),
      _("かちそこねた"),
      _("ちめいしょう"),
      _("だめぽ"),
      _("Noooooooooo!!"),
      _("ＣＭ　はいりまーす"),
      _("ごめいふくを　おいのりします"),
      _("めげるな！　がんばれ！"),
      _("やっちゃったゼ"),
      _("まものめぇ　おのれぇ"),
      _("まものは　364の　けいけんちを　てにいれた"),
      _("#{chara}！　へんじをしろ　#{chara}ーーーーー！"),
      _("いま　あなたは　まものに　たおされました"),
      _("オ「ごめんよ..エリザ...」ラ「エリザってだれよぉぉ！」"),
      _("さいき　ふのう　－リタイア－"),
      _("#{chara}は　ないたり　わらったり　できなくなった"),
      _("#{chara}は　いよいよもって　しんだ"),
      _("ご　りんじゅう"),
      _("むこうに　おはなばたけが　みえます"),
      _("#{chara}！　おうとうしろ　#{chara}ーーーーー！"),
      "ちからつきてしまった",
      "しょうしょう　あそびすぎたか",
      "しゅぎょうして　でなおさねば．．．！",
      "やつは　なにもの　だったんだ．．．",
      "くっ．．．　つよすぎる．．．",
      "あび　きょうかん",
      "どうして　こうなった？",
      "まものは　たのしそうに　わらっている",
    }
    local extraPattern = {}
    math.random(100)
    
    local mapId = map:getIdentifier()
    if mapId == "1a_simple" then -- 1a
      extraPattern = {
        "だいじょうぶ　すこしずつ　なれていこう",
        "まあ　そういうことも　あるさ",
        "チュートリアルは　みてくれた？",
        "ま　まって　やめないでー！"
      }
    elseif mapId == "1b_field" and currentTimeZone == TimeZoneDay then -- 1b昼
      extraPattern = {
        "さすがハード　ひとすじなわでは　いかないってかんじ？",
        "まさか　いきなりハードを　えらんだのでは？",
        "おいおい　こんなのまだ　じょのくち　だぜ？",
        "あまくみては　いけないな...",
      }
    elseif mapId == "1b_field" and currentTimeZone == TimeZoneDay then -- 1b夕方
      extraPattern = {
        "さすがハード　ひとすじなわでは　いかないってかんじ？",
        "まさか　いきなりハードを　えらんだのでは？",
        "たそがれに　しずむ",
        "ああ．．．ゆうひが　しずむ．．．"
      }

    elseif mapId == "1b_field" and currentTimeZone == TimeZoneDay then -- 1b夜
      extraPattern = {
        "さすがハード　ひとすじなわでは　いかないってかんじ？",
        "まさか　いきなりハードを　えらんだのでは？",
        "くらやみに　のみこまれた",
        "やみよに　みえなくなった",
        "よくあさには　あとかたものこらない　だろう"
      }
    elseif mapId == "2a_forest" then
      extraPattern = {
        "やられても　くじけるな",
        "めげずに　がんばって",
        "もういちど　ちょうせんしよう",
        "パワーチャージを　つかってみよう"
      }
    elseif mapId == "2b_cave" then
      extraPattern = {
        "くらいよー　せまいよー　こわいよー",
        "ぐぅ．．．さすが　てごわい",
        "もう　たいようを　みることはできない",
        "てきがそとまで　はこびだしてくれないかな...",
        "じめんが　つめたい"
      }
    elseif mapId == "2c_cyber" then
      extraPattern = {
        "こんなの　できねーよー",
        "むずかしいよう",
        "さすが　ハード．．．がくっ",
        "シールドだけじゃ　さばききれない"
      }
        --ボスの死亡台詞
    elseif mapId == "3a_ruin" and level == 30 then    --A
    extraPattern = {
        "ぷちっ",
        "ぐしゃっ",
        "ぺたんこになった",
        "まにあわなかった...",
        "まるで　きょうせいスクロールの　かべのようだった"
      }
    elseif mapId == "3b_castle" and level == 30 then    --B
    extraPattern = {
        "たて！　きさまのちからは　そのていどでは　ないはずだ",
        "まだだ...　まだ　たたかいたりぬ",
        "でなおして　くるがいい",
        "",
        _("#{chara}　きさまの　な　おぼえておこう")
      }
    elseif mapId == "3c_ocean" and level == 30 then    --C
    extraPattern = {
        "タコなぐりにされてしまった",
        "イカんともしがたい",
        "かずのぼうりょくには　かなわなかった",
        "あのゲソ　たおしても　キリがない!?",
        "スルメに　してやる...!"
    }
    elseif mapId == "3d_space" and level == 30 then    --Dボス
    extraPattern = {
        "あっとうてきなちからで　けしさられた",
        _("そして　#{chara}は　かんがえるのを　やめた"),
        "このせかいから　おとがきえた",
        "あいつは...あいつだけは　たおさないと...!!",
        "やっと　ここまできたのに...!",
    }
    elseif mapId == "3d_space" and level == 30 then    --かわずたん
    extraPattern = {
        "てんしのような　あくまのえがお",
        "おまえのような　1ボスがいるか！",
        "",
        "",
        "",
    }
    elseif mapId == "3a_ruin" then
      extraPattern = {
        "このまま　くちはてていく　さだめ",
        "",
        "",
      }
    elseif mapId == "3b_castle" then
      extraPattern = {
        "しろの　ぼうれいと　なりはてるのか．．．",
        "",
        "",
        "",
      }
    elseif mapId == "3c_ocean" then
      extraPattern = {
        "うみの　もくずと　きえた",
        "くらい　くらい　うみのそこにしずんだ",
        "",
      }
    elseif mapId == "3d_space" then
      extraPattern = {
        "うちゅうの　もくずと　きえた",
        _("そして　#{chara}は　かんがえるのを　やめた")
        "うちゅうに　ただよう　デブリに　なった",
        "ラスカ　きみはどこにおちたい？",
        "",
      }
      
    end 
    local r = math.random(100)
    if r < 20 then -- 2割の確率で個別テーブルを返します
      return extraPattern
    end
    return commonPattern
end