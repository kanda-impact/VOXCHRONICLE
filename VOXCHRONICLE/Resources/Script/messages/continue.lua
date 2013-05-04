require("concat")
require("timezone")
require("variable_expansion")
--コンティニュ―後にゲームが再開した時
return function(map, characterManager, enemyManager)
  chara = characterManager:getCurrentCharacter():getName()
  local mapId = map:getIdentifier()
  local currentTimeZone = getCurrentTimeZone()
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
      "てきのそうびに　きをつけよう"
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
        "",
        "むりだとおもったら　ガードでやりすごすのも　たいせつよ",
        "はりついてくるてきに　ガードをじゃまされないようにね　",
        "はりついてくるてきは　はやめにたおしておこう"
      }
    end

    --3d
    if mapId == "3d_space" and currentTimeZone == 0 then
      return {
        "",
        "",
        "",
        "",
        "はりつかれても　しななきゃやすい"
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
      
    --1b夕暮れ kawaztan
    if mapId == "1b_field" and currentTimeZone == 1 then
      return {
      　　　　"",
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