require("concat")
require("timezone")
require("variable_expansion")
--コンティニュ―後にゲームが再開した時
return function(map, characterManager, enemyManager)
  chara = characterManager:getCurrentCharacter():getName()
  local mapId = map:getIdentifier()
  local currentTimeZone = getCurrentTimeZone()
  local level = characterManager:getLevel()
  --コンティニュ―時（全ステージ共通部分）
  local commonPattern =  {
    "さあ　もういちど！",
    "こんどこそ　こえてやる",
    "こんどこそ　まけないぞ",
    "いやな　ゆめをみたんだ",
    "どうしたら　クリアできるかな",
    "さっきのは　なかったことに",
    "はいぼくなんて　なかった",
    "もういちど　やってみよう",
    "たたかいかたを　かえてみるか",
    "こんどこそ　まけない",
    "こんなことで　へこたれるか！",
    "リハってことにして　もっかい！"
  }
  local getExtraPattern = function()
    --各ステージ部分
    --1a
    if mapId == "1a_simple" then
      return {
        "てきを　どんどん　こうげきしよう",
        "パワーチャージを　つかってみよう",
        "チュートリアルも　みてみてね",
        "けんのマークを　れんだしよう",
        "とにかく　けんのマークとか　いろいろおしてみよう"
      }
    end

    --1b昼
    if mapId == "1b_field" and currentTimeZone == 0 then
      return {
        "そうびと　たいせいに　ちゅうもく",
        "チェンジを　つかいこなすんだ",
        "ＭＰかんりは　できてるかな？",
        "かがみをわってから　まほうこうげきをたたきこむんだ",
        "まだまだ　これからだ！"
      }
    end

    --2a
    if mapId == "2a_forest" then
      return {
        "いっぴきずつたおしては　キリがないな...",
        "たいりょくのたかいやつに　まとをしぼろう",
        "パワーチャージすれば　きっとなんとかなる！",
        "オクススラッシュをうまくつかおう",
        "ラスカサンダーをつかうときは　ＭＰにちゅういしてね"
      }
    end

    --2b
    if mapId == "2b_cave" then
      return {
      "あのコウモリは　すばやいぞ",
      "てきのそうびに　きをつけよう",
      "あかいかがみは　オクスのこうげきで　たたきわれるわよ",
      "あおいたては　ラスカのまほうで　うちやぶれるぞ",
      "たおしきれないときは　ガードでやりすごそう"
      }
    end

    --2c
    if mapId == "2c_cyber" then
      return {
        "たいせいがあっても　たおせればもんだいない",
        "ノックバックすると　てきどうしを　かさねることもできる",
        "かならずしも　ぜんいんたおす　ひつようはないんだ",
        "かいふくのチャンスを　じりきでつくりだそう",
        "ときにはあえて　ダメージをうけることも　ひつようだ"
      }
    end

    --3aBoss
    if (mapId == "3a_ruin" or mapId == "ruin_boss") and level == 30 then
      return {
        "とにかく　こうげきしまくるんだ！",
        "やられるまえに　やるしかない！",
        "おちついてこうげきすれば　だいじょうぶ"
      }
    end
    --3bBoss
    if (mapId == "3b_castle" or mapId == "bossdebug") and level == 30 then
      return {
        "けんをかまえたら　ガードのじゅんびをしよう",
        "ちょくせつこうげきできるコマンドがあるわよね？",
        "てっきゅうは　いっきにかたづけよう"
      }
    end
    --3cBoss
    if (mapId == "3c_ocean" or mapId == "ocean_boss") and level == 30 then
      return {
        "ほんたいをねらって　こうげきするのよ！",
        "つなみにはこうげきがきかない　ガードでやりすごそう",
        "あしのさいせいは　だんだんにぶくなるはずだ"
      }
    end
    --3dBoss
    if (mapId == "3d_space" or mapId == "space_boss" or mapId == "space_boss2") and level == 30 then
      return {
        "いつでもファージーをたおせるようにしておこう",
        "ボスのワザが　どういうこうかなのか　はあくしておこう",
        "てきのこうどうをみてから　コマンドをえらぶという　てもあるぞ"
      }
    end
    
    --3a
    if mapId == "3a_ruin" then
      return {
        "てきのりんかくの　ひかっているいろを　よくみわけよう",
        "チェンジを　つかいこなすんだ",
        "あおくひかってるてきは　ラスカにまかせよう",
        "あかくひかってるてきは　オクスにまかせるのよ",
        "ぞくせいをあわせないと　たおしきれないよ"
      }
    end

    --3b
    if mapId == "3b_castle" then
      return {
        "そうびと　たいせいに　ちゅうもく",
        "チェンジを　つかいこなすんだ",
        "かたーいてきは　ガードでやりすごしても　いいのよ？",
        "あとちょっとでたおせるてきは　ノックバックして　ついげきだ",
        "てきのおおだては　ゆみでもねらえるわよ"
      }
    end

    --3c
    if mapId == "3c_ocean" then
      return {
        "まりょくをおしみなく　つかっていこう",
        "むりだとおもったら　ガードでやりすごすのも　たいせつよ",
        "はやさがちがうてきは　ガードのタイミングにきをつけて",
        "はりついてくるてきに　ガードをじゃまされないようにね　",
        "はりついてくるてきは　はやめにたおしておこう"
      }
    end

    --3d
    if mapId == "3d_space" and currentTimeZone == 0 then
      return {
        "とんでもなく　はやいアイツにちゅうい",
        "せっかくパワーチャージしたのに　わりこまれるとかなしい",
        "はりつかれても　しななきゃやすい",
        "のこりのHPやMPを　つねにチェックしておこう",
        "ここまでこれたきみなら　きっとだいじょうぶ！"
      }
    end

    --1b夕暮れ kawaztan
    local isBattleKawaz = map.__IRegister__:getBool("isBattleKawaztan")
    if mapId == "1b_field" and currentTimeZone == 1 and isBattleKawaz then
      return {
        "こまめにヒーリングをかけよう",
        "きょうりょくなワザはしっかりガードしよう",
        "いちどラスボスをたおしたきみなら　かならずかてる！"
      }
    end
    
     --1b夕暮れ
    if mapId == "1b_field" and currentTimeZone == 1 then
      return {
        "そうびと　たいせいに　ちゅうもく",
        "チェンジを　つかいこなすんだ",
        "ＭＰかんりは　できてるかな？",
        "こんなところじゃ　おわれない！",
        "きをとりなおして　いこう"
      }
    end

    --１b夜
    if mapId == "1b_field" and currentTimeZone == 2 then
      return {
        "そうびと　たいせいに　ちゅうもく",
        "チェンジを　つかいこなすんだ",
        "ＭＰかんりは　できてるかな？",
        "ねむくない　ねむくない...",
        "むりはしちゃ　ダメよ？"
      }
    end
  end
  return concat(commonPattern, getExtraPattern())
end
