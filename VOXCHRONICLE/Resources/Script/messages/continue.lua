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
        "とにかく　けんのマークとか　いろいろおしてみよう",
      }
    end

    --1b昼
    if mapId == "1b_field" and currentTimeZone == 0 then
      return {
        "",
        "",
        "",
        "",
        "",
      }
    end

    --2a
    if mapId == "2a_forest" then
      return {
        "いっぴきずつたおしては　きりがないな...",
        "",
        "",
        "",
        "",
      }
    end

    --2b
    if mapId == "2b_cave" then
      return {
      "あのコウモリは　すばやいぞ",
      "てきのおおだては　ゆみでもねらえるわよ",
      "まにあわないときは　ガードもしよう",
      "ノックバックも　つかってみよう",
      }
    end

    --2c
    if mapId == "2c_cyber" then
      return {
        "たいせいがあっても　たおせればもんだいない",
        "あきらめるには　まだはやい",
        "",
        "",
        "",
      }
    end

    --3a
    if mapId == "3a_ruin" then
      return {
        _("#{chara}はほろびぬ！なんどでもよみがえるさ！"),
        "",
        "",
        "",
        "",
      }
    end

    --3b
    if mapId == "3b_castle" then
      return {
        "",
        "",
        "",
        "",
        "",
      }
    end

    --3c
    if mapId == "3c_ocean" then
      return {
        "",
        "",
        "",
        "",
        "",
      }
    end

    --3d
    if mapId == "3d_space" and currentTimeZone == 0 then
      return {
        "",
        "",
        "",
        "",
        "",
      }
    end

    --1b夕暮れ
    if mapId == "1b_field" and currentTimeZone == 1 then
      return {
        "そうびと　たいせいに　ちゅうもく",
        "チェンジを　つかいこなすのだ",
        "きをとりなおして　いこう",
        "こんなところじゃ　おわれない！",
        "つぎは　ほんきで　いくぞ！"
      }
    end
    --1b夕暮れ kawaztan
    local isBattleKawaz = map.__IRegister__:getBool("isBattleKawaztan", false)
    if mapId == "1b_field" and currentTimeZone == 1 and isBattleKawaz then
      return {
      "",
      }
    end

    --１b夜
    if mapId == "1b_field" and currentTimeZone == 2 then
      return {
        "そうびと　たいせいに　ちゅうもく",
        "チェンジを　つかいこなすのだ",
        "きをとりなおして　いこう",
        "ねむくない　ねむくない...",
        "むりはしちゃ　ダメよ？",
      }
    end
  end
  return concat(commonPattern, getExtraPattern())
end
