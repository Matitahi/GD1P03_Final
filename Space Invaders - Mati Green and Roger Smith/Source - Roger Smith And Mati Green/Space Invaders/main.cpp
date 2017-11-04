//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: main.cpp
// Description	: Controls application and high-level implementation logic
// Author		: Matitahi Green and Roger Smith
// Mail			: matitahi.gre7573@mediadesign.school.nz
//				: roger.smi7429@mediadesign.school.nz

//Library Includes
#include <windows.h>
#include <windowsx.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "level.h"
#include "playership.h"
#include "resource.h"

const int kiWidth = 400;
const int kiHeight = 400;

HINSTANCE g_hInstance;

HWND g_hPlayerSpeed;
HWND g_hPlayerBulletSpeed;
HWND g_hPlayerLives;
HWND g_hAlienSpeed;
HWND g_hAlien1BulletSpeed;
HWND g_hAlien2BulletSpeed;
HWND g_hAlien3BulletSpeed;
HWND g_hAlienNumber;
HWND g_hMysteryShipSpeed;

TCHAR* g_cPlayerSpeed[6] = { TEXT("100"), TEXT("200"), TEXT("300"), TEXT("400"), TEXT("500"), TEXT("600") };
TCHAR* g_cPlayerBulletSpeed[5] = { TEXT("50"), TEXT("100"), TEXT("150"), TEXT("200"), TEXT("250") };
TCHAR* g_cPlayerLives[6] = { TEXT("0"), TEXT("1"), TEXT("2"), TEXT("3"), TEXT("4"), TEXT("5") };
TCHAR* g_cAlienSpeed[5] = { TEXT("10"), TEXT("20"), TEXT("30"), TEXT("40"), TEXT("50") };
TCHAR* g_cAlien1BulletSpeed[5] = { TEXT("25"), TEXT("50"), TEXT("75"), TEXT("100"), TEXT("125") };
TCHAR* g_cAlien2BulletSpeed[5] = { TEXT("25"), TEXT("50"), TEXT("75"), TEXT("100"), TEXT("125") };
TCHAR* g_cAlien3BulletSpeed[5] = { TEXT("25"), TEXT("50"), TEXT("75"), TEXT("100"), TEXT("125") };
TCHAR* g_cAlienNumber[6] = { TEXT("1"), TEXT("11 (one row)"), TEXT("22 (two rows)"),
	TEXT("33 (three rows)"), TEXT("44 (four rows)"), TEXT("55 (five rows)") };
TCHAR* g_cMysteryShipSpeed[5];

// Change this to a singleton pattern
float g_fPlayerSpeed[6] = { 100.0, 200.0, 300.0, 400.0, 500.0, 600.0 };
float g_fPlayerBulletSpeed[5] = { 50.0, 100.0, 150.0, 200.0, 250.0 };
int g_iPlayerLives[6] = { 0, 1, 2, 3, 4, 5 };
float g_fAlienSpeed[5] = { 10.0, 20.0, 30.0, 40.0, 50.0 };
float g_fAlienBulletSpeed[5] = { 25.0, 50.0, 75.0, 100.0, 125.0 };
int g_iAlienNumber[6] = { 1, 11, 22, 33, 44, 55 };

#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

