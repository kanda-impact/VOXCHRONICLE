Character = {
  name = "ラスカ",
  type = CharacterTypeLaska,
  getSkills = function(mapName)
    return {
      {"magic", 1},
      {"bow", 10},
      {"thunder", 6},
      {"cure", 8},
      {"tension", 4},
      {"change", 2},
      {"shield", 10},
      {"run", 1}
    }
  end
}
return Character