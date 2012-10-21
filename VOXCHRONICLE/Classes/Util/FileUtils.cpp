//
//  FileUtils.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/21.
//
//

#include <vector>
#include <boost/algorithm/string.hpp>
#include "FileUtils.h"
#include "macros.h"

using namespace std;

const char* FileUtils::getFilePath(const char *filepath) {
#if IS_IOS
  vector<std::string> results;
  cout << filepath << endl;
  boost::split(results, filepath, boost::is_any_of("/"));
  return results.back().c_str();
#else
  return filepath;
#endif
}
