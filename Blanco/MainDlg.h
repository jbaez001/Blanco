// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

extern void ShowInstalledPrograms(CListViewCtrl mListView);

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
    public CMessageFilter, public CIdleHandler
{
private:
  CListViewCtrl mListView;

public:
  enum { IDD = IDD_MAINDLG };

  virtual BOOL PreTranslateMessage(MSG* pMsg)
  {
    return CWindow::IsDialogMessage(pMsg);
  }

  virtual BOOL OnIdle()
  {
    UIUpdateChildWindows();
    return FALSE;
  }

  BEGIN_UPDATE_UI_MAP(CMainDlg)
  END_UPDATE_UI_MAP()

  BEGIN_MSG_MAP(CMainDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    COMMAND_ID_HANDLER(IDOK, OnOK)
    COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
  END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//  LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//  LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//  LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

  LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  {
    // center the dialog on the screen
    CenterWindow();

    // set icons
    HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
    SetIcon(hIcon, TRUE);
    HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
    SetIcon(hIconSmall, FALSE);

    // register object for message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);

    UIAddChildWindowContainer(m_hWnd);


    // List of columns.

    struct sColumns {
      LPCTSTR strName;
      int iSize;
    };

    sColumns columns[] = {
      { _T("Product ID"), 260 },
      { _T("Product Name"), 360 },
      { _T("Publisher"), 200 },
      { _T("Install Date"), 100 }
    };

    // Installed Product List
    mListView.Attach(GetDlgItem(IDC_LIST_PRODUCTS));

    // Populate the column headers and set their sizes accordingly.
    for (int i = 0; i < sizeof(columns)/sizeof(columns[0]); i++) {
      mListView.InsertColumn(i, columns[i].strName, LVCFMT_LEFT, -1, -1);
      mListView.SetColumnWidth(i, columns[i].iSize);
    }
    ShowInstalledPrograms(mListView);

    return TRUE;
  }

  LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  {
    // unregister message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->RemoveMessageFilter(this);
    pLoop->RemoveIdleHandler(this);

    return 0;
  }

  LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
  {
    // TODO: Add validation code 
    CloseDialog(wID);
    return 0;
  }

  LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
  {
    CloseDialog(wID);
    return 0;
  }

  void CloseDialog(int nVal)
  {
    DestroyWindow();
    ::PostQuitMessage(nVal);
  }
};
