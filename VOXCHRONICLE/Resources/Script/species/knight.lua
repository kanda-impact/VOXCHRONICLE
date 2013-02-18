math.randomseed(os.time())
Enemy = {
  name = "ナイト",
  imageName = "knight",
  attack = 1,
  baseExp = 1,
  minRow = 4,
  hasFrame = true,
  counter = 1,
  speed = 2,
  animationFrames = 4,
  performSkill = function(self)
    local isCharge = self:getRegister("swordTurn", 0) > 0 -- チャージ中かどうか
    if self:getRow() < 4 then -- 最前列にいるとき
      if isCharge then -- チャージ中だったら常にswordを返してやる
        return "sword"
      else -- それ以外は乱数によって行動を振り分ける
        math.random(100)
        rand = math.random(100)
        if rand <= 70 then -- 70%で鉄球投げ
          return "ironball"
        elseif rand <= 90 then -- 残り10%で溜め攻撃
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