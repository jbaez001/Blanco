#include "stdafx.h"
#include <atlctrls.h>
#include <Msi.h>
#include <string>

#pragma comment(lib, "Msi.lib")

std::wstring GetProductStringInfo(LPCTSTR szProductCode, MSIINSTALLCONTEXT dwContext, 
                            LPCTSTR szSid, DWORD cchSid, LPCTSTR szProperty)
{
  TCHAR tmp[1024] = {0};
  DWORD dwSize = 0;

  if (MsiGetProductInfoEx(szProductCode, cchSid == 0 ? NULL : szSid, 
    dwContext, szProperty, NULL, &dwSize) == ERROR_SUCCESS) {
      MsiGetProductInfoEx(szProductCode, cchSid == 0 ? NULL : szSid, 
        dwContext, szProperty, tmp, &(++dwSize));
  }

  return std::wstring(tmp);
}

void ShowInstalledPrograms(CListViewCtrl mListView) {
  mListView.DeleteAllItems();

  LPCTSTR szUserSid = _T("s-1-1-0");  // All users.
  TCHAR szInstalledProductCode[39] = {0};
  MSIINSTALLCONTEXT dwInstalledContext;
  TCHAR szSid[128] = {0}; 
  DWORD cchSid = 1024;

  for (DWORD dwIndex = 0; MsiEnumProductsEx(NULL, szUserSid, MSIINSTALLCONTEXT_ALL, 
    dwIndex, szInstalledProductCode, &dwInstalledContext, szSid, &cchSid) == ERROR_SUCCESS; dwIndex++) {

      std::wstring wstrProductName(GetProductStringInfo(szInstalledProductCode, dwInstalledContext, szSid, cchSid, INSTALLPROPERTY_INSTALLEDPRODUCTNAME));
      std::wstring wstrPublisher(GetProductStringInfo(szInstalledProductCode, dwInstalledContext, szSid, cchSid, INSTALLPROPERTY_PUBLISHER));
      std::wstring wstrInstallDate(GetProductStringInfo(szInstalledProductCode, dwInstalledContext, szSid, cchSid, INSTALLPROPERTY_INSTALLDATE));

      mListView.InsertItem(dwIndex, szInstalledProductCode);      // Product Code.
      mListView.SetItemText(dwIndex, 1, wstrProductName.c_str()); // Product Name.
      mListView.SetItemText(dwIndex, 2, wstrPublisher.c_str());   // Publisher.
      mListView.SetItemText(dwIndex, 3, wstrInstallDate.c_str()); // Last time installation was updated (patches, etc.).

      ZeroMemory(szInstalledProductCode, sizeof(szInstalledProductCode));
  } 
}

// EOF

