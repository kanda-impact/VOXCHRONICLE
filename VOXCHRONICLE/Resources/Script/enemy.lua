function getColor(hp)
  -- RGBを返すように実装してください
  local colors = {
    {255, 252, 108},
    {255, 157, 76},
    {255, 240, 48},
    {138, 255, 200},
    {135, 255, 89},
    {67, 255, 163},
    {146, 182, 255},
    {61, 166, 255},
    {86,  109, 255},
    {66, 178,  255},
    {161,  104, 255},
    {75, 70, 255},
    {0, 145, 193},
    {168, 168, 168},
    {0, 245, 163},
    {0, 250, 3},
    {2, 203, 0},
    {181, 207, 0},
    {232, 175, 0},
    {141, 109, 0},
    {163, 0, 0 },
    {217, 0, 0 },
    {255, 102, 162},
    {255, 55, 247},
    {142, 69, 255},
    {208, 0,  126 },
    {251, 0,  123 },
    {184, 0, 187  },
    {112, 0, 205  },
    {187, 0, 99   },
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