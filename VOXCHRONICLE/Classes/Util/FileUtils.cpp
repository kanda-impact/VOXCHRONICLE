//
//  FileUtils.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/21.
//
//

#include "cocos2d.h"
#include <vector>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/tokenizer.hpp>
#include "FileUtils.h"
#include "macros.h"

using namespace std;
using namespace boost;

string FileUtils::getFilePath(const char *filepath) {
  std::string path(filepath);
#if IS_WIN32
  if (algorithm:iends_with(path, ".caf")) {
    boost::algorithm::replace_all(path, ".caf", ".ogg");
  }
  return path;
#elif IS_IOS
  typedef boost::char_separator<char> char_separator;
  typedef boost::tokenizer<char_separator> tokenizer;
  
  char_separator sep("/", "", boost::keep_empty_tokens);
  tokenizer tokens(path, sep);
  vector<string> results;
  tokenizer::iterator tok_iter;
  for (tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
    results.push_back(*tok_iter);
  }
  return results.back().c_str();
#endif
}

string FileUtils::getMusicExt() {
#if IS_WIN32
  return ".ogg";
#elif IS_IOS
  return ".caf";
#endif
}
