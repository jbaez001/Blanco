/*************************************************************************
 * Blanco - InstalledPrograms.cc
 * Copyright (c) 2012 Juan Baez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include "stdafx.h"
#include <Msi.h>

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

