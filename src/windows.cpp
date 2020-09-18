#include"windows.hpp"

namespace windows
{
    //�C�x���g�����̑O���錾
    //�Œ���̋@�\�����Ȃ�
    LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	std::optional<HWND> create_window(std::string&& windowName, float windowWidth, float windowHeight)
	{
        //�n���h���̊l��
        HWND hwnd;
        HINSTANCE hInstance = GetModuleHandle(NULL);
        if (!hInstance)
            return std::nullopt;

        // �E�B���h�E�N���X�ݒ�
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

        //�E�B���h�E�̐���
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

        //�E�B���h�E�̐��`
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

    //�E�B���h�E�̔j�󃁃b�Z�������A�Œ���̃E�B���h�E�̋@�\�݂̂����Ŏ���
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
        // �s�N�Z���t�H�[�}�b�g������
        PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),  //�T�C�Y
            1,  //1�Œ�
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //�`�ʉ\�AOpenGL�g�p�\�A�_�u���o�b�t�@�����O
            PFD_TYPE_RGBA, //�ԁA�΁A�A�A���t�@�l�̏��ŐF�w��
            32, //�e�J���[�o�b�t�@�̃J���[�r�b�g�v���[���̐�
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24, //�[�x�iz���j�o�b�t�@�̐[�x
            8, //�X�e���V���o�b�t�@
            0, //�⏕�o�b�t�@�̐�
            PFD_MAIN_PLANE, //���͎g���ĂȂ�
            0,  //�I�[�o�[���C�ƃA���_�[���C�̖ʂ̐�
            0, 0, 0
        };

        //�f�o�C�X�R���e�L�X�g�̎擾
        HDC dc = GetDC(hwnd);
        int format = ChoosePixelFormat(dc, &pfd);
        // �Y������s�N�Z���t�H�[�}�b�g�������ꍇ
        if (format == 0)
            return std::nullopt; 

        // OpenGL���g���f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
        if (!SetPixelFormat(dc, format, &pfd))
            return std::nullopt;

        // OpenGL context���쐬
        HGLRC glRC = wglCreateContext(dc);

        // �쐬���ꂽ�R���e�L�X�g�����ݎg�p���̃R���e�L�X�g���ǂ���
        if (!wglMakeCurrent(dc, glRC))
            return std::nullopt;

        return std::make_pair(dc, glRC);
    }


    void shutdown(HWND hwnd, HDC hdc, HGLRC hglrc)
    {

        //�J�����g�R���e�L�X�g�𖳌��ɂ���
        wglMakeCurrent(NULL, NULL);

        //�J�����g�R���e�L�X�g���폜
        //null�ł��������̂Ń`�F�b�N���Ȃ�
        wglDeleteContext(hglrc);

        //�f�o�C�X�R���e�L�X�g���J��
        ReleaseDC(hwnd, hdc);
    }
}