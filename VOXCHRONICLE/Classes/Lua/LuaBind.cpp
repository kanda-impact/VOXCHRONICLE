/*
** Lua binding: VOXCHRONICLE
** Generated automatically by tolua++-1.0.92 on Wed Apr  3 19:36:01 2013.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_VOXCHRONICLE_open (lua_State* tolua_S);

#include "LuaCocos2d.h"
#include "Skill.h"
#include "Enemy.h"
#include "Character.h"
#include "CharacterManager.h"
#include "EnemyManager.h"
#include "EnemySkill.h"
#include "MessageManager.h"
#include "EffectLayer.h"
#include "PopupWindow.h"
#include "IRegister.h"
#include "Controller.h"
#include "StatusLayer.h"
#include "EnemySkill.h"
#include "AchievementManager.h"
#include "Map.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_DamageType (lua_State* tolua_S)
{
 DamageType* self = (DamageType*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"EnemySkill");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"IRegister");
 tolua_usertype(tolua_S,"Skill");
 tolua_usertype(tolua_S,"Enemy");
 tolua_usertype(tolua_S,"Character");
 tolua_usertype(tolua_S,"MessageManager");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"EffectLayer");
 tolua_usertype(tolua_S,"CCArray");
 tolua_usertype(tolua_S,"Map");
 tolua_usertype(tolua_S,"DamageType");
 tolua_usertype(tolua_S,"PopupWindow");
 tolua_usertype(tolua_S,"CharacterManager");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"AchievementManager");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"EnemyManager");
 tolua_usertype(tolua_S,"CCRect");
}

/* method: getPower of class  Skill */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Skill_getPower00
static int tolua_VOXCHRONICLE_Skill_getPower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Skill* self = (Skill*)  tolua_tousertype(tolua_S,1,0);
  CharacterManager* manager = ((CharacterManager*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPower'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPower(manager);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIdentifier of class  Skill */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Skill_getIdentifier00
static int tolua_VOXCHRONICLE_Skill_getIdentifier00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Skill* self = (Skill*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIdentifier'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getIdentifier();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIdentifier'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  Skill */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Skill_getName00
static int tolua_VOXCHRONICLE_Skill_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Skill* self = (Skill*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMP of class  Skill */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Skill_getMP00
static int tolua_VOXCHRONICLE_Skill_getMP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Skill* self = (Skill*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMP'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMP();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRow of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_getRow00
static int tolua_VOXCHRONICLE_Enemy_getRow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRow'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getRow();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttack of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_getAttack00
static int tolua_VOXCHRONICLE_Enemy_getAttack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttack'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAttack();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: moveRow of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_moveRow00
static int tolua_VOXCHRONICLE_Enemy_moveRow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
  float row = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'moveRow'", NULL);
#endif
  {
   self->moveRow(row);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'moveRow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRow of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_setRow00
static int tolua_VOXCHRONICLE_Enemy_setRow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
  float row = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRow'", NULL);
#endif
  {
   self->setRow(row);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCol of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_getCol00
static int tolua_VOXCHRONICLE_Enemy_getCol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCol'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getCol();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCol'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationClip of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_setAnimationClip00
static int tolua_VOXCHRONICLE_Enemy_setAnimationClip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
  const char* clipName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int frames = ((int)  tolua_tonumber(tolua_S,3,0));
  bool hasFrame = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationClip'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setAnimationClip(clipName,frames,hasFrame);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationClip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDefaultAnimationClip of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_setDefaultAnimationClip00
static int tolua_VOXCHRONICLE_Enemy_setDefaultAnimationClip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDefaultAnimationClip'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setDefaultAnimationClip();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDefaultAnimationClip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_getName00
static int tolua_VOXCHRONICLE_Enemy_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHP of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_getHP00
static int tolua_VOXCHRONICLE_Enemy_getHP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHP'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getHP();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCounter of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_setCounter00
static int tolua_VOXCHRONICLE_Enemy_setCounter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
  int counter = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCounter'", NULL);
#endif
  {
   self->setCounter(counter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCounter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRegister of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_getRegister00
static int tolua_VOXCHRONICLE_Enemy_getRegister00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  int defaultValue = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRegister'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getRegister(key,defaultValue);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRegister'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRegister of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_setRegister00
static int tolua_VOXCHRONICLE_Enemy_setRegister00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRegister'", NULL);
#endif
  {
   self->setRegister(key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRegister'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasRegister of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Enemy_hasRegister00
static int tolua_VOXCHRONICLE_Enemy_hasRegister00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Enemy",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasRegister'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasRegister(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasRegister'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __IRegister__ of class  Enemy */
#ifndef TOLUA_DISABLE_tolua_get_Enemy___IRegister__
static int tolua_get_Enemy___IRegister__(lua_State* tolua_S)
{
  Enemy* self = (Enemy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__IRegister__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<IRegister*>(self), "IRegister");
#else
   tolua_pushusertype(tolua_S,(void*)((IRegister*)self), "IRegister");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  Character */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Character_getName00
static int tolua_VOXCHRONICLE_Character_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Character",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Character* self = (Character*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShield of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_setShield00
static int tolua_VOXCHRONICLE_CharacterManager_setShield00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
  bool shield = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShield'", NULL);
#endif
  {
   self->setShield(shield);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShield'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeCharacter of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_changeCharacter00
static int tolua_VOXCHRONICLE_CharacterManager_changeCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeCharacter'", NULL);
#endif
  {
   self->changeCharacter();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTension of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_addTension00
static int tolua_VOXCHRONICLE_CharacterManager_addTension00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
  int tension = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTension'", NULL);
#endif
  {
   self->addTension(tension);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTension'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTension of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getTension00
static int tolua_VOXCHRONICLE_CharacterManager_getTension00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTension'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTension();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTension'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLevel of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getLevel00
static int tolua_VOXCHRONICLE_CharacterManager_getLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLevel'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLevel of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_setLevel00
static int tolua_VOXCHRONICLE_CharacterManager_setLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
  int lv = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLevel'", NULL);
#endif
  {
   self->setLevel(lv);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addHP of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_addHP00
static int tolua_VOXCHRONICLE_CharacterManager_addHP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
  int hp = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addHP'", NULL);
#endif
  {
   int tolua_ret = (int)  self->addHP(hp);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addHP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addMP of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_addMP00
static int tolua_VOXCHRONICLE_CharacterManager_addMP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
  int mp = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addMP'", NULL);
#endif
  {
   int tolua_ret = (int)  self->addMP(mp);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addMP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDrumLevel of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getDrumLevel00
static int tolua_VOXCHRONICLE_CharacterManager_getDrumLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDrumLevel'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getDrumLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDrumLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDrumLevel of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_setDrumLevel00
static int tolua_VOXCHRONICLE_CharacterManager_setDrumLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
  int lv = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDrumLevel'", NULL);
#endif
  {
   self->setDrumLevel(lv);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDrumLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: damage of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_damage00
static int tolua_VOXCHRONICLE_CharacterManager_damage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
  int d = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'damage'", NULL);
#endif
  {
   DamageType tolua_ret = (DamageType)  self->damage(d);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DamageType)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DamageType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DamageType));
     tolua_pushusertype(tolua_S,tolua_obj,"DamageType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'damage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHP of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getHP00
static int tolua_VOXCHRONICLE_CharacterManager_getHP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHP'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getHP();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMP of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getMP00
static int tolua_VOXCHRONICLE_CharacterManager_getMP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMP'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMP();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxHP of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getMaxHP00
static int tolua_VOXCHRONICLE_CharacterManager_getMaxHP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxHP'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxHP();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxHP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxMP of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getMaxMP00
static int tolua_VOXCHRONICLE_CharacterManager_getMaxMP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxMP'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxMP();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxMP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetTension of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_resetTension00
static int tolua_VOXCHRONICLE_CharacterManager_resetTension00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetTension'", NULL);
#endif
  {
   self->resetTension();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetTension'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrentCharacter of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getCurrentCharacter00
static int tolua_VOXCHRONICLE_CharacterManager_getCurrentCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentCharacter'", NULL);
#endif
  {
   Character* tolua_ret = (Character*)  self->getCurrentCharacter();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Character");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRepeatCount of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getRepeatCount00
static int tolua_VOXCHRONICLE_CharacterManager_getRepeatCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRepeatCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getRepeatCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRepeatCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRepeatCount of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_setRepeatCount00
static int tolua_VOXCHRONICLE_CharacterManager_setRepeatCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
  int repeat = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRepeatCount'", NULL);
#endif
  {
   self->setRepeatCount(repeat);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRepeatCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLastSkill of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getLastSkill00
static int tolua_VOXCHRONICLE_CharacterManager_getLastSkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLastSkill'", NULL);
#endif
  {
   Skill* tolua_ret = (Skill*)  self->getLastSkill();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Skill");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLastSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getExp of class  CharacterManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_CharacterManager_getExp00
static int tolua_VOXCHRONICLE_CharacterManager_getExp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CharacterManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CharacterManager* self = (CharacterManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getExp'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getExp();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getExp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: nextTurn of class  EnemyManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EnemyManager_nextTurn00
static int tolua_VOXCHRONICLE_EnemyManager_nextTurn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EnemyManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CharacterManager",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EnemyManager* self = (EnemyManager*)  tolua_tousertype(tolua_S,1,0);
  CharacterManager* manager = ((CharacterManager*)  tolua_tousertype(tolua_S,2,0));
  bool moveOnly = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'nextTurn'", NULL);
#endif
  {
   self->nextTurn(manager,moveOnly);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'nextTurn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: popEnemyAt of class  EnemyManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EnemyManager_popEnemyAt00
static int tolua_VOXCHRONICLE_EnemyManager_popEnemyAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EnemyManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EnemyManager* self = (EnemyManager*)  tolua_tousertype(tolua_S,1,0);
  const char* enemy = ((const char*)  tolua_tostring(tolua_S,2,0));
  float row = ((float)  tolua_tonumber(tolua_S,3,0));
  int col = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'popEnemyAt'", NULL);
#endif
  {
   Enemy* tolua_ret = (Enemy*)  self->popEnemyAt(enemy,row,col);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Enemy");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'popEnemyAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBoss of class  EnemyManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EnemyManager_getBoss00
static int tolua_VOXCHRONICLE_EnemyManager_getBoss00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EnemyManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EnemyManager* self = (EnemyManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBoss'", NULL);
#endif
  {
   Enemy* tolua_ret = (Enemy*)  self->getBoss();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Enemy");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBoss'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEnemies of class  EnemyManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EnemyManager_getEnemies00
static int tolua_VOXCHRONICLE_EnemyManager_getEnemies00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EnemyManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EnemyManager* self = (EnemyManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEnemies'", NULL);
#endif
  {
   CCArray* tolua_ret = (CCArray*)  self->getEnemies();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCArray");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEnemies'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBoss of class  EnemyManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EnemyManager_setBoss00
static int tolua_VOXCHRONICLE_EnemyManager_setBoss00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EnemyManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Enemy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EnemyManager* self = (EnemyManager*)  tolua_tousertype(tolua_S,1,0);
  Enemy* enemy = ((Enemy*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBoss'", NULL);
#endif
  {
   self->setBoss(enemy);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBoss'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadEnemyTextureAsync of class  EnemyManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EnemyManager_loadEnemyTextureAsync00
static int tolua_VOXCHRONICLE_EnemyManager_loadEnemyTextureAsync00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EnemyManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EnemyManager* self = (EnemyManager*)  tolua_tousertype(tolua_S,1,0);
  const char* enemyImageName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadEnemyTextureAsync'", NULL);
#endif
  {
   self->loadEnemyTextureAsync(enemyImageName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadEnemyTextureAsync'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllNormalEnemies of class  EnemyManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EnemyManager_removeAllNormalEnemies00
static int tolua_VOXCHRONICLE_EnemyManager_removeAllNormalEnemies00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EnemyManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EnemyManager* self = (EnemyManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllNormalEnemies'", NULL);
#endif
  {
   self->removeAllNormalEnemies();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllNormalEnemies'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllEnemies of class  EnemyManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EnemyManager_removeAllEnemies00
static int tolua_VOXCHRONICLE_EnemyManager_removeAllEnemies00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EnemyManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EnemyManager* self = (EnemyManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllEnemies'", NULL);
#endif
  {
   self->removeAllEnemies();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllEnemies'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedManager of class  MessageManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_MessageManager_sharedManager00
static int tolua_VOXCHRONICLE_MessageManager_sharedManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MessageManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MessageManager* tolua_ret = (MessageManager*)  MessageManager::sharedManager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MessageManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pushMessage of class  MessageManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_MessageManager_pushMessage00
static int tolua_VOXCHRONICLE_MessageManager_pushMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MessageManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MessageManager* self = (MessageManager*)  tolua_tousertype(tolua_S,1,0);
  const char* message = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pushMessage'", NULL);
#endif
  {
   self->pushMessage(message);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pushRandomMessageFromLua of class  MessageManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_MessageManager_pushRandomMessageFromLua00
static int tolua_VOXCHRONICLE_MessageManager_pushRandomMessageFromLua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MessageManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MessageManager* self = (MessageManager*)  tolua_tousertype(tolua_S,1,0);
  const char* luaFile = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pushRandomMessageFromLua'", NULL);
#endif
  {
   self->pushRandomMessageFromLua(luaFile);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushRandomMessageFromLua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedLayer of class  EffectLayer */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EffectLayer_sharedLayer00
static int tolua_VOXCHRONICLE_EffectLayer_sharedLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EffectLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   EffectLayer* tolua_ret = (EffectLayer*)  EffectLayer::sharedLayer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"EffectLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addPopupWindow of class  EffectLayer */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EffectLayer_addPopupWindow00
static int tolua_VOXCHRONICLE_EffectLayer_addPopupWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EffectLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EffectLayer* self = (EffectLayer*)  tolua_tousertype(tolua_S,1,0);
  int pages = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPopupWindow'", NULL);
#endif
  {
   PopupWindow* tolua_ret = (PopupWindow*)  self->addPopupWindow(pages);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PopupWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addPopupWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addEffectOnEnemy of class  EffectLayer */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EffectLayer_addEffectOnEnemy00
static int tolua_VOXCHRONICLE_EffectLayer_addEffectOnEnemy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EffectLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Enemy",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EffectLayer* self = (EffectLayer*)  tolua_tousertype(tolua_S,1,0);
  Enemy* enemy = ((Enemy*)  tolua_tousertype(tolua_S,2,0));
  const char* prefix = ((const char*)  tolua_tostring(tolua_S,3,0));
  int frameCount = ((int)  tolua_tonumber(tolua_S,4,0));
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEffectOnEnemy'", NULL);
#endif
  {
   self->addEffectOnEnemy(enemy,prefix,frameCount,rect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addEffectOnEnemy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPage of class  PopupWindow */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_PopupWindow_getPage00
static int tolua_VOXCHRONICLE_PopupWindow_getPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PopupWindow",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PopupWindow* self = (PopupWindow*)  tolua_tousertype(tolua_S,1,0);
  int page = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPage'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getPage(page);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setText of class  PopupWindow */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_PopupWindow_setText00
static int tolua_VOXCHRONICLE_PopupWindow_setText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PopupWindow",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PopupWindow* self = (PopupWindow*)  tolua_tousertype(tolua_S,1,0);
  int page = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* headerText = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setText'", NULL);
#endif
  {
   self->setText(page,headerText,message);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRegister of class  IRegister */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_IRegister_getRegister00
static int tolua_VOXCHRONICLE_IRegister_getRegister00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IRegister",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IRegister* self = (IRegister*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  int defaultValue = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRegister'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getRegister(key,defaultValue);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRegister'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRegister of class  IRegister */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_IRegister_setRegister00
static int tolua_VOXCHRONICLE_IRegister_setRegister00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IRegister",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IRegister* self = (IRegister*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRegister'", NULL);
#endif
  {
   self->setRegister(key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRegister'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasRegister of class  IRegister */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_IRegister_hasRegister00
static int tolua_VOXCHRONICLE_IRegister_hasRegister00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IRegister",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IRegister* self = (IRegister*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasRegister'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasRegister(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasRegister'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBool of class  IRegister */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_IRegister_getBool00
static int tolua_VOXCHRONICLE_IRegister_getBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IRegister",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IRegister* self = (IRegister*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBool'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getBool(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBool of class  IRegister */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_IRegister_setBool00
static int tolua_VOXCHRONICLE_IRegister_setBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IRegister",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IRegister* self = (IRegister*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBool'", NULL);
#endif
  {
   self->setBool(key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearRegister of class  IRegister */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_IRegister_clearRegister00
static int tolua_VOXCHRONICLE_IRegister_clearRegister00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IRegister",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IRegister* self = (IRegister*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearRegister'", NULL);
#endif
  {
   self->clearRegister();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearRegister'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  EnemySkill */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_EnemySkill_getName00
static int tolua_VOXCHRONICLE_EnemySkill_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EnemySkill",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EnemySkill* self = (EnemySkill*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxLevel of class  Map */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Map_getMaxLevel00
static int tolua_VOXCHRONICLE_Map_getMaxLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Map",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Map* self = (Map*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxLevel'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getMaxLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInitialLevel of class  Map */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Map_getInitialLevel00
static int tolua_VOXCHRONICLE_Map_getInitialLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Map",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Map* self = (Map*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInitialLevel'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getInitialLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInitialLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getName of class  Map */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Map_getName00
static int tolua_VOXCHRONICLE_Map_getName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Map",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Map* self = (Map*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getName'", NULL);
#endif
  {
   string tolua_ret = (string)  self->getName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBossStage of class  Map */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Map_isBossStage00
static int tolua_VOXCHRONICLE_Map_isBossStage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Map",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Map* self = (Map*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBossStage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBossStage();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBossStage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeBackgroundImage of class  Map */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_Map_changeBackgroundImage00
static int tolua_VOXCHRONICLE_Map_changeBackgroundImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Map",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Map* self = (Map*)  tolua_tousertype(tolua_S,1,0);
  const char* imageName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeBackgroundImage'", NULL);
#endif
  {
   self->changeBackgroundImage(imageName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeBackgroundImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __IRegister__ of class  Map */
#ifndef TOLUA_DISABLE_tolua_get_Map___IRegister__
static int tolua_get_Map___IRegister__(lua_State* tolua_S)
{
  Map* self = (Map*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__IRegister__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<IRegister*>(self), "IRegister");
#else
   tolua_pushusertype(tolua_S,(void*)((IRegister*)self), "IRegister");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: sharedManager of class  AchievementManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_AchievementManager_sharedManager00
static int tolua_VOXCHRONICLE_AchievementManager_sharedManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AchievementManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AchievementManager* tolua_ret = (AchievementManager*)  AchievementManager::sharedManager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AchievementManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sharedManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reportAchievement of class  AchievementManager */
#ifndef TOLUA_DISABLE_tolua_VOXCHRONICLE_AchievementManager_reportAchievement00
static int tolua_VOXCHRONICLE_AchievementManager_reportAchievement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AchievementManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AchievementManager* self = (AchievementManager*)  tolua_tousertype(tolua_S,1,0);
  const char* identifier = ((const char*)  tolua_tostring(tolua_S,2,0));
  float percent = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reportAchievement'", NULL);
#endif
  {
   self->reportAchievement(identifier,percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reportAchievement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_VOXCHRONICLE_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"MAX_ROW",MAX_ROW);
  tolua_constant(tolua_S,"SkillRangeSingle",SkillRangeSingle);
  tolua_constant(tolua_S,"SkillRangeAll",SkillRangeAll);
  tolua_constant(tolua_S,"SkillRangeHorizontal",SkillRangeHorizontal);
  tolua_constant(tolua_S,"SkillRangeVertical",SkillRangeVertical);
  tolua_constant(tolua_S,"SkillRangeBack",SkillRangeBack);
  tolua_constant(tolua_S,"SkillRangeSelf",SkillRangeSelf);
  tolua_constant(tolua_S,"SkillRangeFront",SkillRangeFront);
  tolua_constant(tolua_S,"SkillTypeNone",SkillTypeNone);
  tolua_constant(tolua_S,"SkillTypeNormal",SkillTypeNormal);
  tolua_constant(tolua_S,"SkillTypePhysical",SkillTypePhysical);
  tolua_constant(tolua_S,"SkillTypeMagical",SkillTypeMagical);
  tolua_constant(tolua_S,"CharacterTypeVox",CharacterTypeVox);
  tolua_constant(tolua_S,"CharacterTypeLaska",CharacterTypeLaska);
  tolua_constant(tolua_S,"EnemyItemNone",EnemyItemNone);
  tolua_constant(tolua_S,"EnemyItemShield",EnemyItemShield);
  tolua_constant(tolua_S,"EnemyItemBarrier",EnemyItemBarrier);
  tolua_constant(tolua_S,"MusicSetTypeWay",MusicSetTypeWay);
  tolua_constant(tolua_S,"MusicSetTypeBoss",MusicSetTypeBoss);
  tolua_constant(tolua_S,"MaxHPLabelTag",MaxHPLabelTag);
  tolua_constant(tolua_S,"CurrentHPLabelTag",CurrentHPLabelTag);
  tolua_constant(tolua_S,"LevelLabelTag",LevelLabelTag);
  tolua_constant(tolua_S,"LifeGaugeBackgroundTag",LifeGaugeBackgroundTag);
  tolua_constant(tolua_S,"LifeGaugeTag",LifeGaugeTag);
  tolua_constant(tolua_S,"MPMarkerTag",MPMarkerTag);
  tolua_constant(tolua_S,"ControllerFrameTypeNone",ControllerFrameTypeNone);
  tolua_constant(tolua_S,"ControllerFrameTypeCommon",ControllerFrameTypeCommon);
  tolua_constant(tolua_S,"ControllerFrameTypeFull",ControllerFrameTypeFull);
  tolua_constant(tolua_S,"EffectLayerCutinTypeNormal",EffectLayerCutinTypeNormal);
  tolua_constant(tolua_S,"EffectLayerCutinTypeFailure",EffectLayerCutinTypeFailure);
  tolua_constant(tolua_S,"EffectLayerCutinTypeHold",EffectLayerCutinTypeHold);
  tolua_constant(tolua_S,"EffectLayerCutinTypeCastOff",EffectLayerCutinTypeCastOff);
  tolua_constant(tolua_S,"DamageTypeNone",DamageTypeNone);
  tolua_constant(tolua_S,"DamageTypeHit",DamageTypeHit);
  tolua_constant(tolua_S,"DamageTypeNoDamage",DamageTypeNoDamage);
  tolua_constant(tolua_S,"DamageTypeDisable",DamageTypeDisable);
  tolua_constant(tolua_S,"DamageTypeShield",DamageTypeShield);
  tolua_constant(tolua_S,"DamageTypeInvincible",DamageTypeInvincible);
  tolua_constant(tolua_S,"DamageTypeWeak",DamageTypeWeak);
  tolua_constant(tolua_S,"DamageTypePhysicalResist",DamageTypePhysicalResist);
  tolua_constant(tolua_S,"DamageTypeMagicalResist",DamageTypeMagicalResist);
  tolua_constant(tolua_S,"DamageTypePhysicalInvalid",DamageTypePhysicalInvalid);
  tolua_constant(tolua_S,"DamageTypeMagicalInvalid",DamageTypeMagicalInvalid);
  tolua_constant(tolua_S,"DamageTypeShieldBreak",DamageTypeShieldBreak);
  tolua_constant(tolua_S,"DamageTypeBarrierBreak",DamageTypeBarrierBreak);
  tolua_constant(tolua_S,"DamageTypeDeath",DamageTypeDeath);
  tolua_constant(tolua_S,"DamageTypeAbsorption",DamageTypeAbsorption);
  tolua_cclass(tolua_S,"Skill","Skill","CCObject",NULL);
  tolua_beginmodule(tolua_S,"Skill");
   tolua_function(tolua_S,"getPower",tolua_VOXCHRONICLE_Skill_getPower00);
   tolua_function(tolua_S,"getIdentifier",tolua_VOXCHRONICLE_Skill_getIdentifier00);
   tolua_function(tolua_S,"getName",tolua_VOXCHRONICLE_Skill_getName00);
   tolua_function(tolua_S,"getMP",tolua_VOXCHRONICLE_Skill_getMP00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Enemy","Enemy","CCSprite",NULL);
  tolua_beginmodule(tolua_S,"Enemy");
   tolua_function(tolua_S,"getRow",tolua_VOXCHRONICLE_Enemy_getRow00);
   tolua_function(tolua_S,"getAttack",tolua_VOXCHRONICLE_Enemy_getAttack00);
   tolua_function(tolua_S,"moveRow",tolua_VOXCHRONICLE_Enemy_moveRow00);
   tolua_function(tolua_S,"setRow",tolua_VOXCHRONICLE_Enemy_setRow00);
   tolua_function(tolua_S,"getCol",tolua_VOXCHRONICLE_Enemy_getCol00);
   tolua_function(tolua_S,"setAnimationClip",tolua_VOXCHRONICLE_Enemy_setAnimationClip00);
   tolua_function(tolua_S,"setDefaultAnimationClip",tolua_VOXCHRONICLE_Enemy_setDefaultAnimationClip00);
   tolua_function(tolua_S,"getName",tolua_VOXCHRONICLE_Enemy_getName00);
   tolua_function(tolua_S,"getHP",tolua_VOXCHRONICLE_Enemy_getHP00);
   tolua_function(tolua_S,"setCounter",tolua_VOXCHRONICLE_Enemy_setCounter00);
   tolua_function(tolua_S,"getRegister",tolua_VOXCHRONICLE_Enemy_getRegister00);
   tolua_function(tolua_S,"setRegister",tolua_VOXCHRONICLE_Enemy_setRegister00);
   tolua_function(tolua_S,"hasRegister",tolua_VOXCHRONICLE_Enemy_hasRegister00);
   tolua_variable(tolua_S,"__IRegister__",tolua_get_Enemy___IRegister__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Character","Character","CCObject",NULL);
  tolua_beginmodule(tolua_S,"Character");
   tolua_function(tolua_S,"getName",tolua_VOXCHRONICLE_Character_getName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CharacterManager","CharacterManager","CCObject",NULL);
  tolua_beginmodule(tolua_S,"CharacterManager");
   tolua_function(tolua_S,"setShield",tolua_VOXCHRONICLE_CharacterManager_setShield00);
   tolua_function(tolua_S,"changeCharacter",tolua_VOXCHRONICLE_CharacterManager_changeCharacter00);
   tolua_function(tolua_S,"addTension",tolua_VOXCHRONICLE_CharacterManager_addTension00);
   tolua_function(tolua_S,"getTension",tolua_VOXCHRONICLE_CharacterManager_getTension00);
   tolua_function(tolua_S,"getLevel",tolua_VOXCHRONICLE_CharacterManager_getLevel00);
   tolua_function(tolua_S,"setLevel",tolua_VOXCHRONICLE_CharacterManager_setLevel00);
   tolua_function(tolua_S,"addHP",tolua_VOXCHRONICLE_CharacterManager_addHP00);
   tolua_function(tolua_S,"addMP",tolua_VOXCHRONICLE_CharacterManager_addMP00);
   tolua_function(tolua_S,"getDrumLevel",tolua_VOXCHRONICLE_CharacterManager_getDrumLevel00);
   tolua_function(tolua_S,"setDrumLevel",tolua_VOXCHRONICLE_CharacterManager_setDrumLevel00);
   tolua_function(tolua_S,"damage",tolua_VOXCHRONICLE_CharacterManager_damage00);
   tolua_function(tolua_S,"getHP",tolua_VOXCHRONICLE_CharacterManager_getHP00);
   tolua_function(tolua_S,"getMP",tolua_VOXCHRONICLE_CharacterManager_getMP00);
   tolua_function(tolua_S,"getMaxHP",tolua_VOXCHRONICLE_CharacterManager_getMaxHP00);
   tolua_function(tolua_S,"getMaxMP",tolua_VOXCHRONICLE_CharacterManager_getMaxMP00);
   tolua_function(tolua_S,"resetTension",tolua_VOXCHRONICLE_CharacterManager_resetTension00);
   tolua_function(tolua_S,"getCurrentCharacter",tolua_VOXCHRONICLE_CharacterManager_getCurrentCharacter00);
   tolua_function(tolua_S,"getRepeatCount",tolua_VOXCHRONICLE_CharacterManager_getRepeatCount00);
   tolua_function(tolua_S,"setRepeatCount",tolua_VOXCHRONICLE_CharacterManager_setRepeatCount00);
   tolua_function(tolua_S,"getLastSkill",tolua_VOXCHRONICLE_CharacterManager_getLastSkill00);
   tolua_function(tolua_S,"getExp",tolua_VOXCHRONICLE_CharacterManager_getExp00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"EnemyManager","EnemyManager","CCLayer",NULL);
  tolua_beginmodule(tolua_S,"EnemyManager");
   tolua_function(tolua_S,"nextTurn",tolua_VOXCHRONICLE_EnemyManager_nextTurn00);
   tolua_function(tolua_S,"popEnemyAt",tolua_VOXCHRONICLE_EnemyManager_popEnemyAt00);
   tolua_function(tolua_S,"getBoss",tolua_VOXCHRONICLE_EnemyManager_getBoss00);
   tolua_function(tolua_S,"getEnemies",tolua_VOXCHRONICLE_EnemyManager_getEnemies00);
   tolua_function(tolua_S,"setBoss",tolua_VOXCHRONICLE_EnemyManager_setBoss00);
   tolua_function(tolua_S,"loadEnemyTextureAsync",tolua_VOXCHRONICLE_EnemyManager_loadEnemyTextureAsync00);
   tolua_function(tolua_S,"removeAllNormalEnemies",tolua_VOXCHRONICLE_EnemyManager_removeAllNormalEnemies00);
   tolua_function(tolua_S,"removeAllEnemies",tolua_VOXCHRONICLE_EnemyManager_removeAllEnemies00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"MessageManager","MessageManager","CCObject",NULL);
  tolua_beginmodule(tolua_S,"MessageManager");
   tolua_function(tolua_S,"sharedManager",tolua_VOXCHRONICLE_MessageManager_sharedManager00);
   tolua_function(tolua_S,"pushMessage",tolua_VOXCHRONICLE_MessageManager_pushMessage00);
   tolua_function(tolua_S,"pushRandomMessageFromLua",tolua_VOXCHRONICLE_MessageManager_pushRandomMessageFromLua00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"EffectLayer","EffectLayer","CCLayer",NULL);
  tolua_beginmodule(tolua_S,"EffectLayer");
   tolua_function(tolua_S,"sharedLayer",tolua_VOXCHRONICLE_EffectLayer_sharedLayer00);
   tolua_function(tolua_S,"addPopupWindow",tolua_VOXCHRONICLE_EffectLayer_addPopupWindow00);
   tolua_function(tolua_S,"addEffectOnEnemy",tolua_VOXCHRONICLE_EffectLayer_addEffectOnEnemy00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PopupWindow","PopupWindow","CCSprite",NULL);
  tolua_beginmodule(tolua_S,"PopupWindow");
   tolua_function(tolua_S,"getPage",tolua_VOXCHRONICLE_PopupWindow_getPage00);
   tolua_function(tolua_S,"setText",tolua_VOXCHRONICLE_PopupWindow_setText00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"IRegister","IRegister","",NULL);
  tolua_beginmodule(tolua_S,"IRegister");
   tolua_function(tolua_S,"getRegister",tolua_VOXCHRONICLE_IRegister_getRegister00);
   tolua_function(tolua_S,"setRegister",tolua_VOXCHRONICLE_IRegister_setRegister00);
   tolua_function(tolua_S,"hasRegister",tolua_VOXCHRONICLE_IRegister_hasRegister00);
   tolua_function(tolua_S,"getBool",tolua_VOXCHRONICLE_IRegister_getBool00);
   tolua_function(tolua_S,"setBool",tolua_VOXCHRONICLE_IRegister_setBool00);
   tolua_function(tolua_S,"clearRegister",tolua_VOXCHRONICLE_IRegister_clearRegister00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"EnemySkill","EnemySkill","CCObject",NULL);
  tolua_beginmodule(tolua_S,"EnemySkill");
   tolua_function(tolua_S,"getName",tolua_VOXCHRONICLE_EnemySkill_getName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Map","Map","CCObject",NULL);
  tolua_beginmodule(tolua_S,"Map");
   tolua_function(tolua_S,"getMaxLevel",tolua_VOXCHRONICLE_Map_getMaxLevel00);
   tolua_function(tolua_S,"getInitialLevel",tolua_VOXCHRONICLE_Map_getInitialLevel00);
   tolua_function(tolua_S,"getName",tolua_VOXCHRONICLE_Map_getName00);
   tolua_function(tolua_S,"isBossStage",tolua_VOXCHRONICLE_Map_isBossStage00);
   tolua_function(tolua_S,"changeBackgroundImage",tolua_VOXCHRONICLE_Map_changeBackgroundImage00);
   tolua_variable(tolua_S,"__IRegister__",tolua_get_Map___IRegister__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"AchievementManager","AchievementManager","CCObject",NULL);
  tolua_beginmodule(tolua_S,"AchievementManager");
   tolua_function(tolua_S,"sharedManager",tolua_VOXCHRONICLE_AchievementManager_sharedManager00);
   tolua_function(tolua_S,"reportAchievement",tolua_VOXCHRONICLE_AchievementManager_reportAchievement00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_VOXCHRONICLE (lua_State* tolua_S) {
 return tolua_VOXCHRONICLE_open(tolua_S);
};
#endif

