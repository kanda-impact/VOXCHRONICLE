Skill = {
  name = "パワーチャージ",
  identifier = "tension",
  effectFrames = 0,
  mp = 0,
  se = true,
  tensionLevel = 0,
  common = true,
  cutinType = EffectLayerCutinTypeNormal,
  maxRepeat = 4,
  turn = 1,
  loop = false,
  canRepeat = true,
  keepTension = true,
  performSkill = function(self, target, characterManager, enemyManager)
    characterManager:addTension(1)
    local tension = characterManager:getTension()
    local layer = EffectLayer:sharedLayer()
    local node = CCNode:create()
    local tensionLabel = CCLabelAtlas:create(tension.."", "tension_number.png", 65, 97.5, string.byte("0"))
    local cross = CCSprite:create("tension_cross.png")
    cross:setAnchorPoint(ccp(0.5, 0.5))
    tensionLabel:setAnchorPoint(ccp(0.5, 0.5))
    cross:setPosition(ccp(0, 15))
    node:setPosition(ccp(55, -10))
    node:addChild(tensionLabel)
    tensionLabel:setPosition(ccp(80, 10))
    node:addChild(cross)
    layer:setCutinExtension(node)
  end,
  getPower = function(characterManager)
    return 0
  end,
  skillRange = SkillRangeSelf,
  skillType = SkillTypeNone,
  getMessageTable = function(self, targets, map, characterManager, enemyManager)
    chara = characterManager:getCurrentCharacter():getName()
    local tension = characterManager:getTension()
    if tension >= 3 then -- テンションマックスのとき
    -- この関数はワザの仕様直前に呼ばれるので、3以上だったら最大値判定にしてやる
      return {
        "さいだいパワーだ！！",
        "ＭＡＸ！ハイテンション！！",
        "ぜんりょくぜんかいっ！！",
        "ボルテージ　さいだい！",
        "もえつきるほど　ヒートッ！",
        "さいきょうの　パワー　みせてやる",
        "BEATはさいこうちょうだ",
        "うぉぉおおお！",
        "マキシマム　パワー！！",
        "POWER MAXIMAM!!"
      }
    end
    return { -- 通常時
      _("#{chara}は　ちからをためた"),
      _("#{chara}の　テンションがあがっていく"),
      _("#{chara}は　りきんでいる"),
      _("#{chara}の　ボルテージが　ふくれあがる"),
      "もえあがる　こころ",
      "せいめいりょくが　たかまる！",
      "たかまれ　われらの　BEAT!!",
      "パワー　ちゃーーじ！！！",
      "ちからが　みなぎっていく！！",
      "もえあがる　こころ",
      "ぼくらの　BRAVEが　たかまる",
      "エナジーが　たかまっていく",
      "ちからが　たまるぜ",
      "パワーーー　キターーーー！",
      "パワーが　みなぎってきたぞ",
    }
  end,
}
