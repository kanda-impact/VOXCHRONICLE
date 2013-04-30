require("concat")
require("timezone")
--コンティニュ―後にゲームが再開した時
return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
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
        "",
        "",
        "",
        "",
        "",
      }
    end

    --2b
    if mapId == "2b_cave" then
      return {
        "",
        "",
        "",
        "",
        "",
      }
    end

    --2c
    if mapId == "2c_cyber" then
      return {
        "",
        "",
        "",
        "",
        "",
      }
    end

    --3a
    if mapId == "3a_ruin" then
      return {
        "",
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
    if mapId == "3d_space" then
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
        "",
        "",
        "",
        "",
        "",
      }
    end

    --１ｂ夜
    if mapId == "1b_field" and currentTimeZone == 2 then
      return {
        "",
        "",
        "",
        "",
        "",
      }
    end
  end
  return concat(commonPattern, getExtraPattern())
end
----各ステージ部分
----1a
----[[
--return {
--    "てきを　どんどん　こうげきしよう",
--    "パワーチャージを　つかってみよう",
--    "とりあえず　けんのマークをおしてみよう",
--    "ならうより　なれるのだ",
--  }
----1b昼
--return {
--    "そうびと　たいせいに　ちゅうもく",
--    "チェンジを　つかいこなすのだ",
--    "きをとりなおして　いこう",
--    "こんなところじゃ　おわれない！",
--    "つぎは　ほんきで　いくぞ！",
--  }
----2a
--return {
--    "",
--    "",
--    "",
--    "いっぴきずつたおしては　きりがないな...",
--    "",
--  }
----2b
--return {
--    "あのコウモリは　すばやいぞ",
--    "てきのおおだては　ゆみでもねらえるわよ",
--    "まにあわないときは　ガードやノックバックをかつようしよう",
--    "",
--    "",
--  }
----2c
--return {
--    "",
--    "",
--    "",
--    "たいせいがあっても　たおせればもんだいない",
--    "あきらめるには　まだはやい",
--  }
----3a
--return {
--    string.format("%sはほろびぬ！なんどでもよみがえるさ！", chara),
--    "",
--    "",
--    "",
--    "",
--  }
----3b
--return {
--    "",
--    "",
--    "",
--    "",
--    "",
--  }
----3c
--return {
--    "",
--    "",
--    "",
--    "",
--    "",
--  }
----3d
--return {
--    "",
--    "",
--    "",
--    "",
--    "",
--  }
----1b夕暮れ
--return {
--    "",
--    "",
--    "",
--    "",
--    "",
--  }
----１ｂ夜
--return {
--    "そうびと　たいせいに　ちゅうもく",
--    "チェンジを　つかいこなすのだ",
--    "きをとりなおして　いこう",
--    "ねむくない　ねむくない...",
--    "むりはしちゃ　ダメよ？",
--  }
--  ]]
--end
