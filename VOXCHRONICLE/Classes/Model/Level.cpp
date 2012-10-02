//
//  Level.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/29.
//
//

#include "Level.h"

Level::Level(int level) {
  _level = level;
}

int Level::getLevel() {
  return _level;
}

list< pair<string, int> > Level::getEnemyTable() {
  return _enemyTable;
}

void Level::setEnemyTable(list<pair<string, int> > table) {
  _enemyTable = table;
}

float Level::getEnemyPopRate() {
  return _enemyPopRate;
}

void Level::setEnemyPopRate(float rate) {
  _enemyPopRate = rate;
}