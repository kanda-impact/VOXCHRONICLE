-- 注: local宣言された変数は取得不可能
function _(str)
  str = string.gsub(str, "#{(%w+)}",
  function (n)
    return _G[n]
  end
  )
  return str
end
