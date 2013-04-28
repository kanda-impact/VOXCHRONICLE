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
    local isCharge = self:getRegister("swordTurn", 0) > 0 -- チャージ中かどうか
    local turn = self.__IRegister__:getRegister("turn", 0)
    self.__IRegister__:setRegister("turn", turn + 1)
    local guarded = self.__IRegister__:getBool("isGuarded")
    math.random(100)
    if turn > 2 then
      local r = math.random(100)
      if guarded then
        return ""
      elseif r < 100 or isCharge then
        return "sword"
      end
    end
    return ""
  end
}

return Enemy