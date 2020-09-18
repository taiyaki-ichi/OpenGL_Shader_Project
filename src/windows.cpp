#include"windows.hpp"

namespace windows
{
    //イベント処理の前方宣言
    //最低限の機能しかない
    LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	std::optional<HWND> create_window(std::string&& windowName, float windowWidth, float windowHeight)
	{
        //ハンドルの獲得
        HWND hwnd;
        HINSTANCE hInstance = GetModuleHandle(NULL);
        if (!hInstance)
            return std::nullopt;

        // ウィンドウクラス設定
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



    std::optional<std::pair<HDC, HGLRC>> init_opengl(HWND hwnd)
    {
        // ピクセルフォーマット初期化
        PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),  //サイズ
            1,  //1固定
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //描写可能、OpenGL使用可能、ダブルバッファリング
            PFD_TYPE_RGBA, //赤、緑、青、アルファ値の順で色指定
            32, //各カラーバッファのカラービットプレーンの数
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24, //深度（z軸）バッファの深度
            8, //ステンシルバッファ
            0, //補助バッファの数
            PFD_MAIN_PLANE, //今は使われてない
            0,  //オーバーレイとアンダーレイの面の数
            0, 0, 0
        };

        //デバイスコンテキストの取得
        HDC dc = GetDC(hwnd);
        int format = ChoosePixelFormat(dc, &pfd);
        // 該当するピクセルフォーマットが無い場合
        if (format == 0)
            return std::nullopt; 

        // OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
        if (!SetPixelFormat(dc, format, &pfd))
            return std::nullopt;

        // OpenGL contextを作成
        HGLRC glRC = wglCreateContext(dc);

        // 作成されたコンテキストが現在使用中のコンテキストかどうか
        if (!wglMakeCurrent(dc, glRC))
            return std::nullopt;

        return std::make_pair(dc, glRC);
    }


    void shutdown(HWND hwnd, HDC hdc, HGLRC hglrc)
    {

        //カレントコンテキストを無効にする
        wglMakeCurrent(NULL, NULL);

        //カレントコンテキストを削除
        //nullでも動いたのでチェックしない
        wglDeleteContext(hglrc);

        //デバイスコンテキストを開放
        ReleaseDC(hwnd, hdc);
    }
}