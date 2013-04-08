function getColor(hp)
  -- RGBを返すように実装してください
  local colors = {
    {228, 238, 109},
    {235, 249, 070},
    {230, 224, 000},
    {192, 220, 000},
    {145, 230, 000},
    {089, 224, 000},
    {000, 210, 071},
    {000, 230, 140},
    {000, 230, 207},
    {000, 197, 230},
    {000, 164, 230},
    {000, 130, 230},
    {000, 097, 230},
    {000, 074, 230},
    {000, 052, 230},
    {000, 019, 230},
    {055, 000, 230},
    {066, 000, 230},
    {088, 000, 230},
    {111, 000, 230},
    {122, 000, 230},
    {166, 000, 230},
    {200, 000, 230},
    {230, 000, 182},
    {230, 000, 138},
    {230, 000, 082},
    {230, 000, 063},
    {230, 000, 015},
    {138, 012, 000},
    {155, 155, 155},
  }
  if hp == 0 then -- HPが0のとき
    return 255, 0, 0 -- 強制的に赤を返します
  end
  --  local key = math.ceil(hp / 3) -- 3で割って切り上げます
  local key = 1 -- 2^nを5回ずつ使った数列を使います 1 2 3 4 5 7 9 11 13 15 19 ...
  if hp >= 155 then
    key = math.ceil((hp - 135) / 32) + 25
  elseif hp >= 75 then
    key = math.ceil((hp - 75) / 16) + 20
  elseif hp >= 35 then
    key = math.ceil((hp - 35) / 8) + 15
  elseif hp >= 15 then
    key = math.ceil((hp - 15) / 4) + 10
  elseif hp >= 5 then
    key = math.ceil((hp - 5) / 2) + 5
  else
    key = hp   
  end

  local length = #colors -- 長さをとります
  key = math.min(length, key) -- keyが長さ以上の時、バグるのでkeyを最大値にします
  return colors[key][1], colors[key][2], colors[key][3] -- key番目のr, g, bを1こずつ返します
end

function getColors(count)
  local colors = {}
  for i = 1, count do
    local length = #colors
    local r, g, b = getColor(i)
    table.insert(colors, {r, g, b})
  end
  return colors
end

--[[ 
モンスター図鑑で利用するモンスターを返してください 
本当は種族を返却させたかったけど、種族だとグラの描画が大変面倒だったのでモンスターを返すようにしてください
図鑑ナンバー対応表
1ジクー
2ツテフェズ
3ギネード
4トメゾラ
5ティエヌティ
6ラガスーワ
7葉っぱ
8すらいむ
9どんぐりぃ
10ちょうちょ
11はち
12どくきのこ
13パンジーさん
14うぃすぷ
15たいふーん
16ミミック
17ますく
18がーごいる
19こうもり
20むかで
21くりすたる
22どらごんきっど
23おうむがい
24新クラゲ
25くじら
26こいん
27はーと
28ほのお
29たまご
30かに
31ねこ
32２そく
33なめこ
34Ｔ２
35わくせい
36exob
37Ａぼすリスアクバー
38Ｂぼす　ないと
39てっきゅう
40いか
41あししろひだり
42あししろみぎ
43あし縞
44あし縞
45かぎあししろひだり
46かぎあししろみぎ
47かぎあし縞
48かぎあし縞
49らすぼす１
50らすぼす２
51びっと
52びっと２
53かわずたん
]]
dictionary = {
  "acorn01",
  "bat01",
  "coin2C2",
  "cryst01",
  "doku01",
  "dragon01",
  "egg2C1",
  "flame2C2",
  "flower01",
  "fortress3A0",
  "gago01",
  "gargoyle3A0",
  "heart2C2",
  "hornet01",
  "iron_boss",
  "jfish3C4",
  "kani2C1",
  "knight_boss",
  "kraken3C0",
  "L_plclaw3C0",
  "L_plfoot3C0",
  "L_strclaw3C0",
  "L_strfoot3C0",
  "R_plclaw3C0",
  "R_plfoot3C0",
  "R_strclaw3C0",
  "R_strfoot3C0",
  "leaf01",
  "level10",
  "mask01",
  "mimic01",
  "moth01",
  "mukade2B0",
  "naut3C5",
  "neko2C0",
  "nisok2C0",
  "pak2C0",
  "slime01",
  "T_flower",
  "T_geek",
  "T_ginet",
  "T_tetufez",
  "T_tnt",
  "toadstool2A0",
  "typhoon3A6",
  "wave3C0",
  "whale3C0",
  "wisp3A2"
}