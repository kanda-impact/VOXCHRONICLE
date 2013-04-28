return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  --ステージセレクト時
return {
    "わかれみちだ　どうする？",
    "みちがふたつに　わかれている",
    "わかれみち　みたいね",
    "つぎのステージをえらんでね",
    "ステージセレクト",
  }
 --[[
--ステージセレクトで何もせず一定時間経過した時(作れそうであれば)
return {
    "どっちにすすもうか",
    "みぎにいくほど　むずかしいよ",
    "すきなほうに　すすもう",
    "ひだりのほうが　かんたんだよ",
    "EASY かんたん　HARD むずかしい",
  }
  ]]
end