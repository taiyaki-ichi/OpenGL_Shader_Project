#include"window.hpp"

namespace window
{
    //イベント処理
    //最低限の機能しかない
    LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	std::optional<HWND> create(std::string&& windowName, float windowWidth, float windowHeight)
	{
        HWND hwnd;
        HINSTANCE hInstance = GetModuleHandle(NULL);
        if (!hInstance)
            return nullptr;


        // シンプルウィンドウクラス設定
        WNDCLASSEX wcex = {
            sizeof(WNDCLASSEX),
            CS_HREDRAW | CS_VREDRAW,
            WndProc,
            0,
            0,
            hInstance,
            LoadIcon(NULL, IDI_APPLICATION),
            LoadCursor(NULL, IDC_ARROW),
            NULL,
            NULL,
            windowName.c_str(),
            NULL
        };

        if (!RegisterClassEx(&wcex))
            return std::nullopt;


        //ウィンドウの生成
        hwnd = CreateWindowEx(
            0,
            windowName.c_str(),
            TEXT(windowName.c_str()),
            (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
            CW_USEDEFAULT,
            0,
            static_cast<int>(windowWidth),
            static_cast<int>(windowHeight),
            NULL,
            NULL,
            hInstance,
            NULL);

        if (!hwnd)
            return std::nullopt;

        //ウィンドウの整形
        RECT rc1;
        RECT rc2;
        GetWindowRect(hwnd, &rc1);
        GetClientRect(hwnd, &rc2);
        windowWidth += ((rc1.right - rc1.left) - (rc2.right - rc2.left));
        windowHeight += ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top));
        SetWindowPos(hwnd, NULL, 0, 0, static_cast<int>(windowWidth), static_cast<int>(windowHeight), (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));

        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);

        return hwnd;
	}

    //ウィンドウの破壊メッセを処理、最低限のウィンドウの機能のみここで実装
    LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
            break;

        }

        return 0;
    }
}