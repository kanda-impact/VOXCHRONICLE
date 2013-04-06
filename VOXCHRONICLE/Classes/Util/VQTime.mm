//
//  VQTime.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/6.
//
//

#include "VQTime.h"

static VQTime* _shared = NULL;

VQTime* VQTime::sharedTime() {
  if (!_shared) {
    _shared = new VQTime();
  }
  return _shared;
}

int VQTime::getCurrentHour() {
  NSDate* date = [NSDate date];
  NSCalendar* calendar = [NSCalendar currentCalendar];
  NSDateComponents* components = [calendar components:NSHourCalendarUnit fromDate:date];
  int hour = components.hour;
  return hour;
}