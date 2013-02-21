//
//  MusicManager.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/4.
//
//

#include "MusicManager.h"
#include <boost/lexical_cast.hpp>
#include "BufferCache.h"

#define DEFAULT_EXT ".caf"

using namespace VISS;
using namespace boost;

MusicManager::MusicManager(Music* music, MusicSet* musicSet, EnemyManager* enemyManager, CharacterManager* characterManager) {
  _music = music;
  music->retain();
  _musicSet = musicSet;
  musicSet->retain();
  _enemyManager = enemyManager;
  enemyManager->retain();
  _characterManager = characterManager;
  characterManager->retain();
  _extension = DEFAULT_EXT;
  _minDrumScore = 0;
  _introCount = 0;
  _finishCount = 0;
  _isImpact = false;
}

MusicManager::~MusicManager() {
  _music->release();
  _musicSet->release();
  _enemyManager->release();
  _characterManager->release();
}

void MusicManager::setExtension(const char *ext) {
  _extension = ext;
}

int MusicManager::calcDrumScore () {
  // KYDS
  int score = 0;
  // 敵の数によって分岐
  if (_enemyManager->getEnemies()) {
    int count = _enemyManager->getEnemies()->count();
    if (count == 1 || count == 2) {
      score += 1;
    } else if (count == 3 || count == 4) {
      score += 2;
    } else if (count >= 5) {
      score += 3;
    }
  }
  Enemy* nearest = _enemyManager->getNearestEnemy();
  if (nearest) {
    int row = nearest->getRow();
    if (row <= 3) {
      score += 2;
    } else if (row <= 4) {
      score += 1;
    } else {
      score += 0;
    }
  }
  int tension = _characterManager->getTension();
  score += tension;
  return max(_minDrumScore, min(score, 4));
}

string MusicManager::getTrackFileName(const char *trackName) {
  return _musicSet->getPrefixedMusicName((string(trackName) + _extension).c_str());
}

void MusicManager::pushIntroTracks() {
  string main, counter, drum;
  int introCount = _musicSet->getIntroCount();
  if (introCount == 0) {
    // イントロなしのとき、いきなり曲を鳴らします
    _music->pushTrack(this->getTrackFileName("wait0").c_str(), MusicChannelMain);
    _music->pushTrack(this->getTrackFileName("counter0").c_str(), MusicChannelCounter);
    _music->pushTrack(this->buildTrackName("drum", NULL, 0).c_str(), MusicChannelDrum);
  } else {
    // イントロありのとき、イントロの数だけpushします
    int maxIntroCount = _musicSet->getIntroCount();
    for (int i = 0 ; i < maxIntroCount; ++i) {
      _music->pushTrack(this->getTrackFileName((string("intro") + lexical_cast<string>(i)).c_str()).c_str(), MusicChannelMain);
      _music->pushTrack(this->getTrackFileName("silent").c_str(), MusicChannelCounter);
      _music->pushTrack(this->getTrackFileName("silent").c_str(), MusicChannelDrum);
    }
  }
  _music->getTrack(1)->setVolume(0);
  _music->getTrack(2)->setVolume(0.7);
}

void MusicManager::pushFinishTracks() {
  this->pushFinishTracks(0, _musicSet->getFinishCount());
}

void MusicManager::pushFinishTracks(int from, int to) {
  // フィニッシュ曲をpushしまくる
  for (int i = from ; i < to; ++i) {
    _music->pushTrack(this->getTrackFileName((string("finish") + lexical_cast<string>(i)).c_str()).c_str(), MusicChannelMain);
    _music->pushTrack(this->getTrackFileName("silent").c_str(), MusicChannelCounter);
    _music->pushTrack(this->getTrackFileName("silent").c_str(), MusicChannelDrum);
  }
}

void MusicManager::pushSilentTracks() {
  for (int i = 0; i < MusicChannelNum; ++i) {
    _music->pushTrack(this->getTrackFileName("silent").c_str(), i);
  }
}

