//
//  IRegister.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/3/19.
//
//

#ifndef __VOXCHRONICLE__IRegister__
#define __VOXCHRONICLE__IRegister__

#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class IRegister {
 protected:
  map<string, int>* _register;
  IRegister();
 public:
  virtual ~IRegister();
  /**
   レジスタの値を取り出します
   主にスクリプト側から数ターンに跨ぐ行動のステートを保存したりするのに使います
   未登録の値を取り出そうとした場合は、第二引数を強制的に返します
   @param const char* key 取り出す値のキー
   @param int defaultValue キーが未登録だったときに返却する値
   @return int 登録されている値
   */
  int getRegister(const char* key, int defaultValue);
  
  /**
   レジスタの値を登録します
   主にスクリプト側から利用します
   @param const char* key
   @param int value 登録する値
   */
  void setRegister(const char* key, int value);
  
  /**
   あるキーを与えたとき、そのレジスタに登録済みかどうかを返します
   @param const char* key キー
   @return bool 登録済みかどうか
   */
  bool hasRegister(const char* key);
};

#endif /* defined(__VOXCHRONICLE__IRegister__) */
