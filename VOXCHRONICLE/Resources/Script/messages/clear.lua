require("concat")
require("timezone")
return function(map, characterManager, enemyManager)
  --ステージクリア―時
  --クリア時（全ステージ共通部分）
  local commonPattern =  {
    "ステージ　クリアー！",
    "なんとか　てきを　しのいだ",
    "たたかいを　きりぬけた",
    "よし！　きりぬけたぞ！",
    "モンスターを　たおした",
    "つぎぃ　いってみよ～",
  }
  local chara = characterManager:getCurrentCharacter():getName()
  local mapId = map:getIdentifier()
  local currentTimeZone = getCurrentTimeZone()
  local getExtraPattern = function()
    --各ステージ部分
    --1a
    if mapId == "1a_simple" then
      return {
        "らくしょう　らくしょう",
        "へへへ　どんなもんだい！",
        "荒野　クリアー！",
        "ここからが　しょうねんば！",
      }
    end

    --1b昼
    if mapId == "1b_field" and currentTimeZone == 0 then
      return {
        "ふぅ　なんとかなったぜ",
        "平原を　こえた",
        "平原　クリアー！",
        "きょうは　いいてんきだな",
      }
    end

    --2a
    if mapId == "2a_forest" then
      return {
        "もりを　ぬけた",
        "森林　クリアー",
        "どくきのこ　つよかったな",
        "もりを　ぬけるわよ！",
      }
    end

    --2b
    if mapId == "2b_cave" then
      return {
        "炭鉱の　でぐちについた",
        "炭鉱　クリアー",
        "くずれおちなくて　よかった",
        "炭鉱には　ジャズがにあう",
      }
    end

    --2c
    if mapId == "2c_cyber" then
      return {
        "電脳世界　クリアー",
        "電脳世界から　だっしゅつした",
        "すさまじい　たたかいだったぜ",
        "おそろしい　せかいだった",
      }
    end

    --1b夕暮れ
    if mapId == "1b_field" and currentTimeZone == 1 then
      return {
        "ゆうぐれを　こえて",
        "平原　クリアー",
        "平原の　おわりがみえた",
        "さあ　たたかいはこれからだ",
        "かった！　おれたちはつよい！",
      }
    end
       --1b夕暮れ　かわずたん
    local isBattleKawaz = map.__IRegister__:getBool("isBattleKawaztan", false)
    if mapId == "1b_field" and currentTimeZone == 1 and isBattleKawaz then
      return {
        "ゆうぐれを　こえて",
        "平原　クリアー",
        "平原の　おわりがみえた",
        "さあ　たたかいはこれからだ",
        "かった！　おれたちはつよい！",
        "あいつは　なんだったんだ？！",
        "やったー　たおしたぞー",
        "まいったケロ～",
        "やられたケロ～",
        "こうさんケロ～",
        "ばたんきゅーケロー",
        "ぎゃふんケロ～",
        "やーらーれーたーけーろー",
        "そうぜつな　たたかいだったぜ．．．",
      }
    end
    --１ｂ夜
    if mapId == "1b_field" and currentTimeZone == 2 then
      return {
        "もうじき　よるがあけそうね",
        "平原　クリアー",
        "平原に　おわりがみえた",
        "さあ　たたかいはこれからだ"
      }
    end
  end
  return concat(commonPattern, getExtraPattern())
end