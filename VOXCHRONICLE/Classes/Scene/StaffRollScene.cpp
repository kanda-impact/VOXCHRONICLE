//
//  StaffRollScene.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/3.
//
//

#include "StaffRollScene.h"
#include "Map.h"
#include "TitleScene.h"
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "FileUtils.h"
#include "CCRemoveFromParentAction.h"
#include "PlayLog.h"
#include "ResultScene.h"
#include <sstream>

#define EXT ".caf"

using namespace std;
using namespace boost;

const char* kLuaFileName = "staffroll";

StaffRollScene::StaffRollScene(CCArray* mapNames) {
  CCTextureCache::sharedTextureCache()->removeUnusedTextures();
  _music = new Music(3);
  _music->setTrackDidBackFunction(boost::bind(&StaffRollScene::trackDidBack, this, _1, _2, _3));
  _music->setTrackDidFinishFunction(boost::bind(&StaffRollScene::trackDidFinishPlaying, this, _1, _2, _3, _4));
  _music->setTrackWillFinishFunction(boost::bind(&StaffRollScene::trackWillFinishPlaying, this, _1, _2, _3, _4));
  _texts = CCArray::create();
  _texts->retain();
  
  _currentCharacterType = CharacterTypeVox;
  _maxTrackCount = 0;
  _trackCount = 0;
  _textIndex = 0;
  _lua = LuaObject::create(kLuaFileName);
  _lua->retain();
  _isAddCutin = new deque<bool>();
  CCObject* obj = NULL;
  CCARRAY_FOREACH(mapNames, obj) {
    CCString* mapName = (CCString*)obj;
    Map* map = new Map(mapName->getCString());
    map->autorelease();
    _currentCharacterType = CharacterTypeVox;
    this->pushTracksFor(map->getWayMusic());
    _currentCharacterType = CharacterTypeVox;
    if (map->isBossStage()) {
      this->pushTracksFor(map->getBossMusic());
      this->pushTrack("silent", map->getBossMusic());
    }
  }
  
  _lua->getLuaEngineWithLoad();
  shared_ptr<CCLuaValueArray> texts = _lua->getArray("texts");
  for (CCLuaValueArrayIterator it = texts->begin(); it != texts->end(); ++it) {
    CCLuaValueDict dict = it->dictValue();
    CCArray* t = CCArray::create();
    for (int i = 1; i <= 3; ++i) {
      CCString* str = CCString::create(dict[lexical_cast<string>(i)].stringValue());
      t->addObject(str);
    }
    _texts->addObject(t);
  }
  
  CCMenuItem* backItem = CCMenuItemImage::create("credit_back.png",
                                                 "credit_back_pressed.png",
                                                 this,
                                                 menu_selector(StaffRollScene::onBackButtonPressed));
  CCMenu* backMenu = CCMenu::create(backItem, NULL);
  backMenu->setPosition(ccp(440, 290));
  this->addChild(backMenu);
}

StaffRollScene::~StaffRollScene() {
  delete _isAddCutin;
  _texts->release();
  _music->release();
  _lua->release();
}

void StaffRollScene::onEnterTransitionDidFinish() {
  _music->play();
}

void StaffRollScene::trackDidBack(VISS::Music *music, VISS::Track *currentTrack, int trackNumber) {
}

void StaffRollScene::trackWillFinishPlaying(VISS::Music *music, VISS::Track *currentTrack, VISS::Track *nextTrack, int trackNumber) {
  ++_trackCount;
  if (_trackCount >= _maxTrackCount) {
    _music->stop(); // 音楽止めて
    this->scheduleOnce(schedule_selector(StaffRollScene::onFinishPlaying), 0.5f);
  }
}

void StaffRollScene::trackDidFinishPlaying(VISS::Music *music, VISS::Track *finishedTrack, VISS::Track *nextTrack, int trackNumber) {
  // カットインを追加する
  bool isAdd = (*_isAddCutin)[_trackCount];
  if (_textIndex < _texts->count() && (isAdd || _trackCount == 1 || _trackCount >= _maxTrackCount - 5)) {
    CCArray* texts = (CCArray*)_texts->objectAtIndex(_textIndex);
    string section = ((CCString*)texts->objectAtIndex(0))->getCString();
    string text = ((CCString*)texts->objectAtIndex(1))->getCString();
    string description = ((CCString*)texts->objectAtIndex(2))->getCString();
    CutinType sectionCutinType = CutinTypeNormal;
    if (_textIndex < _texts->count() - 1 && _textIndex > 0) {
      CCArray* prevTexts = (CCArray*)_texts->objectAtIndex(_textIndex - 1);
      string prevSection = ((CCString*)prevTexts->objectAtIndex(0))->getCString();
      
      CCArray* nextTexts = (CCArray*)_texts->objectAtIndex(_textIndex + 1);
      string nextSection = ((CCString*)nextTexts->objectAtIndex(0))->getCString();
      
      if (section.length() > 0 && nextSection.length() == 0) {
        sectionCutinType = CutinTypeIn;
      } else if (section.length() == 0 && nextSection.length() > 0) {
        sectionCutinType = CutinTypeOut;
      } else if (section.length() > 0 && prevSection.length() == 0 && nextSection.length() > 0) {
        sectionCutinType = CutinTypeNormal;
      }
    }
    
    this->addCutin(section.c_str(), TextTypeSection, sectionCutinType);
    
    if (text.length() > 0) {
      this->addCutin(text.c_str(), TextTypeText, CutinTypeNormal);
    }
    if (description.length() > 0) {
      this->addCutin(description.c_str(), TextTypeDescription, CutinTypeNormal);
    }
    ++_textIndex;
  }
}