void MusicManager::pushNextTracks(Skill* skill, SkillPerformInfo& performInfo) {
  // リフの設定
  Enemy* nearest = _enemyManager->getNearestEnemy();
  if (nearest) {
    int counterNum = nearest->getCounter();
    Track* track = _music->pushTrack(this->getTrackFileName((string("counter") + lexical_cast<string>(counterNum)).c_str()).c_str(), 1);
    int row = nearest->getRow();
    int denominator = (MAX_ROW + 1) * MAX_ROW / 2.0;
    int numerator = ((MAX_ROW - row) + 1) * (MAX_ROW - row) / 2.0;
    float volume = 0.5 + 1.0 * numerator / denominator;
    track->setVolume(volume);
  } else {
    Track* track = _music->pushTrack(this->getTrackFileName("silent").c_str(), MusicChannelCounter);
    track->setVolume(0);
  }
  
  // メロディの設定
  SkillPerformType performType = SkillPerformTypeNone;
  string name = this->checkSkillTrackName(skill, performType);
  performInfo.skillTrackName = name;
  performInfo.type = performType;
  performInfo.skill = skill;
  _music->pushTrack(this->getTrackFileName(name.c_str()).c_str(), MusicChannelMain);
  
  // ドラムの設定
  stringstream drumFileStream;
  if (_characterManager->getTension() > 0 && skill != NULL && string(skill->getIdentifier()) != "tension" && performInfo.type == SkillPerformTypeSuccess) {
    // テンションが1以上で、skillがあるとき、かつテンションじゃないとき、かつ攻撃ピロってないときインパクトをならしてやる
    drumFileStream << this->buildTrackName("impact", NULL, _characterManager->getTension() - 1);
  } else {
    int drumLevel = this->calcDrumScore();
    drumFileStream << this->buildTrackName("drum", NULL, drumLevel);
  }
  _music->pushTrack(this->getTrackFileName(drumFileStream.str().c_str()).c_str(), MusicChannelDrum);
}

string MusicManager::checkSkillTrackName(Skill* skill, SkillPerformType& performeType) {
  performeType = SkillPerformTypeNone;
  if (skill) {
    _characterManager->setWaitTurn(_characterManager->getWaitTurn() + 1);
    if (_characterManager->getWaitTurn() == skill->getTurn()) {
      string trackName = "";
      if (_characterManager->getLastSkill() &&
          string(_characterManager->getLastSkill()->getIdentifier()) != string(skill->getIdentifier())) {
        _characterManager->setRepeatCount(0);
      }
      trackName = this->buildTrackName(skill->getIdentifier().c_str(), skill, _characterManager->getRepeatCount());
      if (skill->isLoop()) {
        _characterManager->setRepeatCount((_characterManager->getRepeatCount() + 1) % skill->getMaxRepeat());
      } else {
        _characterManager->setRepeatCount(min(_characterManager->getRepeatCount() + 1, skill->getMaxRepeat() - 1));
      }
      _characterManager->setLastSkill(skill);
      _characterManager->setCurrentSkill(NULL);
      _characterManager->setWaitTurn(0);
      
      performeType = SkillPerformTypeSuccess;
      bool isMiss = true;
      // 攻撃ミスってたら失敗扱いに
      CCArray* targets = _enemyManager->getTargets(skill);
      if (targets->count() > 0) {
        for (int i = 0; i < targets->count(); ++i) {
          Enemy* enemy = (Enemy*)targets->objectAtIndex(i);
          DamageType damageType = DamageTypeNone;
          enemy->damage(skill, _characterManager, damageType, true); // ダメージは与えずに結果だけ取り出す
          if (damageType != DamageTypePhysicalInvalid && damageType != DamageTypeMagicalInvalid && damageType != DamageTypeNoDamage) {
            isMiss = false;
          }
        }
      } else {
        isMiss = false;
      }
      if (skill->getMP() > _characterManager->getMP()) { // MP足りてないとき、失敗に
        performeType = SkillPerformTypeFailure;
        isMiss = true;
      }
      
      if (performeType == SkillPerformTypeFailure || isMiss) { // 失敗したとき、もしくはピロったとき、miss音を返す
        return this->buildTrackName("miss", NULL, -1);
      } else {
        return trackName;
      }
    } else {
      _characterManager->setCurrentSkill(skill);
      performeType = SkillPerformTypeCharge;
      std::stringstream ss;
      ss << _characterManager->getCurrentCharacter()->getIdentifier() << skill->getIdentifier() << "_charge" << (_characterManager->getWaitTurn() - 1); // チャージ中の時、チャージ音返す
      return ss.str().c_str();
    }
  } else {
    if (_characterManager->getLastSkill() == NULL) {
      _characterManager->setRepeatCount((_characterManager->getRepeatCount() + 1) % _musicSet->getWaitCount());
    } else {
      _characterManager->setRepeatCount(0);
    }
    _characterManager->setLastSkill(skill);
  }
  return this->buildTrackName("wait", NULL, _characterManager->getRepeatCount());
}

