*Blanco Uninstaller*
=========

Blanco is basically an uninstaller that was born out of frustration. To make a long story short, I had an HDD where I installed all of my programs (a separate drive than the OS itself). This drive had died. There were a lot of programs that just would not uninstall using the fancy "Add or Remove Programs" utility that Windows has. In some cases where the application in question was successfully uninstalled, it could not be reinstalled. Visual Studio for example, kept telling me "Invalid Drive" whenever I attempted to reinstall it.

For Example: ![Lazy Coders](https://dl.dropbox.com/u/389096/img/vs2012.png "Lazy Coders")

Alas, after a month of search I had found a solution. It turns out that the Windows SDK has a nifty MSI (Windows Installer) public API. I perused through the API and wrote "Blanco." Blanco basically lists all of the programs that Windows thinks that are installed (I say think because the programs that were giving me problems were not actually installed). Once you select the program that you want to uninstall, you can either right click to bring up the context menu, or click the “Uninstall” button to uninstall it.

Fixed VS Install: ![Fixed](https://dl.dropbox.com/u/389096/img/vsfixed.png "Fixed")

How it works.
=========

It calls upon “msiexec.exe” with the parameters “/x {PRODUCT_ID}” the “PRODUCT_ID” is of course automatically populated. So in actuality, Blanco just fetches a list of programs that are installed and if you choose to “Uninstall it,” it will actually use “msiexec.exe” to attempt to uninstall the program in question.
I hope this will be of use to someone else…I know it saved me various reformats.

Requirements
=========
  1) Administrative Access to the computer.
  2) Windows Vista or higher. 

Credits
=========

Author - Juan Baez (jbaez at genscripts.net)
Application Icon: http://www.jigsoaricons.com/
 