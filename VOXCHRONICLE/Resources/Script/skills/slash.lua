Skill = {
  name = "オクススラッシュ",
  identifier = "slash",
  effectFrames = 4,
  mp = 0,
  se = true,
  tensionLevel = 1,
  common = false,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 1,
  turn = 1,
  loop = true,
  canRepeat = true,
  skillRange = SkillRangeFront,
  skillType = SkillTypePhysical,
  getPower = function(characterManager)
    local tension = characterManager:getTension()
    t = {0, 4, 6, 9, 12}
    return t[tension + 1]
  end,
  messages = {
    "オクスは　おもいきり　けんをふりまわした",
    "ひっさつの　オクススラッシュ！！",
    "オクスの　はんいこうげき！",
    "オクスの　けんから　しょうげきはが！！",
    "いくぜ　オクススラッシュ！！",
    "ちからをこめた　いちげき！！",
    "ぜんたいを　きりきざむ！！　オクススラッシュ！"
  }
}
