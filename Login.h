// Login.h

#ifndef LOGIN_H
#define LOGIN_H

#include <windows.h>

// This function will create all the necessary controls (like buttons, text fields, labels) 
// for the login form and position them on the window.
void CreateLoginControls(HWND hwnd);

// This function is called when the user clicks the "Submit" button. It checks the 
// entered username and password to see if they match predefined values, 
// and handles the login process accordingly.
void HandleLogin(HWND hwnd, WPARAM wParam);

// This function is used to handle the drawing of the window’s content, 
// such as the image or icon, whenever the window needs to be redrawn.
void HandlePaint(HWND hwnd);

// This function cleans up any resources used during the window's lifetime 
// (like images and icons) when the window is closed.
void Cleanup();

// This function creates and updates the footer at the bottom of the window, 
// which displays the copyright message.
void CreateFooter(HWND hwnd);

#endif // LOGIN_H

