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
    elseif mapName == "1a_simple" then
      return {
        {"attack", 1},
        {"knockback", 8},
        {"slash", 7},
        {"charge", 5},
        {"tension", 1},
        {"change", 3},
        {"shield", 6},
        {"run", 1}
      }
    elseif mapName == "tutorial0" then
      return {
        {"attack", 1},
        {"knockback", 9},
        {"slash", 7},
        {"charge", 11},
        {"tension", 5},
        {"change", 11},
        {"shield", 8},
        {"run", 4}
      }
    elseif mapName == "tutorial1" then
       -- チュートリアル「Lesson2」初期状態(チェンジ以外無効)
       return {
        {"attack", 12},
        {"knockback", 12},
        {"slash", 12},
        {"charge", 12},
        {"tension", 12},
        {"change", 11},
        {"shield", 12},
        {"run", 12}
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