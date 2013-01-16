//
//  FileUtils.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/21.
//
//

#ifndef __VOXCHRONICLE__FileUtils__
#define __VOXCHRONICLE__FileUtils__

#include <iostream>
#include <string>

using namespace std;

class FileUtils {
public:
  static string getFilePath(const char* filepath);
  static string getMusicExt();
};

#endif /* defined(__VOXCHRONICLE__FileUtils__) */
