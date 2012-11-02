#include "VIMciPlayer.h"
#include <fstream>

#include <iostream>

#define WIN_CLASS_NAME        "VISSCallbackWnd"
#define BREAK_IF(cond)      if (cond) break;

namespace VISS {

  static HINSTANCE s_hInstance;
  static MCIERROR  s_mciError;

  static LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

  VIMciPlayer::VIMciPlayer()
    : m_hWnd(NULL)
    , m_hDev(NULL)
    , m_nSoundID(0)
    , m_uTimes(0)
    , m_bPlaying(false)
    , m_next_player(NULL)
  {
    if (! s_hInstance)
    {
      s_hInstance = GetModuleHandle( NULL );            // Grab An Instance For Our Window

      WNDCLASS  wc;        // Windows Class Structure

      // Redraw On Size, And Own DC For Window.
      wc.style          = 0;  
      wc.lpfnWndProc    = _SoundPlayProc;                    // WndProc Handles Messages
      wc.cbClsExtra     = 0;                              // No Extra Window Data
      wc.cbWndExtra     = 0;                                // No Extra Window Data
      wc.hInstance      = s_hInstance;                    // Set The Instance
      wc.hIcon          = 0;                                // Load The Default Icon
      wc.hCursor        = LoadCursor( NULL, IDC_ARROW );    // Load The Arrow Pointer
      wc.hbrBackground  = NULL;                           // No Background Required For GL
      wc.lpszMenuName   = NULL;                           // We Don't Want A Menu
      wc.lpszClassName  = (LPTSTR)WIN_CLASS_NAME;                 // Set The Class Name

      if (! RegisterClass(&wc)
        && 1410 != GetLastError())
      {
        return;
      }
    }

    m_hWnd = CreateWindowEx(
      WS_EX_APPWINDOW,                                    // Extended Style For The Window
      (LPTSTR)WIN_CLASS_NAME,                                        // Class Name
      NULL,                                        // Window Title
      WS_POPUPWINDOW,/*WS_OVERLAPPEDWINDOW*/               // Defined Window Style
      0, 0,                                                // Window Position
      0,                                                    // Window Width
      0,                                                    // Window Height
      NULL,                                                // No Parent Window
      NULL,                                                // No Menu
      s_hInstance,                                        // Instance
      NULL );
    if (m_hWnd)
    {
      SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
      m_CurrentPosition = 0;
    }
  }

  VIMciPlayer::~VIMciPlayer()
  {
    Close();
    DestroyWindow(m_hWnd);
  }

