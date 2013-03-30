//
//  EnemyManager.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/28.
//
//

#ifndef __VOXCHRONICLE__EnemyManager__
#define __VOXCHRONICLE__EnemyManager__

#include <iostream>
#include <boost/function.hpp>

#include "cocos2d.h"

#include "Enemy.h"
#include "Skill.h"
#include "Level.h"
#include "CharacterManager.h"

using namespace cocos2d;

class EnemyManager :public CCLayer {
 private:
  deque<bool>* _enemyPopLots;
  Level* _level;
  CCArray* _enemyNamesQueue;
  CCArray* createEnemyQueue();
  
  /**
   Enemyをすぐにreleaseして殺そうとすると、
   Luaの実行ステートがEnemyを参照し続けていて、死ぬことがあるので、
   遅延させて解放するためにTrashに一時的にEnemyを溜めておく的なdirtyなことをしている。
   ターン中に殺されたモンスターは全てTrashに一時的に格納され、
   Luaの実行ステートが終了した毎ターン終了時辺りにTrashが空にされる
   */
  CCArray* _trash;
  Enemy* _boss;
  void onTextureLoaded(CCTexture2D* texture);
  bool performLuaFunction(Skill* skill, Enemy* target, CharacterManager* characterManager);
 public:
  virtual bool init();
  EnemyManager();
  ~EnemyManager();
  
  /**
   次のモンスターを取り出して、nodeに追加し、表示します。
   _enemyQueueに中身があるときは、一番最初のモンスターをPopします
   _enemyQueueが空の時は、Levelの持つモンスターテーブルを元に生成し、一番上をPopします
   @return Enemy* 次に出現するモンスター
   */
  Enemy* popEnemy();
  
  /**
   popEnemyを行うか、Levelの持つpopEnemyRateを元に抽選します。
   抽選に当たってモンスターが出現するときは、popEnemyが呼ばれ、モンスターが返ってきます。
   抽選に外れたときは、何もモンスターが出現しないのでNULLが返ります。
   @return Enemy* 次に出現するモンスター、もしくはNULL
   */
  Enemy* lotPopEnemy();
  
  /**
   与えられた行、列の位置にモンスターがいるかどうかを返します
   @param int col 行
   @param int row 列
   @return bool モンスターがいるかどうか
   */
  bool isExistEnemy(int col, int row);
  
  /**
   現在、フィールドに存在するモンスターの一覧を返します
   順番はおそらく出現順になってる気がしています
   @return CCArray* Enemy*を含むCCArray
   */
  CCArray* getEnemies();
  
  /**
   現在のレベルオブジェクトを返します
   @return Level*
   */
  Level* getLevel();
  void setLevel(Level* lv);
  
  /**
   指定した位置にいるモンスターを返します。存在しない場合はNULLを返します
   @param int col 行
   @param int row 列
   @return Enemy* モンスター、もしくはNULL
   */
  Enemy* enemyAt(int col, int row);
  
  /**
   渡したEnemy*を現在のフィールドから消し去ります
   死亡時の処理は走りません
   @param Enemy* enemy 殺すモンスター
   @return bool 殺せたかどうか
   */
  bool removeEnemy(Enemy* enemy);
  
  /**
   プレイヤーから最も近いモンスターを取り出します。
   最も近いモンスターは、列が最も小さい、列が同じ場合行が小さい、行と列共に等しい場合、生成順が早いモンスターが返ります
   @return Enemy* 一番近いモンスター
   */
  Enemy* getNearestEnemy();
  
  /**
   bool値を返す条件式をわたし、その条件を満たすモンスターを全て返します。
   いない場合は空のArrayが返ってきます
   引数のfunctionには第1引数にモンスターの行、第2引数にモンスターの列が渡されます
   @param boost::function<bool (int, float)> filter 条件式を定義する関数（第1引数は行、第2引数は列）
   @return CCArray* 条件を満たすモンスターの配列 Enemy*
   */
  CCArray* getFilteredEnemies(boost::function<bool (float, int)>filter);
  
  /**
   Trashを空にします
   */
  void purgeAllTrash();
  
  /**
   モンスターに実際にスキルを使用し、情報を返します
   @param Skill* skill 使用するスキル
   @param CCArray* Skillを適用するターゲット
   @param CharacterManager* characterManager 現在のCharacterManager
   @return CCDictionary 以下のキーと値を持つ辞書が返ります
       damages : CCArray 与えたダメージのリスト
       damageTypes : CCArray DamageType型のenumをラップしたCCIntegerのリスト。damagesと対応しています
       enemies : CCArray 攻撃を当てた敵のリスト。damagesと対応しています
       exp : 得られた総経験値
   */
  CCDictionary* performSkill(Skill* skill, CCArray* targets, CharacterManager* characterManager);
  
  /**
   スキルを渡したとき、その対象モンスターを含むCCArrayを返します
   @param Skill* skill 使用するスキル
   @return CCArray* ターゲットの一覧
   */
  CCArray* getTargets(Skill* skill);
  
  void draw();
  
  /**
   EnemyQueueの末尾にモンスターを追加します。
   要は次の出現モンスターを割り込ませます。
   @param CCArray* 割り込ませるEnemy*を含んだCCArray
   */
  void pushEnemiesQueue(CCArray* enemies);
  
  void removeAllEnemiesQueue();
  
  void nextTurn(CharacterManager* characterManager);
  
  Enemy* popEnemyAt(string enemyName, int row, int col);
  
  Enemy* getBoss();
  void setBoss(Enemy* boss);
  
  static float calcScale(float row);
  static CCPoint& calcLinePosition(int row, int col);
  
  /**
   ボス含めて全滅させます
   */
  void removeAllEnemies();
  
  /**
   ボス以外の敵を消します
   */
  void removeAllNormalEnemies();
  
  void loadEnemyTextureAsync(const char* enemyImageName);

  CREATE_FUNC(EnemyManager)
};

#endif /* defined(__VOXCHRONICLE__EnemyManager__) */
