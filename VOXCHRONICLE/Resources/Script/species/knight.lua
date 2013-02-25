math.randomseed(os.time())
Enemy = {
  name = "ナイト",
  imageName = "knight",
  attack = 1,
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
  animationFrames = 4,
  performSkill = function(self)
    local isCharge = self:getRegister("swordTurn", 0) > 0 -- チャージ中かどうか
    self:setCounter(-1)
    if self:getRow() < 4 then -- 最前列にいるとき
      if isCharge then -- チャージ中だったら常にswordを返してやる
        self:setCounter(2)
        return "sword"
      else -- それ以外は乱数によって行動を振り分ける
        math.random(100)
        rand = math.random(100)
        if rand <= 70 then -- 70%で鉄球投げ
          self:setCounter(1)
          return "ironball"
        elseif rand <= 90 then -- 残り10%で溜め攻撃
          self:setCounter(2)
          return "sword"
        end
      end
    else -- 最前列にいなかったら
      -- チャージをリセットしてやる（ノックバックなどで飛ばされたとき）
      if isCharge then
        self:setRegister("swordTurn", 0)
        self:setDefaultAnimationClip()
      end
    end
    return ""
  end
}

return Enemy