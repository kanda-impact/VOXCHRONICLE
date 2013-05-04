--[[
  音楽データ定義クラスです。
  各ステージの音楽について定義できます
  name : 曲名です。ゲーム内ではおそらく使用されないので好きな曲名を付けてください
  composer : 作曲者名です。作曲者に敬意を払って一応指定できますが、ゲーム内では利用されません
  prefix : 曲ファイルのプレフィックスです Music/<prefix>/<prefix>_<trackname>.mp3のファイルが読まれます
  type : 曲セットの種類です。道中曲の場合、MusicSetTypeWay ボス曲の場合、MusicSetTypeBossを指定してください
  introCount : イントロが何小節あるかを指定します。0の場合はイントロを鳴らしません
  finishCount : フィニッシュ曲が何小節あるか指定します。0の場合はフィニッシュ曲を鳴らしません
  common : wait/shield/run/tensionについて、オクス、ラスカ共通の音を利用する場合はtrueを、キャラ毎に変えたいとか面倒なことを考えている場合はfalseを指定してください
  ignoreDrums : ドラムを無効にしたいトラック名を含むリストを定義してください。例えば"voxattack1"を要素にすると、攻撃の2発目だけドラムが鳴りません。
  これを指定することで、ある曲だけ別のドラムを含めるなどと行った面倒なことができます
--]]


Music = {
  name = "古城ルパティナ",
  composer = "Tetu_fs",
  prefix = "dub",
  type = MusicSetTypeWay,
  introCount = 2,
  finishCount = 2,
  waitCount = 1,
  common = {
    wait = true,
    shield = true,
    run = true,
    tension = true,
    miss = true,
    drum = true,
    impact = true
  },
  ignoreDrums = {
  }
}

return Music