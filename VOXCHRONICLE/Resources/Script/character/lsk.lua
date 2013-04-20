Character = {
  name = "ラスカ",
  type = CharacterTypeLaska,
  getSkills = function(mapName)
    if mapName == "testMap" then
      return {
        {"magic", 1},
        {"bow", 11},
        {"thunder", 6},
        {"cure", 8},
        {"tension", 4},
        {"change", 3},
        {"shield", 11},
        {"run", 1}
      }
    elseif mapName == "1a_simple" then
      return {
        {"magic", 1},
        {"bow", 4},
        {"thunder", 7},
        {"cure", 5},
        {"tension", 1},
        {"change", 3},
        {"shield", 6},
        {"run", 1}
      }
    elseif mapName == "tutorial1" then
    -- チュートリアル「Lesson2」初期状態(最初は攻撃・ガード・進むのみ)
      return {
      {"magic", 11},
      {"bow", 12},
      {"thunder", 13},
      {"cure", 14},
      {"tension", 13},
      {"change", 15},
      {"shield", 20},
      {"run", 20}
      }
    end
    return {
      {"magic", 1},
      {"bow", 1},
      {"thunder", 1},
      {"cure", 1},
      {"tension", 1},
      {"change", 1},
      {"shield", 1},
      {"run", 1}
    }
  end
}
return Character
