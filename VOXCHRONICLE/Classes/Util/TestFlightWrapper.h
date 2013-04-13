//
//  TestFlightWrapper.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/9.
//
//

#ifndef __VOXCHRONICLE__TestFlightWrapper__
#define __VOXCHRONICLE__TestFlightWrapper__

#include <iostream>
#include <map>

using namespace std;

namespace TestFlightWrapper {
  class TestFlightWrapper {
   public:
    static void addCustomEnvironmentInformation(const char* information, const char* key);
    static void takeOff(const char* teamToken);
    static void setOptions(map<string, bool> options);
    static void passCheckpoint(const char* checkpointName);
    static void openFeedbackView();
    static void submitFeedback(const char* feedback);
    static void setDeviceIndetifier(const char* deviceIdentifier);
  };
};

#endif /* defined(__VOXCHRONICLE__TestFlightWrapper__) */
