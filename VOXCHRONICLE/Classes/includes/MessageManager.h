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
#include "Map.h"
#include "CharacterManager.h"
#include "EnemyManager.h"

using namespace cocos2d;

/**
 メッセージウィンドウにメッセージを流し込むシングルトンな管理クラスです。
 主にLuaスクリプトから文章を流し込むのに使います。
 */

class MessageManager :public CCObject {
  MessageWindow* _defaultWindow;
  static MessageManager* _instance;
 public:
  static MessageManager* sharedManager();
  static void purgeMessageManager();
  MessageManager();
  ~MessageManager();
  void setDefaultMessageWindow(MessageWindow* window);
  
  /**
   渡した文字列をデフォルトMessageWindowに追加します
   @param const char* message 渡すメッセージ
   */
  void pushMessage(const char* message);
  
  /**
   渡した文字列のタグをdictの中身で差し替えてMessageWindowに追加します
   例えば#{word}みたいな文字列がmessageの中に含まれているとき
   dict["word"]をCCStringとして扱って、それに置換します。
   dictの中に含まれないときはそのまま表示します。
   これによって、メッセージにキャラ名やモンスター名を入れたり、わりと好き勝手できます
   @param const char* message 渡すメッセージ
   @param CCDictionary* dict CCStringが含まれる置換されるメッセージ
   */
  void pushMessage(const char* message, CCDictionary* dict);

  /**
   Luaファイル名を渡すと、そのスクリプトに定義されたテーブルの
   中からランダムに文字列を持ってきてMessageWindowに追加します
   @param const char* luaName 読み込むLuaスクリプト名
   */
  void pushRandomMessageFromLua(const char* luaName);
  
  /**
   上の3つのドキュメントを読んだあなたには使い方がわかるはずだ！
   @param const char* luaName 読み込むLuaスクリプト名
   @param CCDictionary* dict CCStringが含まれる置換されるメッセージ
   */
  void pushRandomMessageFromLua(const char* luaName, CCDictionary* dict);
  
  /**
   Luaの関数を実行してランダムメッセージを取り出します
   細かい条件を指定したいたわしさん向け
   指定するスクリプトファイルでは、characterManager, enemyManagerを
   引数に取り、tableを返却する関数をスタックの一番上に積んでください
   */
  void pushRandomMessageFromFunction(const char* scriptFile, Map* map, CharacterManager* manager, EnemyManager* enemyManager);
  
  void pushRandomMessageFromSkill(Skill* skill, CCArray* targets, Map* map, CharacterManager* manager, EnemyManager* enemyManager);

  void pushRandomMessageFromObject(LuaObject* lua, Map* map, CharacterManager* manager, EnemyManager* enemyManager);
};

#endif /* defined(__VOXCHRONICLE__MessageManager__) */
