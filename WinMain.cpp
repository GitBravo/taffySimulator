#include "Simulator.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE _hInstance;
Simulator simulator;
Simulator simulator2;

DWORD WINAPI ThreadFunction(LPVOID pvoid)
{
	simulator.Run();
	return 0;
}
DWORD WINAPI ThreadFunction2(LPVOID pvoid)
{
	simulator2.Run();
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArg, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;
	WndClass.style = NULL;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = TEXT("Hello");

	if (!RegisterClass(&WndClass)) return NULL;

	hWnd = CreateWindow(
		TEXT("Hello"),
		TEXT("Taffy Simulator"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		520,
		350,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT mesg, WPARAM wParam, LPARAM lParam)
{
	WCHAR str1[50];
	WCHAR str2[50];
	WCHAR str3[50];
	WCHAR str4[50];

	WCHAR str5[50];
	WCHAR str6[50];
	WCHAR str7[50];
	WCHAR str8[50];

	WCHAR str9[50];

	WCHAR str10[50];
	WCHAR str11[50];
	WCHAR str12[50];
	WCHAR str13[50];
	HDC hdc = GetDC(hWnd);

	static HWND hBtn1 = NULL;
	static HWND hBtn2 = NULL;
	static HWND hBtn3 = NULL;
	static HWND hBtn4 = NULL;
	static HANDLE Thread1 = NULL;
	static HANDLE Thread2 = NULL;
	switch (mesg)
	{
	case WM_CREATE:
		Thread1 = CreateThread(NULL, 0, ThreadFunction, NULL, 0, NULL);
		Thread2 = CreateThread(NULL, 0, ThreadFunction2, NULL, 0, NULL);
		hBtn1 = CreateWindow(
			TEXT("BUTTON"),
			TEXT("1번 전화"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			300,
			200,
			75,
			40,
			hWnd,
			(HMENU)111,
			_hInstance,
			NULL
		);
		hBtn2 = CreateWindow(
			TEXT("BUTTON"),
			TEXT("재개"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			300,
			240,
			75,
			40,
			hWnd,
			(HMENU)222,
			_hInstance,
			NULL
		);
		hBtn3 = CreateWindow(
			TEXT("BUTTON"),
			TEXT("2번 전화"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			375,
			200,
			75,
			40,
			hWnd,
			(HMENU)333,
			_hInstance,
			NULL
		);
		hBtn4 = CreateWindow(
			TEXT("BUTTON"),
			TEXT("재개"),
			WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			375,
			240,
			75,
			40,
			hWnd,
			(HMENU)444,
			_hInstance,
			NULL
		);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	case WM_COMMAND:
		if (LOWORD(wParam) == 111)
			SuspendThread(Thread1);
		else if (LOWORD(wParam) == 222)
			ResumeThread(Thread1);
		else if (LOWORD(wParam) == 333)
			SuspendThread(Thread2);
		else if (LOWORD(wParam) == 444)
			ResumeThread(Thread2);
		break;
	case WM_PAINT:
		TextOut(hdc, 50, 30, TEXT("< 1번 창구 서비스 고객 >"), 16);
		wsprintf(str1, TEXT("고객 번호 : %d번"), simulator.GetCurrentStatistic().custNum);
		wsprintf(str2, TEXT("도착 시간 : %d시 %d분"), 8 + ((int)simulator.GetCurrentStatistic().arriveTime) / 60, (int)simulator.GetCurrentStatistic().arriveTime % 60);
		wsprintf(str3, TEXT("시작 시간 : %d시 %d분"), 8 + ((int)simulator.GetCurrentStatistic().startTime) / 60, (int)simulator.GetCurrentStatistic().startTime % 60);
		wsprintf(str4, TEXT("서비스 시간 : %d분"), simulator.GetCurrentStatistic().svcTime);
		TextOut(hdc, 50, 50, str1, lstrlen(str1));
		TextOut(hdc, 50, 70, str2, lstrlen(str2));
		TextOut(hdc, 50, 90, str3, lstrlen(str3));
		TextOut(hdc, 50, 110, str4, lstrlen(str4));

		TextOut(hdc, 300, 30, TEXT("< 통계 >"), 6);
		wsprintf(str5, TEXT("총 서비스 고객 수 : %d명"), simulator.GetFinalStatistic().custNum + simulator2.GetFinalStatistic().custNum);
		wsprintf(str6, TEXT("총 서비스 시간 : %d시간 %d분"), (simulator.GetFinalStatistic().totSvcTime + simulator2.GetFinalStatistic().totSvcTime) / 60, (simulator.GetFinalStatistic().totSvcTime + simulator2.GetFinalStatistic().totSvcTime) % 60);
		wsprintf(str7, TEXT("최대 대기 고객 수 : %d명"), simulator.GetFinalStatistic().maxQueueSize);
		wsprintf(str8, TEXT("평균 대기 시간 : %d분"), simulator.GetFinalStatistic().totWaitTime);
		TextOut(hdc, 300, 50, str5, lstrlen(str5));
		TextOut(hdc, 300, 70, str6, lstrlen(str6));
		TextOut(hdc, 300, 90, str7, lstrlen(str7));
		TextOut(hdc, 300, 110, str8, lstrlen(str8));

		TextOut(hdc, 300, 150, TEXT("< 현재시간 >"), 8);
		wsprintf(str9, TEXT("현재시간 : %d시 %d분"), 8 + (int)simulator.GetGlobalSecond() / 60, (int)simulator.GetGlobalSecond() % 60);
		TextOut(hdc, 300, 170, str9, lstrlen(str9));

		TextOut(hdc, 50, 150, TEXT("< 2번 창구 서비스 고객 >"), 16);
		wsprintf(str10, TEXT("고객 번호 : %d번"), simulator2.GetCurrentStatistic().custNum);
		wsprintf(str11, TEXT("도착 시간 : %d시 %d분"), 8 + ((int)simulator2.GetCurrentStatistic().arriveTime) / 60, (int)simulator2.GetCurrentStatistic().arriveTime % 60);
		wsprintf(str12, TEXT("시작 시간 : %d시 %d분"), 8 + ((int)simulator2.GetCurrentStatistic().startTime) / 60, (int)simulator2.GetCurrentStatistic().startTime % 60);
		wsprintf(str13, TEXT("서비스 시간 : %d분"), simulator2.GetCurrentStatistic().svcTime);
		TextOut(hdc, 50, 170, str10, lstrlen(str10));
		TextOut(hdc, 50, 190, str11, lstrlen(str11));
		TextOut(hdc, 50, 210, str12, lstrlen(str12));
		TextOut(hdc, 50, 230, str13, lstrlen(str13));

		ReleaseDC(hWnd, hdc);
		break;
	}
	return DefWindowProc(hWnd, mesg, wParam, lParam);
}