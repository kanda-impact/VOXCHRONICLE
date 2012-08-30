//
//  Track.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#ifndef __VOXCHRONICLE__Track__
#define __VOXCHRONICLE__Track__
#define IS_IOS (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define IS_WIN32 (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>

namespace VISS {
  class Track {
#if IS_IOS
    struct AudioTrack;
#endif
  private:
    std::string* _fileName;
#if IS_IOS
    // for iOS
    // OALAudioTrackをラップしたC++のオブジェクトを保持する
    boost::shared_ptr<AudioTrack> _track;
#elif IS_WIN32
    // for windows
#endif
  public:
    /**
     @brief トラックを生成します。引数にはファイル名を指定します
     @param const std::string fileName ファイル名
     */
    Track(const std::string* fileName);
    
    ~Track();
    
    /**
     @brief トラックを再生します。再生に成功した場合trueを返します
     @return bool 再生に成功したかどうか
     */
    bool play();
    
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
  };
}

#endif /* defined(__VOXCHRONICLE__Track__) */
