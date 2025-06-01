// PaperPlease_final.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "PaperPlease_final.h"
#include "DoubleBufferManager.h"
#include "FrameRateManager.h"
#include "StaticRenderCheckPoint.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "MainGameScene.h"
#include "Define.h"
#include "SoldierObj.h"
#include "CollisionManager.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define MAX_LOADSTRING 100
using namespace Gdiplus;
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
ULONG_PTR gdiplusToken;
DoubleBufferManager backBuffer;//더블버퍼링(백버퍼)
HWND g_hWnd = nullptr;//핸들의 또다른이름이됨..
FrameRateManager frameManager;
// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    GdiplusStartupInput gdiInput;
    GdiplusStartup(&gdiplusToken, &gdiInput, nullptr);
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PAPERPLEASEFINAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAPERPLEASEFINAL));
    //여기서 씬매니저 이니셜라이즈로 초기시작화면셋팅
    auto& SceneMgr = SceneManager::GetInstance();
    auto& renMgr = RenderManager::GetInstance();
    MSG msg;
    msg.message = WM_NULL;
    frameManager.Init(144);

    // Main message loop:
    while (true)
    {
        frameManager.BeginFrame();
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                goto ExitLoop;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        backBuffer.Clear(Color(255, 0, 0, 0));
        RECT clientRect;

        GetClientRect(g_hWnd, &clientRect);
        float sx = static_cast<float>(clientRect.right - clientRect.left) / RenderManager::BASE_WIDTH;
        float sy = static_cast<float>(clientRect.bottom - clientRect.top) / RenderManager::BASE_HEIGHT;
        SceneMgr.UpdateScene(frameManager.GetDeltaTime());
        SceneMgr.RenderScene();
        renMgr.RenderAll(backBuffer.GetGraphics(), sx, sy);
        renMgr.GetDynamicLayer().Clear();
        backBuffer.Present(g_hWnd);
        frameManager.EndFrame();

    }
ExitLoop:
    auto& resMgr = ResourceManager::GetInstance();
    resMgr.Clear();
    backBuffer.Release();
    GdiplusShutdown(gdiplusToken);
    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable
    RECT desiredClient = { 0, 0, 1280, 720 };
    AdjustWindowRect(&desiredClient, WS_OVERLAPPEDWINDOW, FALSE);

    int winWidth = desiredClient.right - desiredClient.left;
    int winHeight = desiredClient.bottom - desiredClient.top;
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, winWidth, winHeight, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    g_hWnd = hWnd;
    backBuffer.Initialize(g_hWnd);
    auto& resMgr = ResourceManager::GetInstance();
    CollisionManager::GetInstance().SetWindowsClient(g_hWnd);
    resMgr.InitImgJson();
    resMgr.PreloadingImageJson("images");
    SceneManager::GetInstance().RegisterScene(SceneType::MAINGAME, std::make_shared<MainGameScene>());
    SceneManager::GetInstance().ChangeScene(SceneType::MAINGAME);
    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
