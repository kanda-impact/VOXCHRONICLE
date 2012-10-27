//
//  FileUtils.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/10/21.
//
//

#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include "FileUtils.h"
#include "macros.h"

using namespace std;
using namespace boost;

string FileUtils::getFilePath(const char *filepath) {
#if IS_IOS
  std::string path(filepath);
  
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
#else
  return filepath;
#endif
}
