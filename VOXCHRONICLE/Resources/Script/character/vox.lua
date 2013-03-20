Character = {
  name = "オクス",
  type = CharacterTypeVox,
  getSkills = function(mapName)
    -- mapNameにMapファイルのスクリプト名が渡ってくるので、そこで返す技を変更してください
    if mapName == "hoge" then
      return {}
    elseif mapName == "testMap" then
      return {
        {"attack", 1},
        {"knockback", 11},
        {"slash", 8},
        {"charge", 6},
        {"tension", 4},
        {"change", 3},
        {"shield", 11},
        {"run", 1}
      }
    end
    return {
      {"attack", 1},
      {"knockback", 1},
      {"slash", 1},
      {"charge", 1},
      {"tension", 1},
      {"change", 1},
      {"shield", 1},
      {"run", 1}
    }
  end
}
return Character