//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	:	
// Description	: 
// Author		:	Mati Green and Roger Smith
// Mail			:	matitahi.gre7573@mediadesign.school.nz
//				:	roger.smi7429@mediadesign.school.nz
//

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

#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

// Callback for the Debug window
BOOL CALLBACK
DebugDlgProc(HWND hDlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		break;
	}
	
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))
		{
		case IDOK:
		{
			EndDialog(hDlg, 0);
			return TRUE;
			break;
		}
		default:break;
		}
	}
	
	case WM_CLOSE:
	{
		EndDialog(hDlg, 0);
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
			rGame.ExecuteOneFrame();
		}
	}

	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}