string MusicManager::buildTrackName(const char* skillIdentifier, Skill *skill, int repeatCount, Character* currentCharacter) {
  stringstream ss;
  if ((skill == NULL || skill->isCommon()) && _musicSet->isCommon(skillIdentifier)) {
    // スキルのcommonがfalseのとき、曲名にキャラ名が付かない
    // tension0.wav
    ss << skillIdentifier;
    if (repeatCount >= 0) {
      ss << repeatCount;
    }
  } else {
    // commonがtrueのとき、曲名にキャラ名が付く
    // ex: voxattack0.wav
    ss << currentCharacter->getIdentifier() << skillIdentifier;
    if (repeatCount >= 0) {
      ss << repeatCount;
    }
  }
  return ss.str();
}

string MusicManager::buildTrackName(const char *skillIdentifier, Skill *skill, int repeatCount) {
  return this->buildTrackName(skillIdentifier, skill, repeatCount, _characterManager->getCurrentCharacter());
}

int MusicManager::getIntroCount() {
  return _introCount;
}

void MusicManager::setIntroCount(int count) {
  _introCount = count;
}

int MusicManager::getFinishCount() {
  return _finishCount;
}

void MusicManager::setFinishCount(int count) {
  _finishCount = count;
}

Music* MusicManager::getMusic() {
  return _music;
}

MusicSet* MusicManager::getMusicSet() {
  return _musicSet;
}

void MusicManager::setMusic(Music *music) {
  if (_music) {
    _music->release();
  }
  _music = music;
  if (music) {
    music->retain();
  }
}

void MusicManager::setMusicSet(MusicSet *set) {
  if (_musicSet) {
    _musicSet->release();
  }
  if (_musicSet != set) {
    _musicSet = set;
    if (set) {
      set->retain();
    }
    BufferCache::sharedCache()->purgeAllBuffers();
  }
}

void MusicManager::setMinDrumScore(int min) {
  _minDrumScore = min;
}

void MusicManager::preloadAllTracks(CharacterManager* manager) {
  CCArray* characters = manager->getCharacters();
  CCObject* obj0 = NULL;
  CCARRAY_FOREACH(characters, obj0) {
    Character* chara = (Character*)obj0;
    CCArray* skills = chara->getSkills();
    CCObject* obj1 = NULL;
    CCARRAY_FOREACH(skills, obj1) {
      Skill* skill = (Skill*)obj1;
      int repeat = skill->getMaxRepeat();
      for (int i = 0; i < repeat; ++i) {
        string file = buildTrackName(skill->getIdentifier().c_str(), skill, i, chara);
        BufferCache::sharedCache()->addBuffer(this->getTrackFileName(file.c_str()).c_str());
      }
    }
  }
  this->preloadMusic("wait", _musicSet->getWaitCount());
  this->preloadMusic("drum", 5);
  this->preloadMusic("impact", 4);
  this->preloadMusic("intro", _musicSet->getIntroCount());
  this->preloadMusic("finish", _musicSet->getFinishCount());
}

void MusicManager::preloadMusic(const char *trackName, int maxCount) {
  for (int i = 0; i < maxCount; ++i) {
    string file = buildTrackName(trackName, NULL, i);
    BufferCache::sharedCache()->addBuffer(this->getTrackFileName(file.c_str()).c_str());
  }
}