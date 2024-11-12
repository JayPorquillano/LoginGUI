// Login.cpp
#include <windows.h>
#include <string.h>
#include "Login.h"  // Include the header file

// Global variables for controls
HBITMAP hImage = NULL;
HICON hIcon = NULL;
HWND hUsernameLabel, hPasswordLabel;
HWND hUsernameField, hPasswordField;
HWND hSubmitButton, hRegisterButton;
HWND hFooterLabel;  // Footer label variable

// Function to create login form controls
void CreateLoginControls(HWND hwnd) {
    // First, we try to load an image to show on the left side of the login screen. 
    // If that fails (maybe the file is missing or there's an issue), we fallback to a default icon instead.
    hImage = (HBITMAP)LoadImage(NULL, "download.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (!hImage) {
        // If the image doesn’t load, we load a default system icon as a backup.
        hIcon = LoadIcon(NULL, IDI_INFORMATION);
    }

    // Creating the Username label, which simply tells the user to enter their username.
    hUsernameLabel = CreateWindow("STATIC", "Username:", WS_VISIBLE | WS_CHILD | SS_LEFT,
                                  310, 50, 80, 20, hwnd, NULL, NULL, NULL);

    // A text field where the user will type in their username.
    hUsernameField = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  400, 50, 150, 20, hwnd, NULL, NULL, NULL);

    // The Password label, just like the username label, asks for the password.
    hPasswordLabel = CreateWindow("STATIC", "Password:", WS_VISIBLE | WS_CHILD | SS_LEFT,
                                  310, 90, 80, 20, hwnd, NULL, NULL, NULL);

    // This is the password field, where the text is masked (hidden) as the user types.
    hPasswordField = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD,
                                  400, 90, 150, 20, hwnd, NULL, NULL, NULL);

    // The Submit button, which the user clicks to attempt logging in.
    hSubmitButton = CreateWindow("BUTTON", "Submit", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                 310, 140, 100, 30, hwnd, (HMENU)1, NULL, NULL);

    // The Register button, which currently just lets the user know that registration isn’t implemented.
    hRegisterButton = CreateWindow("BUTTON", "Register", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                   450, 140, 100, 30, hwnd, (HMENU)2, NULL, NULL);

    // Creating the footer at the bottom of the window, which will display a copyright message.
    CreateFooter(hwnd);
}

// Function to create the footer
void CreateFooter(HWND hwnd) {
    // The footer shows copyright information and stays fixed at the bottom of the window.
    hFooterLabel = CreateWindow("STATIC", "© 2024 My App - All Rights Reserved", WS_VISIBLE | WS_CHILD | SS_CENTER,
                                0, 300, 600, 20, hwnd, NULL, NULL, NULL);  // It spans the entire width of the window
}

// Function to handle the login logic
void HandleLogin(HWND hwnd, WPARAM wParam) {
    switch (LOWORD(wParam)) {
        case 1: { // Submit Button
            // Here, we retrieve the username and password that the user has typed into the fields.
            // The validation is simple: if the username is "user" and the password is "pass", we log them in.
            char username[30], password[30];
            GetWindowText(hUsernameField, username, 30);
            GetWindowText(hPasswordField, password, 30);

            // If the login details are correct, we show a success message.
            // If not, we inform the user that the username or password is invalid.
            if (strcmp(username, "user") == 0 && strcmp(password, "pass") == 0) {
                MessageBox(hwnd, "Login successful!", "Success", MB_OK | MB_ICONINFORMATION);
            } else {
                MessageBox(hwnd, "Invalid username or password.", "Error", MB_OK | MB_ICONERROR);
            }
            break;
        }
        case 2: // Register Button
            // Since the registration feature isn't implemented, we show an informational message.
            MessageBox(hwnd, "Registration feature not implemented.", "Info", MB_OK | MB_ICONINFORMATION);
            break;
    }
}

// Function to handle painting the controls
void HandlePaint(HWND hwnd) {
    // This function is called when the window needs to be redrawn (for example, when it’s resized or uncovered).
    // We begin the painting process and get the device context (where we can draw).
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // If the image was successfully loaded, we draw it on the left side of the window.
    if (hImage) {
        // We create a temporary drawing area (memory device context) to handle the image.
        HDC hMemDC = CreateCompatibleDC(hdc);
        SelectObject(hMemDC, hImage);
        // Now, we copy the image onto the window's drawing area.
        BitBlt(hdc, 20, 50, 250, 200, hMemDC, 0, 0, SRCCOPY);
        // Clean up the temporary drawing area after we're done.
        DeleteDC(hMemDC);
    } else if (hIcon) {
        // If no image was loaded, we display the default icon instead.
        DrawIconEx(hdc, 20, 50, hIcon, 250, 200, 0, NULL, DI_NORMAL);
    }

    // Finally, we end the painting process to finalize everything.
    EndPaint(hwnd, &ps);
}

// Function to clean up when the window is destroyed
void Cleanup() {
    // When the window is being closed, we want to make sure that any resources we’ve loaded (like images or icons) are properly cleaned up.
    // This helps prevent memory leaks.
    if (hImage) {
        DeleteObject(hImage);  // Free up the memory used by the image.
    }
    if (hIcon) {
        DestroyIcon(hIcon);  // Clean up the icon if we used it.
    }
}

