math.randomseed(os.time())
Enemy = {
  name = "ウィル・デ・ヤゥク",
  imageName = "knight",
  attack = 20,
  baseExp = 1,
  hasFrame = true,
  counter = 0,
  getSpeed = function(enemy, characterManager)
    local row = enemy:getRow()
    if row < 4 then -- 4列目より前に行ったとき、速度を0にします
      return 0
    end
    return 1
  end,
  getFrequency = function(enemy, characterManager)
    return 1
  end,
  disableSkills = {"knockback"},
  description = [[
  かつてこの城の主に仕えていたナイトの亡霊。その目的はとうの昔に忘れて、目の前の敵と戦う事だけに執着する存在に成り果ててしまった。
  ]],
  habitat = "",
  animationFrames = 4,
  performSkill = function(self)
    return "sword"
  end
}

return Enemy