function getLevel(exp)
  --[[
  --経験値テーブルを実装できます
  --経験値expを引数としたときにレベルを計算してreturnしてください
  ]]
  local l = 1
  while true do
    exp = exp - math.pow(l / 2 + 3, 2)
    if exp <= 0 then
      return l
    end
    l = l + 1
  end
  return 1
end
