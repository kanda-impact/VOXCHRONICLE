Map = {
  name = "草原",
  wayMusic = "volca",
  bossMusic = "",
  backgroundImage = "field_background0.png",
  skin = "skinB",
  ending = "",
  nextMaps = {"2b_cave","2c_cyber"},
  initialLevel = 1,
  maxLevel = 10,
  getEnemyTable = function(level)
    if level <= 5 then
      return {slime0 = 5}
    else
      return {slime0 = 1}
    end
  end,
  onLevelUp = function(self, characterManager, enemyManager)
    local num = (characterManager:getLevel() - 1) % 3
    local imageName = "field_background"..num..".png"
    self:changeBackgroundImage(imageName)
  end,
  getEnemyPopRate = function(level)
    return 0.7
  end,
  fixedEnemies = {
    --{"level10",0}
  }
}
