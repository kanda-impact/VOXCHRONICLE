#ifndef _VIMCI_PLAYER_WIN32_H_
#define _VIMCI_PLAYER_WIN32_H_

#include<windows.h>
#include <mmsystem.h>

namespace VISS {

class VIMciPlayer
{
public:
    VIMciPlayer();
    ~VIMciPlayer();

    void Close();

    void Open(const char* pFileName, UINT uId);

    void Play(UINT uTimes = 1);

    void Pause();

    void Resume();

    void Stop();

    void Rewind();

    bool IsPlaying();

    UINT GetSoundID();

    void SetNextPlayer(VIMciPlayer* next);

    float GetDuration();
    float GetPosition();
    void SetVolume(float volume);

private:
    friend LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    void _SendGenericCommand(int nCommand);
    
    HWND        m_hWnd;
    MCIDEVICEID m_hDev;
    UINT        m_nSoundID;
    UINT        m_uTimes;
    DWORD       m_CurrentPosition;
    DWORD       m_Duration;
    bool        m_bPlaying;

    VIMciPlayer* m_next_player;
};

} // end of namespace CocosDenshion

#endif