// Callback for the Debug window
BOOL CALLBACK
DebugDlgProc(HWND hDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	ShowCursor(TRUE);
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		// Store each combo box in it's respective handle
		g_hPlayerSpeed = GetDlgItem(hDlg, IDC_COMBO8);
		g_hPlayerBulletSpeed = GetDlgItem(hDlg, IDC_COMBO4);
		g_hPlayerLives = GetDlgItem(hDlg, IDC_COMBO6);
		g_hAlienSpeed = GetDlgItem(hDlg, IDC_COMBO1);
		g_hAlien1BulletSpeed = GetDlgItem(hDlg, IDC_COMBO2);
		g_hAlien2BulletSpeed = GetDlgItem(hDlg, IDC_COMBO5);
		g_hAlien3BulletSpeed = GetDlgItem(hDlg, IDC_COMBO7);
		g_hAlienNumber = GetDlgItem(hDlg, IDC_COMBO3);

		// Add each dropdown option to their respective combo box
		// Player Speed
		SendMessage(g_hPlayerSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerSpeed[0]);
		SendMessage(g_hPlayerSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerSpeed[1]);
		SendMessage(g_hPlayerSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerSpeed[2]);
		SendMessage(g_hPlayerSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerSpeed[3]);
		SendMessage(g_hPlayerSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerSpeed[4]);
		SendMessage(g_hPlayerSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerSpeed[5]);

		SendMessage(g_hPlayerSpeed, CB_SETCURSEL, (WPARAM)3, (LPARAM)0);

		// Player Bullet Speed
		SendMessage(g_hPlayerBulletSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerBulletSpeed[0]);
		SendMessage(g_hPlayerBulletSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerBulletSpeed[1]);
		SendMessage(g_hPlayerBulletSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerBulletSpeed[2]);
		SendMessage(g_hPlayerBulletSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerBulletSpeed[3]);
		SendMessage(g_hPlayerBulletSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerBulletSpeed[4]);

		SendMessage(g_hPlayerBulletSpeed, CB_SETCURSEL, (WPARAM)4, (LPARAM)0);

		// Player Lives
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerLives[0]);
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerLives[1]);
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerLives[2]);
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerLives[3]);
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerLives[4]);
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)g_cPlayerLives[5]);

		SendMessage(g_hPlayerLives, CB_SETCURSEL, (WPARAM)3, (LPARAM)0);

		// Alien Speed
		SendMessage(g_hAlienSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienSpeed[0]);
		SendMessage(g_hAlienSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienSpeed[1]);
		SendMessage(g_hAlienSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienSpeed[2]);
		SendMessage(g_hAlienSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienSpeed[3]);
		SendMessage(g_hAlienSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienSpeed[4]);

		SendMessage(g_hAlienSpeed, CB_SETCURSEL, (WPARAM)4, (LPARAM)0);

		// Alien 1 Bullet Speed
		SendMessage(g_hAlien1BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien1BulletSpeed[0]);
		SendMessage(g_hAlien1BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien1BulletSpeed[1]);
		SendMessage(g_hAlien1BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien1BulletSpeed[2]);
		SendMessage(g_hAlien1BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien1BulletSpeed[3]);
		SendMessage(g_hAlien1BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien1BulletSpeed[4]);

		SendMessage(g_hAlien1BulletSpeed, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

		// Alien 2 Bullet Speed
		SendMessage(g_hAlien2BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien2BulletSpeed[0]);
		SendMessage(g_hAlien2BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien2BulletSpeed[1]);
		SendMessage(g_hAlien2BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien2BulletSpeed[2]);
		SendMessage(g_hAlien2BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien2BulletSpeed[3]);
		SendMessage(g_hAlien2BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien2BulletSpeed[4]);

		SendMessage(g_hAlien2BulletSpeed, CB_SETCURSEL, (WPARAM)3, (LPARAM)0);

		// Alien 3 Bullet Speed
		SendMessage(g_hAlien3BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien3BulletSpeed[0]);
		SendMessage(g_hAlien3BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien3BulletSpeed[1]);
		SendMessage(g_hAlien3BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien3BulletSpeed[2]);
		SendMessage(g_hAlien3BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien3BulletSpeed[3]);
		SendMessage(g_hAlien3BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlien3BulletSpeed[4]);

		SendMessage(g_hAlien3BulletSpeed, CB_SETCURSEL, (WPARAM)4, (LPARAM)0);

		// Alien Number
		SendMessage(g_hAlienNumber, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienNumber[0]);
		SendMessage(g_hAlienNumber, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienNumber[1]);
		SendMessage(g_hAlienNumber, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienNumber[2]);
		SendMessage(g_hAlienNumber, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienNumber[3]);
		SendMessage(g_hAlienNumber, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienNumber[4]);
		SendMessage(g_hAlienNumber, (UINT)CB_ADDSTRING, 0, (LPARAM)g_cAlienNumber[5]);

		SendMessage(g_hAlienNumber, CB_SETCURSEL, (WPARAM)5, (LPARAM)0);

		return FALSE;
		break;
	}
	
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))
		{

		case IDOK:
		{
			int iIndex = 0;

			// Adjust player bullet speed to selected value
			g_hPlayerBulletSpeed = GetDlgItem(hDlg, IDC_COMBO4);
			iIndex = SendMessage(g_hPlayerBulletSpeed, CB_GETCURSEL, 0, 0);
			

			// Adjust player lives to selected value
			g_hPlayerLives = GetDlgItem(hDlg, IDC_COMBO6);
			iIndex = SendMessage(g_hPlayerLives, CB_GETCURSEL, 0, 0);
			//g_iPlayerLives = iIndex;

			// Adjust alien speed to selected value
			g_hAlienSpeed = GetDlgItem(hDlg, IDC_COMBO1);
			iIndex = SendMessage(g_hAlienSpeed, CB_GETCURSEL, 0, 0);
			//g_fAlienSpeed = (iIndex * 10) + 10;

			// Adjust alien 1 bullet speed to selected value
			g_hAlien1BulletSpeed = GetDlgItem(hDlg, IDC_COMBO2);
			iIndex = SendMessage(g_hAlien1BulletSpeed, CB_GETCURSEL, 0, 0);
			//g_fAlien1BulletSpeed = (iIndex * 25) + 25;

			// Adjust alien 2 bullet speed to selected value
			g_hAlien2BulletSpeed = GetDlgItem(hDlg, IDC_COMBO5);
			iIndex = SendMessage(g_hAlien2BulletSpeed, CB_GETCURSEL, 0, 0);
			//g_fAlien2BulletSpeed = (iIndex * 25) + 25;

			// Adjust alien 3 bullet speed to selected value
			g_hAlien3BulletSpeed = GetDlgItem(hDlg, IDC_COMBO7);
			iIndex = SendMessage(g_hAlien3BulletSpeed, CB_GETCURSEL, 0, 0);
			//g_fAlien3BulletSpeed = (iIndex * 25) + 25;

			// Adjust the number of aliens to selected value
			g_hAlienNumber = GetDlgItem(hDlg, IDC_COMBO3);
			iIndex = SendMessage(g_hAlienNumber, CB_GETCURSEL, 0, 0);
			//g_iAlienNumber = (iIndex * 10) + 1; 

			EndDialog(hDlg, 0);
			ShowCursor(FALSE);
			return TRUE;
			break;
		}

		case IDCANCEL:
		{
			EndDialog(hDlg, 0);
			ShowCursor(FALSE);
			return TRUE;
			break;
		}

		default:break;
		}
		break;
	}
	
	case WM_CLOSE:
	{
		EndDialog(hDlg, 0);
		ShowCursor(FALSE);
		return TRUE;
		break;
	}
	default:break;
	}
	return FALSE;
}