  void VIMciPlayer::Open(const char* pFileName, UINT uId)
  {
    //     WCHAR * pBuf = NULL;
    do {
      BREAK_IF(! pFileName || ! m_hWnd);
      int nLen = (int)strlen(pFileName);
      BREAK_IF(! nLen);
      //         pBuf = new WCHAR[nLen + 1];
      //         BREAK_IF(! pBuf);
      //         MultiByteToWideChar(CP_ACP, 0, pFileName, nLen + 1, pBuf, nLen + 1);

      Close();

      MCI_OPEN_PARMS mciOpen = {0};
      MCIERROR mciError;
      mciOpen.lpstrDeviceType = (LPCTSTR)MCI_ALL_DEVICE_ID;
      mciOpen.lpstrElementName = (LPCTSTR)(pFileName);

      mciError = mciSendCommand(0,MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
      BREAK_IF(mciError);

      m_hDev = mciOpen.wDeviceID;
      m_nSoundID = uId;
      m_bPlaying = false;

        MCI_SET_PARMS set;
        MCI_STATUS_PARMS status;

        set.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
        mciSendCommand(this->m_hDev, MCI_SET, MCI_SET_TIME_FORMAT, (DWORD)(LPVOID)&set);

        status.dwItem = MCI_STATUS_LENGTH;
        mciSendCommand(this->m_hDev, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&status);

        m_Duration = status.dwReturn;

        SetTimer(m_hWnd, uId, 1000.0 / 60.0, NULL);
    } while (0);
  }

  void VIMciPlayer::Play(UINT uTimes /* = 1 */)
  {
    if (! m_hDev)
    {
      return;
    }
    MCI_PLAY_PARMS mciPlay = {0};
    mciPlay.dwCallback = (DWORD_PTR)m_hWnd;
    s_mciError = mciSendCommand(m_hDev,MCI_PLAY, MCI_FROM|MCI_NOTIFY,(DWORD)&mciPlay);
    if (! s_mciError)
    {
      m_bPlaying = true;
      m_uTimes = uTimes;
    }
  }

  void VIMciPlayer::Close()
  {
    if (m_bPlaying)
    {
      Stop();
    }
    if (m_hDev)
    {
      _SendGenericCommand(MCI_CLOSE);
    }
    KillTimer(this->m_hWnd, this->GetSoundID());
    m_hDev = 0;
    m_bPlaying = false;
  }

  void VIMciPlayer::Pause()
  {
    _SendGenericCommand(MCI_PAUSE);
  }

  void VIMciPlayer::Resume()
  {
    _SendGenericCommand(MCI_RESUME);
  }

  void VIMciPlayer::Stop()
  {
    _SendGenericCommand(MCI_STOP);
    m_bPlaying = false;
  }

  void VIMciPlayer::Rewind()
  {
    if (! m_hDev)
    {
        return;
    }
    mciSendCommand(m_hDev, MCI_SEEK, MCI_SEEK_TO_START, 0);

    MCI_PLAY_PARMS mciPlay = {0};
    mciPlay.dwCallback = (DWORD)m_hWnd;
    m_bPlaying = mciSendCommand(m_hDev, MCI_PLAY, MCI_NOTIFY,(DWORD)&mciPlay) ? false : true;
  }

  bool VIMciPlayer::IsPlaying()
  {
    return m_bPlaying;
  }

  UINT VIMciPlayer::GetSoundID()
  {
    return m_nSoundID;
  }

  float VIMciPlayer::GetDuration() {
    return m_Duration;
  }

  float VIMciPlayer::GetPosition() {
    return m_CurrentPosition;
  }

  void VIMciPlayer::SetVolume(float v) {
    MCI_SET_PARMS parms;
    parms.dwAudio = v;
    mciSendCommand(m_hDev, MCI_SET_AUDIO, MCI_SET_AUDIO, (DWORD)(LPVOID)&parms);
  }

  void VIMciPlayer::SetNextPlayer(VIMciPlayer* next) {
    m_next_player = next;
  }

  //////////////////////////////////////////////////////////////////////////
  // private member
  //////////////////////////////////////////////////////////////////////////

  void VIMciPlayer::_SendGenericCommand(int nCommand)
  {
    if (! m_hDev)
    {
      return;
    }
    mciSendCommand(m_hDev, nCommand, 0, 0);
  }

  //////////////////////////////////////////////////////////////////////////
  // static function
  //////////////////////////////////////////////////////////////////////////

  LRESULT WINAPI _SoundPlayProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
  {
    VIMciPlayer * pPlayer = NULL;
    if (pPlayer = (VIMciPlayer *)GetWindowLong(hWnd, GWL_USERDATA)) {
      if (Msg == MM_MCINOTIFY) {
        if (wParam == MCI_NOTIFY_SUCCESSFUL ) {
          if (pPlayer->m_next_player) {
            pPlayer->m_next_player->Play(1);
            pPlayer->m_next_player = NULL;
          }
          pPlayer->m_bPlaying = false;
          return 0;
        }
      } else if (Msg == WM_TIMER) {
        MCI_SET_PARMS set;
        MCI_STATUS_PARMS status;

        set.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
        mciSendCommand(pPlayer->m_hDev, MCI_SET, MCI_SET_TIME_FORMAT, (DWORD)(LPVOID)&set);

        status.dwItem = MCI_STATUS_POSITION;
        mciSendCommand(pPlayer->m_hDev, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&status);

        pPlayer->m_CurrentPosition = status.dwReturn;
        return 0;
      }
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
  }


}