#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "CCScriptSupport.h"
#include "CCLuaEngine.h"
#include "TitleScene.h"
#include "InitialScene.h"
#include "macros.h"
#include "SaveData.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
  // fixed me
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
  // end simple audio engine here, or it may crashed on win32
  SimpleAudioEngine::sharedEngine()->end();
  CCScriptEngineManager::purgeSharedManager();
}

bool AppDelegate::applicationDidFinishLaunching()
{
  // initialize director
  CCDirector *pDirector = CCDirector::sharedDirector();
  pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
  
#if IS_IOS
  if (pDirector->enableRetinaDisplay(true)) {
    // iphone hd
    CCFileUtils::sharedFileUtils()->setResourceDirectory("Retina");
  } else {
    CCFileUtils::sharedFileUtils()->setResourceDirectory("Image");
  }
#elif IS_WIN32
  //pDirector->enableRetinaDisplay(true);
  CCFileUtils::sharedFileUtils()->setResourceDirectory("Resources");
#endif
  // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
  
  srand((unsigned int)time(NULL));
  
  // turn on display FPS
  pDirector->setDisplayStats(false);
  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);
  
  CCScriptEngineManager::sharedManager()->setScriptEngine(CCLuaEngine::defaultEngine());
  
  if (SaveData::sharedData()->getCountFor(SaveDataCountKeyBoot) == 1 || true) { // 初回起動時
    CCScene *pScene = CCScene::create();
    InitialScene* initial = InitialScene::create();
    
    pScene->addChild(initial);
    
    // run
    pDirector->runWithScene(pScene);
  } else {
    // create a scene. it's an autorelease object
    CCScene *pScene = TitleScene::scene();
  
    CCTransitionFade* transition = CCTransitionFade::create(1.0f, pScene);
  
    // run
    pDirector->runWithScene(transition);
  }
  
  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
  CCDirector::sharedDirector()->stopAnimation();
  
  // if you use SimpleAudioEngine, it must be pause
  // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
  CCDirector::sharedDirector()->startAnimation();
  
  // if you use SimpleAudioEngine, it must resume here
  // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
