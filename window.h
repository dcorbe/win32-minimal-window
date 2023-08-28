#ifndef WINDOW_H
#define WINDOW_H

class Window
{
public:
    explicit Window(HINSTANCE hInstance);
    ~Window();
    void show();
    void hide();

private:
    HINSTANCE hInstance;
    HWND hwnd;
    const std::string className = "MinimalExample";
    const std::string windowTitle = "Minimum Example";

    void Register();
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif  /* WINDOW_H */
