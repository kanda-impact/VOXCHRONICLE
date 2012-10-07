function getExp(level)
  --[[
    経験値テーブルを実装できます
    レベルlevelを引数としたときに、そのレベルになるために最低限必要な経験値をreturnしてください
  ]]
  local exp = 0
  for l = 2, level do
    exp = exp + math.pow(l / 2 + 3 , 2)
  end
  return exp
end


function getLevel(exp)
  --[[
    経験値に対応したレベルを返します。
    ここは変えない方がよさげです
  ]]
  for level = 1, 30 do
    if math.floor(getExp(level)) > exp then
      return level - 1
    end
  end
  return 1
end

function getMaxHP(level)
  return 5
end

function getMaxMP(level)
  return 5
end
