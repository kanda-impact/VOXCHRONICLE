//
//  Track.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#include "Track.h"

// It is wrapper class for ObjectAL::OALAudioTrack.

using namespace std;
using namespace VISS;

static char     s_szRootPath[MAX_PATH];
static DWORD    s_dwRootLen;
static char     s_szFullPath[MAX_PATH];

unsigned int _Hash(const char *key) {
    unsigned int len = strlen(key);
    const char *end=key+len;
    unsigned int hash;

    for (hash = 0; key < end; key++)
    {
        hash *= 16777619;
        hash ^= (unsigned int) (unsigned char) toupper(*key);
    }
    return (hash);
}

const char * _FullPath(const char * szPath)
{
    if (! s_szRootPath[0])
    {
        WCHAR  wszPath[MAX_PATH];
        s_dwRootLen = WideCharToMultiByte(CP_ACP, 0, wszPath, 
            GetCurrentDirectoryW(sizeof(wszPath), wszPath), 
            s_szRootPath, MAX_PATH, NULL, NULL);
        s_szRootPath[s_dwRootLen] = '\\';
        s_szRootPath[s_dwRootLen + 1] = 0;
        strcpy_s(s_szFullPath, sizeof(s_szFullPath), s_szRootPath);
        ++s_dwRootLen;
    }

    if (0 != szPath[0] && ':' != szPath[1])
    {
        strcpy_s(s_szFullPath + s_dwRootLen, sizeof(s_szFullPath) - s_dwRootLen, szPath);
        return s_szFullPath;
    }
    else
    {
        return szPath;
 
    }
}

Track::Track(const char* fileName) {
  _player = new VIMciPlayer();
  _fileName = string(fileName);
  _player->Open(_FullPath(fileName), _Hash(fileName));
}

Track::~Track() {
  delete _player;
}

bool Track::play() {
  _player->Play(1);
  return true;
}

void Track::resume() {
  _player->Play(1);
}

void Track::playAfterTime(float time) {
  play();
}
  
void Track::stop() {
  _player->Stop();
}
  
void Track::pause() {
  _player->Pause();
}

bool Track::isPlaying() {
  return _player->IsPlaying();
}

float Track::getDuration() {
  return _player->GetDuration() / 1000.0;
}

float Track::getPosition() {
  return _player->GetPosition() / 1000.0;
}

float Track::getDeviceCurrentTime() {
  return 0.0f;
}

void Track::setVolume(float v) {
  _player->SetVolume(v * 1000);
}

void Track::playAfterTrack(VISS::Track *track) {
  track->setNextTrack(this);
}

void Track::setNextTrack(Track* nextTrack) {
  _player->SetNextPlayer(nextTrack->_player);
}

string Track::getTrackName() {
  return _fileName;
}