//
//  CCAchievementDescription.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/1.
//
//

#include "CCAchievementDescription.h"

const char* CCAchievementDescription::getIdentifier() {
  return _identifier;
}

const char* CCAchievementDescription::getTitle() {
  return _title;
}

const char* CCAchievementDescription::getUnachievedDescription() {
  return _unachievedDescription;
}

const char* CCAchievementDescription::getAchievedDescription() {
  return _archievedDescription;
}

int CCAchievementDescription::getMaximumPoints() {
  return _maximumPoints;
}

bool CCAchievementDescription::isHidden() {
  return _hidden;
}

bool CCAchievementDescription::isReplayable() {
  return _replayable;
}

CCTexture2D* CCAchievementDescription::getImage() {
  return NULL;
}