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
#include "gamesettings.h"
#include "Clock.h"
#include "utils.h"
#include "level.h"
#include "playership.h"
#include "PlayerBullet.h"
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
HWND g_hAlienQuantity;
HWND g_hMysteryShipSpeed;
HWND g_hRestoreBarriers;

#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

// Callback for the Debug window
BOOL CALLBACK
DebugDlgProc(HWND hDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CGame& rGame = CGame::GetInstance();
	CGameSettings& rGameSettings = CGameSettings::GetInstance();
	ShowCursor(TRUE);
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		// Store each combo box in its respective handle
		g_hPlayerSpeed = GetDlgItem(hDlg, IDC_COMBO8);
		g_hPlayerBulletSpeed = GetDlgItem(hDlg, IDC_COMBO4);
		g_hPlayerLives = GetDlgItem(hDlg, IDC_COMBO6);
		g_hAlienSpeed = GetDlgItem(hDlg, IDC_COMBO1);
		g_hAlien1BulletSpeed = GetDlgItem(hDlg, IDC_COMBO2);
		g_hAlien2BulletSpeed = GetDlgItem(hDlg, IDC_COMBO5);
		g_hAlien3BulletSpeed = GetDlgItem(hDlg, IDC_COMBO7);
		g_hAlienQuantity = GetDlgItem(hDlg, IDC_COMBO3);
		g_hMysteryShipSpeed = GetDlgItem(hDlg, IDC_COMBO9);

		int CurrentIndex = 0;

		// Add each dropdown option to their respective combo box
		// Player Speed
		SendMessage(g_hPlayerSpeed, CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetPlayerSpeedText(0));
		SendMessage(g_hPlayerSpeed, CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetPlayerSpeedText(1));
		SendMessage(g_hPlayerSpeed, CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetPlayerSpeedText(2));
		SendMessage(g_hPlayerSpeed, CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetPlayerSpeedText(3));
		SendMessage(g_hPlayerSpeed, CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetPlayerSpeedText(4));
		SendMessage(g_hPlayerSpeed, CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetPlayerSpeedText(5));

		CurrentIndex = (rGameSettings.GetPlayerSpeed() / 100) - 1;
		SendMessage(g_hPlayerSpeed, CB_SETCURSEL, (WPARAM)CurrentIndex, (LPARAM)0);

		// Player Bullet Speed
		SendMessage(g_hPlayerBulletSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerBulletSpeedText(0));
		SendMessage(g_hPlayerBulletSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerBulletSpeedText(1));
		SendMessage(g_hPlayerBulletSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerBulletSpeedText(2));
		SendMessage(g_hPlayerBulletSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerBulletSpeedText(3));
		SendMessage(g_hPlayerBulletSpeed, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerBulletSpeedText(4));

		CurrentIndex = (rGameSettings.GetPlayerBulletSpeed() / 50) - 1;
		SendMessage(g_hPlayerBulletSpeed, CB_SETCURSEL, (WPARAM)CurrentIndex, (LPARAM)0);

		// Player Lives
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerLivesText(0));
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerLivesText(1));
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerLivesText(2));
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerLivesText(3));
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerLivesText(4));
		SendMessage(g_hPlayerLives, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)rGameSettings.GetPlayerLivesText(5));

		CurrentIndex = (rGameSettings.GetPlayerLives());
		SendMessage(g_hPlayerLives, CB_SETCURSEL, (WPARAM)CurrentIndex, (LPARAM)0);

		// Alien Speed
		SendMessage(g_hAlienSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienSpeedText(0));
		SendMessage(g_hAlienSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienSpeedText(1));
		SendMessage(g_hAlienSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienSpeedText(2));
		SendMessage(g_hAlienSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienSpeedText(3));
		SendMessage(g_hAlienSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienSpeedText(4));

		CurrentIndex = (rGameSettings.GetAlienSpeed() / 10) - 1;
		SendMessage(g_hAlienSpeed, CB_SETCURSEL, (WPARAM)CurrentIndex, (LPARAM)0);

		// Alien 1 Bullet Speed
		SendMessage(g_hAlien1BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(0));
		SendMessage(g_hAlien1BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(1));
		SendMessage(g_hAlien1BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(2));
		SendMessage(g_hAlien1BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(3));
		SendMessage(g_hAlien1BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(4));

		CurrentIndex = (rGameSettings.GetAlienType1BulletSpeed() / 25) - 1;
		SendMessage(g_hAlien1BulletSpeed, CB_SETCURSEL, (WPARAM)CurrentIndex, (LPARAM)0);

		// Alien 2 Bullet Speed
		SendMessage(g_hAlien2BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(0));
		SendMessage(g_hAlien2BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(1));
		SendMessage(g_hAlien2BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(2));
		SendMessage(g_hAlien2BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(3));
		SendMessage(g_hAlien2BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(4));

		CurrentIndex = (rGameSettings.GetAlienType2BulletSpeed() / 25) - 1;
		SendMessage(g_hAlien2BulletSpeed, CB_SETCURSEL, (WPARAM)CurrentIndex, (LPARAM)0);

		// Alien 3 Bullet Speed
		SendMessage(g_hAlien3BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(0));
		SendMessage(g_hAlien3BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(1));
		SendMessage(g_hAlien3BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(2));
		SendMessage(g_hAlien3BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(3));
		SendMessage(g_hAlien3BulletSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienBulletSpeedText(4));

		CurrentIndex = (rGameSettings.GetAlienType3BulletSpeed() / 25) - 1;
		SendMessage(g_hAlien3BulletSpeed, CB_SETCURSEL, (WPARAM)CurrentIndex, (LPARAM)0);

		// Alien Quantity
		SendMessage(g_hAlienQuantity, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienQuantityText(0));
		SendMessage(g_hAlienQuantity, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienQuantityText(1));
		SendMessage(g_hAlienQuantity, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienQuantityText(2));
		SendMessage(g_hAlienQuantity, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienQuantityText(3));
		SendMessage(g_hAlienQuantity, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienQuantityText(4));
		SendMessage(g_hAlienQuantity, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetAlienQuantityText(5));

		CurrentIndex = (rGameSettings.GetAlienQuantity() / 10);
		SendMessage(g_hAlienQuantity, CB_SETCURSEL, (WPARAM)CurrentIndex, (LPARAM)0);

		// Mystery Ship Speed
		SendMessage(g_hMysteryShipSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetMysteryShipSpeedText(0));
		SendMessage(g_hMysteryShipSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetMysteryShipSpeedText(1));
		SendMessage(g_hMysteryShipSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetMysteryShipSpeedText(2));
		SendMessage(g_hMysteryShipSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetMysteryShipSpeedText(3));
		SendMessage(g_hMysteryShipSpeed, (UINT)CB_ADDSTRING, 0, (LPARAM)rGameSettings.GetMysteryShipSpeedText(4));

		CurrentIndex = (rGameSettings.GetMysteryShipSpeed() / 25) - 1;
		SendMessage(g_hMysteryShipSpeed, CB_SETCURSEL, (WPARAM)CurrentIndex, (LPARAM)0);
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

			// Adjust player speed to selected value
			g_hPlayerSpeed = GetDlgItem(hDlg, IDC_COMBO8);
			iIndex = SendMessage(g_hPlayerSpeed, CB_GETCURSEL, 0, 0);
			rGameSettings.SetPlayerSpeed(iIndex);

			// Adjust player bullet speed to selected value
			g_hPlayerBulletSpeed = GetDlgItem(hDlg, IDC_COMBO4);
			iIndex = SendMessage(g_hPlayerBulletSpeed, CB_GETCURSEL, 0, 0);
			rGameSettings.SetPlayerBulletSpeed(iIndex);
			CPlayerBullet* pBullet = rGame.GetLevel()->GetPlayerBullet();
			pBullet->SetVelocityY(rGameSettings.GetPlayerBulletSpeed());

			// Adjust player lives to selected value
			g_hPlayerLives = GetDlgItem(hDlg, IDC_COMBO6);
			iIndex = SendMessage(g_hPlayerLives, CB_GETCURSEL, 0, 0);
			rGameSettings.SetPlayerLives(iIndex);

			// Adjust alien speed to selected value
			g_hAlienSpeed = GetDlgItem(hDlg, IDC_COMBO1);
			iIndex = SendMessage(g_hAlienSpeed, CB_GETCURSEL, 0, 0);
			rGameSettings.SetAlienSpeed(iIndex);

			// Adjust alien 1 bullet speed to selected value
			g_hAlien1BulletSpeed = GetDlgItem(hDlg, IDC_COMBO2);
			iIndex = SendMessage(g_hAlien1BulletSpeed, CB_GETCURSEL, 0, 0);
			rGameSettings.SetAlienType1BulletSpeed(iIndex);

			// Adjust alien 2 bullet speed to selected value
			g_hAlien2BulletSpeed = GetDlgItem(hDlg, IDC_COMBO5);
			iIndex = SendMessage(g_hAlien2BulletSpeed, CB_GETCURSEL, 0, 0);
			rGameSettings.SetAlienType2BulletSpeed(iIndex);

			// Adjust alien 3 bullet speed to selected value
			g_hAlien3BulletSpeed = GetDlgItem(hDlg, IDC_COMBO7);
			iIndex = SendMessage(g_hAlien3BulletSpeed, CB_GETCURSEL, 0, 0);
			rGameSettings.SetAlienType3BulletSpeed(iIndex);

			// Adjust the number of aliens to selected value
			g_hAlienQuantity = GetDlgItem(hDlg, IDC_COMBO3);
			iIndex = SendMessage(g_hAlienQuantity, CB_GETCURSEL, 0, 0);
			rGameSettings.SetAlienQuantity(iIndex);

			// Adjust the mystery ship movement speed to selected value
			g_hMysteryShipSpeed = GetDlgItem(hDlg, IDC_COMBO9);
			iIndex = SendMessage(g_hMysteryShipSpeed, CB_GETCURSEL, 0, 0);
			rGameSettings.SetMysteryShipSpeed(iIndex);

			g_hRestoreBarriers = GetDlgItem(hDlg, IDC_CHECK1);

			if (SendDlgItemMessage(hDlg, IDC_CHECK1, BM_GETCHECK, 0, 0))
			{
				rGame.GetLevel()->RestoreBarriers();
			}
			else
			{
				// Do nothing
			}

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
	
	rGame.GetHighScores();

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
			rGame.ExecuteOneFrame();
		}
	}

	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}
