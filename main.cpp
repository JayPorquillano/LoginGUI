#include <windows.h>
#include "Login.h"  // Include the header file for login functionality

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char className[] = "LoginWindowClass";

    // Setting up the window class with necessary properties.
    // This is essentially telling Windows how the window will behave.
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProcedure;  // Link to the function that will handle the messages
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // Background color for the window

    // Register the window class. If it fails, show an error message and exit.
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Define the window size as 600x350 so the login form fits comfortably.
    int windowWidth = 600;
    int windowHeight = 350;

    // Create the window, set it to be fixed-size (not resizable or maximizable).
    HWND hwnd = CreateWindowEx(
        0, className, "Login Panel", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
        NULL, NULL, hInstance, NULL
    );

    // If the window creation fails, show an error and exit.
    if (!hwnd) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Get the dimensions of the screen (work area without taskbar)
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

    // Calculate the coordinates to center the window on the screen
    int screenWidth = rect.right;
    int screenHeight = rect.bottom;
    int posX = (screenWidth - windowWidth) / 2;
    int posY = (screenHeight - windowHeight) / 2;

    // Set the window position so that it appears centered on the screen
    SetWindowPos(hwnd, HWND_TOP, posX, posY, windowWidth, windowHeight, SWP_NOZORDER);

    // Set the window style to prevent resizing after creation
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX);

    // Show the window and update its content
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Enter the message loop to keep the application running
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  // Convert the message into something that can be processed
        DispatchMessage(&msg);   // Send the message to the window procedure
    }

    // Return the exit code of the application when it ends
    return msg.wParam;
}

// Window procedure is where all messages for the window are handled.
// It processes messages like clicks, resizing, and other events.
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            // When the window is created, call the function to add the login controls.
            CreateLoginControls(hwnd);
            break;

        case WM_COMMAND:
            // This handles user interactions with the login form, like button clicks.
            HandleLogin(hwnd, wParam);
            break;

        case WM_PAINT:
            // When the window needs to be redrawn, handle the painting (e.g., for images).
            HandlePaint(hwnd);
            break;

        case WM_DESTROY:
            // Clean up resources when the window is closed, then post a quit message.
            Cleanup();
            PostQuitMessage(0);
            break;

        case WM_SIZE:
            // We block the window from resizing by intercepting the resize message.
            return 0;

        default:
            // If it's a message we're not handling, pass it to the default handler.
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