LRESULT CALLBACK
WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMsg)
	{
	case WM_KEYDOWN:
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DEBUG), NULL, DebugDlgProc);
		}

		break;
	}
	case WM_MOUSEMOVE:
	{
		int iMouseX = LOWORD(_lParam);
		//CGame::GetInstance().GetLevel()->GetPaddle()->SetX(static_cast<float>(iMouseX));
		return (0);
	}
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return(0);
	}
		break;

	default:break;
	}

	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

HWND
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, const wchar_t* _pcTitle)
{
	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
	{
		// Failed to register.
		return (0);
	}

	HWND hwnd;
	hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		_pcTitle,
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		_iWidth, _iHeight,
		NULL,
		NULL,
		_hInstance,
		NULL);

	if (!hwnd)
	{
		// Failed to create.
		return (0);
	}

	return (hwnd);
}

int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	MSG msg;
	RECT _rect;
	ZeroMemory(&msg, sizeof(MSG));

	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Space Invaders");

	CGame& rGame = CGame::GetInstance();
	
	GetClientRect(hwnd, &_rect);

	//if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	if (!rGame.Initialise(_hInstance, hwnd, _rect.right, _rect.bottom))
	{
		// Failed
		return (0);
	}

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//rGame.GetInstance().GetLevel()->GetPlayerShip()-
			//rGame.GetInstance().GetLevel()->SetPlayerBulletSpeed(g_fAlien1BulletSpeed);
			//rGame.GetInstance().GetLevel()->GetPlayerShip()->SetLives(g_iPlayerLives);
			//rGame.GetInstance().GetLevel()->SetAlienSpeed(g_fAlien1BulletSpeed);
			//rGame.GetInstance().GetLevel()->SetType1BulletSpeed(g_fAlien1BulletSpeed);
			//rGame.GetInstance().GetLevel()->SetType2BulletSpeed(g_fAlien2BulletSpeed);
			//rGame.GetInstance().GetLevel()->SetType3BulletSpeed(g_fAlien3BulletSpeed);
			//rGame.GetInstance().GetLevel()->SetEnemiesRemaining(g_iAlienNumber);

			rGame.ExecuteOneFrame();
		}
	}

	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}
