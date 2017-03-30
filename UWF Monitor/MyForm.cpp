#include "MyForm.h"
#include "resource.h"
#include <Windows.h>
#include <string>


using namespace Microsoft::Win32;
using namespace System;
using namespace System::Windows::Forms;


//Gets UWF Status from Registry
void getUWF(int& c, int& n)
{
	int current;
	int next;
	HKEY hKey;
	DWORD value_length = sizeof(DWORD);

	if (RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\ControlSet001\\Services\\uwfvol\\Parameters\\Static\\"), &hKey) != ERROR_SUCCESS)
	{
		MessageBox::Show("Unable to open registry key!", "UWF Manager", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	RegQueryValueEx(hKey, TEXT("CurrentSettings"), NULL, NULL, (LPBYTE)&current, &value_length);
	RegQueryValueEx(hKey, TEXT("UpdatedSettings"), NULL, NULL, (LPBYTE)&next, &value_length);

	c = current;
	n = next;

	RegCloseKey(hKey);
	
}


//Get UWF status and return corresponding tray icon.
HICON loadIcon()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HICON Green = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	HICON Orange = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	HICON Red = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON3));

	int current, next;

	getUWF(current, next);

	if (current == 0 && current == next)
	{
		return Red;
	}
	else if (current == 1 && current == next)
	{
		return Green;
	}
	else
	{
		return Orange;
	}
	return 0;
}


//Launch UWF Manager GUI.
int loadMgr()
{

	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = L"C:\\Program Files\\UWF Manager\\uwfgui.exe";
	ShExecInfo.lpParameters = NULL;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteEx(&ShExecInfo))
	{
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
		return 0;
	}
	else
	{
		return 1;
	}
}


// Check if startup item exists, if not, ask the user if they would like to add.
void checkStartup()
{
	HKEY hKey;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"), 0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS)
	{
		MessageBox::Show("Unable to open startup key!", "UWF Manager", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else
	{
		DWORD value_length = sizeof(DWORD);
		if (RegQueryValueEx(hKey, TEXT("UWF_Monitor"), NULL, NULL, NULL, &value_length) != ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			if (MessageBox::Show("Would you like to add the UWF Monitor to system startup?", "UWF Monitor", MessageBoxButtons::YesNo, MessageBoxIcon::Information) == DialogResult::Yes)
			{
				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"), 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS)
				{
					MessageBox::Show("Unable to add to startup items, make sure you are running as administrator.", "UWF Manager", MessageBoxButtons::OK, MessageBoxIcon::Error);
					RegCloseKey(hKey);
					exit(0);
				}
				else
				{
					std::wstring path = TEXT("C:\\Program Files\\UWF Manager\\uwfmon.exe");
					int pathLength = path.length();
					if (RegSetValueEx(hKey, TEXT("UWF_Monitor"), 0, REG_SZ, (LPBYTE)path.c_str(), (path.size() + 1)* sizeof(wchar_t)) != ERROR_SUCCESS)
					{
						MessageBox::Show("Unable to add UWF Monitor to startup, make sure you are running as administrator.", "UWF Monitor", MessageBoxButtons::OK, MessageBoxIcon::Error);
						RegCloseKey(hKey);
						exit(0);
					}
					else
					{
						RegCloseKey(hKey);
						MessageBox::Show("Successfully added to startup! Please make sure this executable is renamed and copied to \"C:\\Program Files\\UWF Manager\\uwfmon.exe\"", "UWF Monitor", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
				}
			}
		}
	}
}


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	checkStartup();

	UWFMonitor::MyForm form;
	Application::Run(%form);
}

