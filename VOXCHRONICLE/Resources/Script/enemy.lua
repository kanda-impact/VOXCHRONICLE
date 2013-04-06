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
]]
dictionary = {
  "acorn01",
  "slime01",
  "mask01",
  "fortress3A0",
  "knight_boss",
  "kraken3C0"
}