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

    /**
    @brief ²¥·ÅÉùÒôÎÄ¼ş
    @param pFileName ²¥·ÅµÄÉùÒôÎÄ¼şÃû³Æ£¬ĞèÒª°E¬ÎÄ¼şµÄÂ·¾¶
    @param nTimes    ²¥·ÅÉùÒôÎÄ¼şµÄÑ­»·´ÎÊı£¬Ä¬ÈÏÖµÎª 1£¬¼´²¥·ÅÒ»´Î
    */
    void Open(const char* pFileName, UINT uId);

    void Play(UINT uTimes = 1);

    /**
    @brief ÔİÍ£²¥·ÅÉùÒE
    */
    void Pause();

    /**
    @brief ¼ÌĞø²¥·ÅÉùÒE
    */
    void Resume();

    /**
    @brief Í£Ö¹²¥·ÅÉùÒE
    */
    void Stop();

    /**
    @brief ÖØĞÂ²¥·Å
    */
    void Rewind();

    /**
    @brief »ñÈ¡²¥·ÅÆ÷µ±Ç°ÊÇ·ñÕıÔÚ²¥·ÅÖĞ
    */
    bool IsPlaying();

    /**
    @brief »ñÈ¡µ±Ç°²¥·ÅµÄÒôĞ§ ID
    @return µ±Ç°²¥·ÅµÄÒôĞ§ID
    */
    UINT GetSoundID();

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
    bool        m_bPlaying;
};

} // end of namespace CocosDenshion

#endif
