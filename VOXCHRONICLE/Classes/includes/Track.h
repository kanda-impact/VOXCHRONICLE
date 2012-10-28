//
//  Track.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#ifndef __VOXCHRONICLE__Track__
#define __VOXCHRONICLE__Track__

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include "cocos2d.h"
#include "macros.h"

#if IS_WIN32
#include<windows.h>
#include <mmsystem.h>
#include "VIMciPlayer.h"
#endif

using namespace cocos2d;

namespace VISS {
  class Track :public CCObject {
#if IS_IOS
    struct AudioTrack;
#endif
  private:
    char* _fileName;
#if IS_IOS
    // for iOS
    // OALAudioTrackをラップしたC++のオブジェクトを保持する
    boost::shared_ptr<AudioTrack> _track;
#elif IS_WIN32
    // for windows
    VIMciPlayer* _player;
    void setNextTrack(Track* next);
#endif
  public:
    /**
    @brief トラックを生成します。引数にはファイル名を指定します
    @param const char fileName ファイル名
    */
    Track(const char* fileName);

    ~Track();

    /**
    @brief トラックを再生します。再生に成功した場合trueを返します
    @return bool 再生に成功したかどうか
    */
    bool play();

    void playAfterTime(float time);
    void playAfterTrack(Track* track);

    /**
    @brief トラックを停止します。再生位置は最初に戻ります
    */
    void stop();

    /**
    @brief トラックを一時停止します。再生位置は保持されます
    */
    void pause();

    /**
    @brief 再生中かどうかを返します
    @return bool 再生中かどうか
    */
    bool isPlaying();

    /**
    @brief トラックの総再生時間を秒数で返します
    @return float トラックの総再生時間
    */
    float getDuration();

    /**
    @brief トラックの現在の再生位置を秒数で返します
    @return float トラックの現在の再生位置
    */
    float getPosition();

    void setVolume(float v);

    float getDeviceCurrentTime();
  };
}

#endif /* defined(__VOXCHRONICLE__Track__) */
