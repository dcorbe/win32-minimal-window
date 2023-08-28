#include <string>
#include <windows.h>
#include <cstring>

#include "window.h"

Window::Window(HINSTANCE hInstance)
: hInstance(hInstance)
{
    this->Register();
    this->hwnd = CreateWindowEx(
            0,
            this->className.c_str(),
            this->windowTitle.c_str(),
            WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            nullptr,
            nullptr,
            this->hInstance,
            this
    );
    if (!this->hwnd)
    {
        // TODO: Handle this more gracefully.
        MessageBox(nullptr, "Failed to create main window", "Error", MB_OK);
        exit(14);
    }
}

Window::~Window()
{
    DestroyWindow(this->hwnd);
    UnregisterClass(this->className.c_str(), this->hInstance);
}

void Window::Register()
{
    WNDCLASS wc;

    // Best practice is to zero out the wc struct
    ZeroMemory(&wc, sizeof(wc));

    wc.lpfnWndProc = Window::WndProc;
    wc.hInstance = this->hInstance;
    wc.lpszClassName = this->className.c_str();
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc))
    {
        // TODO: Handle this more gracefully.
        MessageBox(nullptr, "Failed to register main window class", "Error", MB_OK);
        exit(15);
    }
}

void Window::show()
{
    ShowWindow(this->hwnd, SW_SHOW);
}

void Window::hide()
{
    ShowWindow(this->hwnd, SW_HIDE);
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window *This;

    if (msg == WM_NCCREATE)
    {
        // Extract the pointer to the MainWindow instance passed to us through lpParam
        This = static_cast<Window *>(reinterpret_cast<CREATESTRUCT *>(lParam)->lpCreateParams);

        // Store the MainWindow* passed in to CreateWindowEx
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) This);

        // Stops the user from thinking the application is frozen
        SetCursor(LoadCursor(nullptr, IDC_ARROW));
    }
    else
    {
        // Retrieve the stored MainWindow*
        This = reinterpret_cast<Window *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    // If we have a pointer, use it to handle the message.
    if (This)
    {
        if (msg == WM_DESTROY)
        {
            PostQuitMessage(0);
        }
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}
