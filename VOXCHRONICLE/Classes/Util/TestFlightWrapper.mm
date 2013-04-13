//
//  TestFlightWrapper.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2013/4/9.
//
//

#import "TestFlight.h"
#include "TestFlightWrapper.h"

void Kawaz::TestFlightWrapper::addCustomEnvironmentInformation(const char* information, const char* key) {
  [TestFlight addCustomEnvironmentInformation:[NSString stringWithCString:information encoding:NSASCIIStringEncoding]
                                       forKey:[NSString stringWithCString:key encoding:NSASCIIStringEncoding]];
}

void Kawaz::TestFlightWrapper::takeOff(const char *teamToken) {
  [TestFlight takeOff:[NSString stringWithCString:teamToken encoding:NSASCIIStringEncoding]];
}

void Kawaz::TestFlightWrapper::setOptions(map<string, bool> options) {
  NSMutableDictionary* dictionary = [NSDictionary dictionary];
  for (map<string, bool>::iterator it = options.begin(); it != options.end(); ++it) {
    NSString* key = [NSString stringWithCString:it->first.c_str() encoding:NSASCIIStringEncoding];
    bool value = it->second;
    [dictionary setObject:[NSNumber numberWithBool:(BOOL)value] forKey:key];
  }
  [TestFlight setOptions:dictionary];
}

void Kawaz::TestFlightWrapper::passCheckpoint(const char *checkpointName) {
  [TestFlight passCheckpoint:[NSString stringWithCString:checkpointName encoding:NSASCIIStringEncoding]];
}

void Kawaz::TestFlightWrapper::openFeedbackView() {
  [TestFlight openFeedbackView];
}

void Kawaz::TestFlightWrapper::submitFeedback(const char *feedback) {
  [TestFlight submitFeedback:[NSString stringWithCString:feedback encoding:NSASCIIStringEncoding]];
}

void Kawaz::TestFlightWrapper::setDeviceIndetifier(const char *deviceIdentifier) {
  [TestFlight passCheckpoint:[NSString stringWithCString:deviceIdentifier encoding:NSASCIIStringEncoding]];
}