void StaffRollScene::addCutin(const char *text, TextType type, CutinType cutinType) {
  int heights[] = {250, 150, 80};
  int sizes[] = {48, 36, 16};
  int height = heights[type];
  int size = sizes[type];
  CCLabelTTF* label = NULL;
  if (cutinType == CutinTypeOut && type == TextTypeSection) {
    label = (CCLabelTTF*)this->getChildByTag(type); // 出て行くとき、古いセクションを使い回す
  } else {
    label = CCLabelTTF::create(text, "Helvetica", size); // それ以外の時は新しく生成する
    label->setPosition(ccp(0, height));
  }
  
  float duration = _music->getCurrentMainTrack()->getDuration();
  if (label != NULL) {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCArray* actions = CCArray::create();
    if (cutinType != CutinTypeOut) {
      actions->addObject(CCMoveTo::create(duration * 0.125, ccp(size.width / 2.0, height)));
      actions->addObject(CCDelayTime::create(duration * 0.75));
      this->addChild(label, 0, type);
    }
    if (cutinType == CutinTypeOut) {
      actions->addObject(CCDelayTime::create(duration * 0.875));
    }
    if (cutinType != CutinTypeIn) {
      actions->addObject(CCMoveTo::create(duration * 0.125, ccp(size.width, height)));
      actions->addObject(CCRemoveFromParentAction::create());
    }
    label->runAction(CCSequence::create(actions));
  }
}

void StaffRollScene::onFinishPlaying(cocos2d::CCObject *sender) {
  PlayLog* log = (PlayLog*)this->getUserObject();
  CCScene* scene = CCScene::create();
  if (log == NULL) {
    scene->addChild(TitleScene::create());
  } else { // PlayLogがあったらResultSceneへ
    ResultScene* layer = ResultScene::create();
    layer->setPlayLog(log);
    layer->buildUI();
    scene->addChild(layer);
  }
  CCTransitionFade* fade = CCTransitionFade::create(2.0f, scene);
  CCDirector::sharedDirector()->replaceScene(fade);
  
}

void StaffRollScene::pushTracksFor(MusicSet* set) {
  _lua->getLuaEngineWithLoad();
  shared_ptr<CCLuaValueArray> tracks = _lua->getArray("tracks");
  for (CCLuaValueArrayIterator it = tracks->begin(); it != tracks->end(); ++it) {
    string track = it->stringValue();
    if (track == "intro") {
      this->pushTracks("intro", set->getIntroCount(), set);
    } else if (track == "finish") {
      this->pushTracks("finish", set->getFinishCount(), set);
    } else if (track == "change") {
      if (_currentCharacterType == CharacterTypeVox) {
        _currentCharacterType = CharacterTypeLaska;
        this->pushTrack("voxchange0", set);
      } else {
        _currentCharacterType = CharacterTypeVox;
        this->pushTrack("lskchange0", set);
      }
    } else if (track == "wait") {
      if (_currentCharacterType == CharacterTypeVox) {
        this->pushWaitTracks("vox", set);
      } else {
        this->pushWaitTracks("lsk", set);
      }
    } else if (track == "qte") {
      if (set->getType() == MusicSetTypeBoss) {
        this->pushTrack("qte", set);
      }
    } else {
      this->pushTrack(track.c_str(), set);
    }
  }
}

void StaffRollScene::pushTrack(const char *identifier, MusicSet* set) {
  stringstream ss;
  ss << identifier << EXT;
  _music->pushTrack(set->getPrefixedMusicName(ss.str().c_str()).c_str(), MusicChannelMain);
  // ドラムとリフは仮ですが、いずれランダムで載るようにする？
  _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelCounter);
  _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelDrum);
  ++_maxTrackCount;
  _isAddCutin->push_back(true);
}

void StaffRollScene::pushTracks(const char *identifier, int count, MusicSet* set) {
  for (int i = 0; i < count; ++i) {
    stringstream ss;
    ss << identifier << i << EXT;
    _music->pushTrack(set->getPrefixedMusicName(ss.str().c_str()).c_str(), MusicChannelMain);
    _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelCounter);
    _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelDrum);
    ++_maxTrackCount;
    _isAddCutin->push_back(false);
  }
}

void StaffRollScene::pushWaitTracks(const char *characterIdentifier, MusicSet* set) {
  int waitCount = set->getWaitCount();
  for (int i = 0; i < waitCount; ++i) {
    stringstream ss;
    if (!set->isCommon("wait")) {
      ss << characterIdentifier;
    }
    ss << "wait" << i << EXT;
    _music->pushTrack(set->getPrefixedMusicName(ss.str().c_str()).c_str(), MusicChannelMain);
    _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelCounter);
    _music->pushTrack(set->getPrefixedMusicName((string("silent") + string(EXT)).c_str()).c_str(), MusicChannelDrum);
    _isAddCutin->push_back(false);
    ++_maxTrackCount;
  }
}

void StaffRollScene::onBackButtonPressed(cocos2d::CCObject *sender) {
  CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileUtils::getFilePath("SE/cancel.mp3").c_str());
  _music->stop();
  this->onFinishPlaying(sender);
}