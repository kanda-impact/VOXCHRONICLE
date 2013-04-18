-- 死亡時メッセージ
return function(map, characterManager, enemyManager)
  local chara = characterManager:getCurrentCharacter():getName()
  return {
    string.format("%sは　とうとう　しんでしまった", chara), -- ${chara}とか書いてあるのは使えないので、この行と同じ感じに書き換えてください
    "おお${chara}よ　しんでしまうとは　なさけない",
    "${chara}は　みちなかばで　おわった",
    "うんが　わるかったに　ちがいない",
    "むねん　......！",
    "ぐわぁぁぁ！",
    "ざんねん！　${chara}のぼうけんは　ここでおわって　しまった",
    "${chara}の　ぼうけんは　ここまでだった",
    "CONTINUE?",
    "${chara}は　にどと　おきあがることは　なかった",
    "${chara}の　めのまえは　まっくらになった",
    "はいカットー",
    "そのご　${chara}の　すがたを　みたものは　いない",
    "${chara}の　だんまつまが　ひびきわたった",
    "${chara}は　たべられて　しまった",
    "ゆうしゃ　${chara}　ここにねむる",
    "こんなに　がんばったのに　......なぜ",
    "だめだった",
    "あんそくのち　グランエターナは　とおい",
    "まりょくは　なにも　しなければ　かいふくするわよ",
    "まわりの　おとが　とおのく　......",
    "まものたちの　おたけびを　ききつつ　はてた",
    "いぬと　くらげは　つよいぞ",
    "コマンド　「きょうか」は　３ターン　ゆうこうだぞ",
    "なぜ　やられてしまったのか　......",
    "${chara}は　ちからつきた......",
    "......　ざんねんだったな",
    "ざんねん　むねん　もういっかい",
    "じんせいの　まくが　とじた",
    "${chara}は　おわって　しまった",
    "うんが　わるかったに　ちがいない",
    "ぐふっ。",
    "オクスは　むごたらしく　なった",
    "これは　ひどい",
    "くちおしい　......ちくしょー！",
    "―　Ｋ　Ｏ　―",
    "もはや、ここまでか…",
    "こんなところで　まけてしまうのか......",
    "${chara}ーーーーーー！",
    "オクスは　くちはてた",
    "そ、そんなバカなぁー！",
    "おしいひとを　うしなってしまった",
    "どうして　こうなった",
    "${chara}はほろびぬ！　なんどでも　よみがえるさ",
    "お　おぼえてろー",
    "うわーん",
    "だが　だいに　だいさんの　${chara}が　......かならず",
    "こんなところで　くちるなんて　もったいない",
    "${chara}のなきがらは　まものたちが　おいしくいただきました",
    "どういうこと　だってばよ......",
    "わがしょうがいに　いっぺんのくい　なし",
    "べ　べつにあんたのために　やられたわけじゃないんだからね",
    "か......　かてない......　だと",
    "もっと　がんばれ！　きみなら　できる",
    "ゆだん　たいてき",
    "てきは　のこりたいりょくで　いろが　かわるぞ",
    "おお......　かみよ......　どうして......",
    "どんまい",
    "アーッ!",
    "しにました",
    "どん・まい　❤",
    "まだ、まけるわけには　......！",
    "な、なんという、ていたらく！",
    "おつかれさまでした",
    "あ　やられた",
    "やーい　やーい",
    "ヤラレチャッタ",
    "ばたんきゅ～......",
    "ざんねん！　がめおべら　です",
    "( ﾟдﾟ )",
    "そして　でんせつへ",
    "${chara}せんせいの　じかいさくに　ごきたいください",
    "うつくしく　はかなく　ちった",
    "かちそこねた",
    "ちめいしょう",
    "だめぽ",
    "Noooooooooo!!",
    "ＣＭ　はいりまーす",
    "ごめいふくを　おいのりします",
    "めげるな！　がんばれ！",
    "やっちゃったゼ",
    "まものめぇ　おのれぇ",
    "まものは　364の　けいけんちを　てにいれた",
    "${chara}！　へんじをしろ　${chara}ーーーーー！",
    "いま　あなたは　まものに　たおされました",
    "ごめんよ......　エリザ......",
    "さいき　ふのう　－リタイア－",
    "${chara}は　ないたり　わらったり　できなくなった",
    "${chara}は　いよいよもって　しんだ",
    "ご　りんじゅう",
    "むこうに　おはなばたけが　みえます",
    "${chara}！　おうとうしろ　${chara}ーーーーー！"
--死亡時（全ステージ共通部分）
--各ステージ部分
--1a
--1b昼
--2a
--2b
--2c
--3a
--3b
--3c
--3d
--1b夕暮れ
--１ｂ夜
}
end