Character = {
  name = "オクス",
  type = CharacterTypeVox,
  getSkills = function(mapName)
    -- mapNameにMapファイルのスクリプト名が渡ってくるので、そこで返す技を変更してください
    if mapName == "hoge" then
      return {}
    end
    return {
      {"attack", 1},
      {"knockback", 10},
      {"slash", 8},
      {"charge", 6},
      {"tension", 4},
      {"change", 2},
      {"shield", 10},
      {"run", 1}
    }
  end
}
return Character