//
//  MessageManager.h
//  VOXCHRONICLE
//
//  Created by giginet on 2013/2/6.
//
//

#ifndef __VOXCHRONICLE__MessageManager__
#define __VOXCHRONICLE__MessageManager__

#include <iostream>
#include "cocos2d.h"
#include "MessageWindow.h"

using namespace cocos2d;

/**
 メッセージウィンドウにメッセージを流し込むシングルトンな管理クラスです。
 主にLuaスクリプトから文章を流し込むのに使います。
 */

class MessageManager :public CCObject {
  static MessageManager* sharedManager();
  MessageWindow* _defaultWindow;
  static MessageManager* _instance;
 public:
  MessageManager();
  ~MessageManager();
  void setDefaultMessageWindow(MessageWindow* window);
  
  /**
   渡した文字列をデフォルトMessageWindowに追加します
   @param const char* message 渡すメッセージ
   */
  void pushMessage(const char* message);

  /**
   Luaファイル名を渡すと、そのスクリプトに定義されたテーブルの
   中からランダムに文字列を持ってきてMessageWindowに追加します
   @param const char* luaName 読み込むLuaスクリプト名
   */
  void pushRandomMessageFromLua(const char* luaName);
};

#endif /* defined(__VOXCHRONICLE__MessageManager__) */
