#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <tlhelp32.h>
#include <commctrl.h>
#include <shlobj.h>

// Global variables
volatile int isActive = 1;
wchar_t originalWallpaper[MAX_PATH] = L"";
int orientationOriginal = 0;
const wchar_t* processesToMonitor[] = {L"chrome.exe", L"firefox.exe", L"msedge.exe", NULL};
const wchar_t* sites[] = {L"https://youtube.com/watch?v=dQw4w9WgXcQ", L"https://youtube.com/watch?v=oHg5SJYRHA0", 
                         L"https://www.bleepingcomputer.com/", L"https://www.howtogeek.com/", NULL};

// Function prototypes
void InitializeSimulation();
void MainEffects();
void MonitorProcesses();
void RandomSound();
void ScreenEffects();
void OpenRandomSite();
void RandomizeWindows();
void MouseJitter();
void ChangeClipboard();
void FakeErrorMessages();
void FakeSystemScan();
void OpenRickRoll();
void RotateScreen(int degrees, int duration);
void InvertColors(int duration);
void ShakeScreen(int intensity, int duration);
void CreateDesktopFiles();
void EmergencyStop();
void ToggleSimulation();
void ShowEducationMenu();
void ShowWarning();
void ShowNotification(const wchar_t* message);
void PlayStartSound();
void GetCurrentWallpaper(wchar_t* buffer, int bufferSize);
void SetWallpaper(const wchar_t* path);
int GetDisplayOrientation();
void SetDisplayOrientation(int orientation);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
DWORD WINAPI SimulationThread(LPVOID lpParam);

// Enhanced window position storage for shaking effect
typedef struct {
    HWND hWnd;
    RECT originalRect;
} WindowInfo;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize common controls
    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_PROGRESS_CLASS;
    InitCommonControlsEx(&icc);
    
    // Initialize random seed
    srand((unsigned int)time(NULL));
    
    // Create hidden window for message handling
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SimulationClass";
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, L"Failed to register window class", L"Error", MB_ICONERROR);
        return 1;
    }
    
    HWND hWnd = CreateWindow(wc.lpszClassName, L"", 0, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);
    if (!hWnd) {
        MessageBox(NULL, L"Failed to create window", L"Error", MB_ICONERROR);
        return 1;
    }
    ShowWindow(hWnd, SW_HIDE);
    
    // Register hotkeys
    if (!RegisterHotKey(hWnd, 1, MOD_CONTROL | MOD_ALT, VK_END)) {
        MessageBox(NULL, L"Failed to register Ctrl+Alt+End hotkey", L"Warning", MB_ICONWARNING);
    }
    if (!RegisterHotKey(hWnd, 2, MOD_CONTROL | MOD_ALT, 'D')) {
        MessageBox(NULL, L"Failed to register Ctrl+Alt+D hotkey", L"Warning", MB_ICONWARNING);
    }
    if (!RegisterHotKey(hWnd, 3, MOD_CONTROL | MOD_ALT, 'R')) {
        MessageBox(NULL, L"Failed to register Ctrl+Alt+R hotkey", L"Warning", MB_ICONWARNING);
    }
    if (!RegisterHotKey(hWnd, 4, VK_F1, 0)) {
        MessageBox(NULL, L"Failed to register F1 hotkey", L"Warning", MB_ICONWARNING);
    }
    
    // Start simulation in separate thread
    HANDLE hThread = CreateThread(NULL, 0, SimulationThread, NULL, 0, NULL);
    if (!hThread) {
        MessageBox(NULL, L"Failed to create simulation thread", L"Error", MB_ICONERROR);
        return 1;
    }
    CloseHandle(hThread);
    
    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}

DWORD WINAPI SimulationThread(LPVOID lpParam) {
    InitializeSimulation();
    
    // Main simulation loop
    while (1) {
        if (isActive) {
            MainEffects();
            MonitorProcesses();
            ScreenEffects();
        }
        Sleep(10000 + (rand() % 5000)); // Random sleep between 10-15 seconds
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_HOTKEY:
            switch (wParam) {
                case 1: EmergencyStop(); break;     // Ctrl+Alt+End
                case 2: ToggleSimulation(); break;  // Ctrl+Alt+D
                case 3: ExitProcess(0); break;      // Ctrl+Alt+R (reload)
                case 4: ShowEducationMenu(); break; // F1
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

void InitializeSimulation() {
    // Save original settings
    GetCurrentWallpaper(originalWallpaper, MAX_PATH);
    orientationOriginal = GetDisplayOrientation();
    
    // Show warning
    ShowWarning();
    
    // Initial effects
    PlayStartSound();
    CreateDesktopFiles();
    ShowNotification(L"Virus simulation started! Press F1 for help");
}

void MainEffects() {
    int effect = rand() % 7 + 1;
    switch (effect) {
        case 1: OpenRandomSite(); break;
        case 2: RandomizeWindows(); break;
        case 3: MouseJitter(); break;
        case 4: ChangeClipboard(); break;
        case 5: FakeErrorMessages(); break;
        case 6: FakeSystemScan(); break;
        case 7: OpenRickRoll(); break;
    }
    
    // Random sound every few iterations
    if (rand() % 3 == 0) {
        RandomSound();
    }
}

void MonitorProcesses() {
    for (int i = 0; processesToMonitor[i] != NULL; i++) {
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE) return;
        
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);
        
        BOOL processFound = FALSE;
        if (Process32First(hSnapshot, &pe)) {
            do {
                if (wcsicmp(pe.szExeFile, processesToMonitor[i]) == 0) {
                    processFound = TRUE;
                    break;
                }
            } while (Process32Next(hSnapshot, &pe));
        }
        
        CloseHandle(hSnapshot);
        
        if (!processFound) {
            ShellExecute(NULL, L"open", processesToMonitor[i], NULL, NULL, SW_SHOW);
            
            wchar_t message[256];
            swprintf_s(message, 256, L"Restarted %s for your safety!", processesToMonitor[i]);
            ShowNotification(message);
        }
    }
}

void RandomSound() {
    int freq = 500 + rand() % 1501; // 500-2000 Hz
    int duration = 100 + rand() % 401; // 100-500 ms
    Beep(freq, duration);
}

void ScreenEffects() {
    int effect = rand() % 3 + 1;
    switch (effect) {
        case 1: RotateScreen(180, 5000); break;
        case 2: InvertColors(3000); break;
        case 3: ShakeScreen(5, 1000); break;
    }
}

void OpenRandomSite() {
    int count = 0;
    while (sites[count] != NULL) count++;
    
    int index = rand() % count;
    ShellExecute(NULL, L"open", sites[index], NULL, NULL, SW_SHOW);
}

void RandomizeWindows() {
    HWND hWnd = GetTopWindow(NULL);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    
    while (hWnd) {
        if (IsWindowVisible(hWnd) && !IsIconic(hWnd)) {
            int newX = rand() % (screenWidth + 200) - 100;
            int newY = rand() % (screenHeight + 200) - 100;
            int newW = 300 + rand() % (screenWidth - 300);
            int newH = 200 + rand() % (screenHeight - 200);
            
            SetWindowPos(hWnd, NULL, newX, newY, newW, newH, SWP_NOZORDER);
        }
        hWnd = GetNextWindow(hWnd, GW_HWNDNEXT);
    }
}

void MouseJitter() {
    POINT pt;
    GetCursorPos(&pt);
    
    int xOffset = rand() % 201 - 100; // -100 to +100
    int yOffset = rand() % 201 - 100; // -100 to +100
    
    SetCursorPos(pt.x + xOffset, pt.y + yOffset);
}

void ChangeClipboard() {
    if (OpenClipboard(NULL)) {
        EmptyClipboard();
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, 64 * sizeof(wchar_t));
        if (hMem) {
            wchar_t* text = (wchar_t*)GlobalLock(hMem);
            if (text) {
                wcscpy_s(text, 64, L"!!! WARNING: System compromised! (Educational Simulation) !!!");
                GlobalUnlock(hMem);
                SetClipboardData(CF_UNICODETEXT, hMem);
            }
        }
        CloseClipboard();
        Sleep(2000);
    }
}

void FakeErrorMessages() {
    const wchar_t* errors[] = {
        L"Critical System Error: 0x80070005",
        L"Memory Access Violation at 0x7FF89876",
        L"Security Threat Detected: Trojan:Script/Wacatac.B!ml",
        L"Your files are being encrypted! (Simulation)",
        L"System32 files corrupted! Restart required",
        NULL
    };
    
    int count = 0;
    while (errors[count] != NULL) count++;
    
    int index = rand() % count;
    MessageBox(NULL, errors[index], L"SYSTEM ALERT", MB_ICONERROR | MB_OK);
}

void FakeSystemScan() {
    // Create progress window
    HWND hwndProgress = CreateWindowEx(0, PROGRESS_CLASS, L"System Scan", 
        WS_POPUP | WS_VISIBLE | PBS_SMOOTH, 100, 100, 300, 50, 
        NULL, NULL, GetModuleHandle(NULL), NULL);
    
    if (hwndProgress) {
        SendMessage(hwndProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
        SendMessage(hwndProgress, PBM_SETSTEP, 1, 0);
        
        for (int i = 0; i <= 100; i++) {
            SendMessage(hwndProgress, PBM_SETPOS, i, 0);
            Sleep(20);
        }
        
        DestroyWindow(hwndProgress);
        ShowNotification(L"Scan complete! 127 threats found (Simulation)");
    }
}

void OpenRickRoll() {
    ShellExecute(NULL, L"open", L"https://youtube.com/watch?v=dQw4w9WgXcQ", NULL, NULL, SW_SHOW);
}

void RotateScreen(int degrees, int duration) {
    int current = GetDisplayOrientation();
    SetDisplayOrientation(degrees);
    Sleep(duration);
    SetDisplayOrientation(current);
}

void InvertColors(int duration) {
    HDC hdc = GetDC(NULL);
    if (hdc) {
        StretchBlt(hdc, 0, 0, 0, 0, hdc, 0, 0, 0, 0, NOTSRCCOPY);
        Sleep(duration);
        ReleaseDC(NULL, hdc);
    }
}

void ShakeScreen(int intensity, int duration) {
    // Count windows
    int windowCount = 0;
    HWND hWnd = GetTopWindow(NULL);
    while (hWnd) {
        if (IsWindowVisible(hWnd)) windowCount++;
        hWnd = GetNextWindow(hWnd, GW_HWNDNEXT);
    }
    
    if (windowCount == 0) return;
    
    // Allocate storage for window positions
    WindowInfo* windows = (WindowInfo*)malloc(windowCount * sizeof(WindowInfo));
    if (!windows) return;
    
    // Store original positions
    hWnd = GetTopWindow(NULL);
    int idx = 0;
    while (hWnd && idx < windowCount) {
        if (IsWindowVisible(hWnd)) {
            windows[idx].hWnd = hWnd;
            GetWindowRect(hWnd, &windows[idx].originalRect);
            idx++;
        }
        hWnd = GetNextWindow(hWnd, GW_HWNDNEXT);
    }
    
    // Shake effect
    DWORD startTime = GetTickCount();
    while (GetTickCount() - startTime < duration) {
        int xOffset = rand() % (intensity * 2 + 1) - intensity;
        int yOffset = rand() % (intensity * 2 + 1) - intensity;
        
        for (int i = 0; i < windowCount; i++) {
            SetWindowPos(windows[i].hWnd, NULL, 
                windows[i].originalRect.left + xOffset,
                windows[i].originalRect.top + yOffset,
                0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }
        Sleep(50);
    }
    
    // Restore original positions
    for (int i = 0; i < windowCount; i++) {
        SetWindowPos(windows[i].hWnd, NULL, 
            windows[i].originalRect.left,
            windows[i].originalRect.top,
            0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }
    
    free(windows);
}

void CreateDesktopFiles() {
    wchar_t desktopPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_CURRENT, desktopPath))) {
        for (int i = 1; i <= 5; i++) {
            wchar_t filePath[MAX_PATH];
            swprintf_s(filePath, MAX_PATH, L"%s\\Warning_%d.txt", desktopPath, i);
            
            FILE* file;
            if (_wfopen_s(&file, filePath, L"w") == 0 && file) {
                fwprintf(file, L"This is a harmless text file for educational purposes.\n");
                fwprintf(file, L"Delete me anytime!\n");
                fwprintf(file, L"Simulation ID: %lld\n", (long long)time(NULL));
                fclose(file);
            }
        }
    }
}

void EmergencyStop() {
    isActive = 0;
    
    // Restore original settings
    SetWallpaper(originalWallpaper);
    SetDisplayOrientation(orientationOriginal);
    
    // Cleanup desktop files
    wchar_t desktopPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_CURRENT, desktopPath))) {
        for (int i = 1; i <= 5; i++) {
            wchar_t filePath[MAX_PATH];
            swprintf_s(filePath, MAX_PATH, L"%s\\Warning_%d.txt", desktopPath, i);
            DeleteFile(filePath);
        }
    }
    
    ShowNotification(L"Simulation stopped! All effects disabled");
    ExitProcess(0);
}

void ToggleSimulation() {
    isActive = !isActive;
    ShowNotification(isActive ? L"Simulation RESUMED" : L"Simulation PAUSED");
}

void ShowEducationMenu() {
    MessageBox(NULL, 
        L"ADVANCED VIRUS SIMULATION (EDUCATIONAL)\n\n"
        L"Features:\n"
        L"- Safe browser redirection\n"
        L"- Window randomization\n"
        L"- Mouse movement simulation\n"
        L"- Fake system alerts\n"
        L"- Temporary screen effects\n"
        L"- Simulated 'threat detection'\n\n"
        L"Safety Measures:\n"
        L"- Press Ctrl+Alt+End to STOP immediately\n"
        L"- Press Ctrl+Alt+D to pause/resume\n"
        L"- All effects are temporary\n"
        L"- Restarting PC removes all effects\n\n"
        L"Educational Purpose:\n"
        L"This demonstrates common malware techniques:\n"
        L"1. Social engineering (fake warnings)\n"
        L"2. System disruption (screen effects)\n"
        L"3. Persistence (process monitoring)\n"
        L"4. Browser manipulation\n\n"
        L"Real malware can:\n"
        L"- Encrypt your files\n"
        L"- Steal passwords\n"
        L"- Install backdoors\n\n"
        L"Protection Tips:\n"
        L"- Use reputable antivirus\n"
        L"- Keep systems updated\n"
        L"- Backup important data\n"
        L"- Don't open suspicious attachments\n\n"
        L"YouTube Content Ideas:\n"
        L"1. Show simulation effects\n"
        L"2. Explain malware techniques\n"
        L"3. Demonstrate proper removal\n"
        L"4. Compare to real malware",
        L"Cybersecurity Education", MB_OK | MB_ICONINFORMATION);
}

void ShowWarning() {
    MessageBox(NULL, 
        L"WARNING: ADVANCED VIRUS SIMULATION ACTIVATED!\n\n"
        L"This is a safe educational demonstration showing\n"
        L"how real malware behaves. Your system will experience:\n"
        L"- Browser windows opening\n"
        L"- Screen effects\n"
        L"- Fake warnings\n"
        L"- Mouse movement\n\n"
        L"Press Ctrl+Alt+End to STOP immediately\n"
        L"Press F1 for educational information\n\n"
        L"This simulation is TEMPORARY and NON-DESTRUCTIVE.\n"
        L"All effects will stop after system restart.",
        L"EDUCATIONAL SIMULATION", MB_OK | MB_ICONWARNING);
}

void ShowNotification(const wchar_t* message) {
    NOTIFYICONDATA nid = { sizeof(nid) };
    nid.hWnd = FindWindow(L"SimulationClass", NULL);
    nid.uID = 1;
    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO;
    wcsncpy_s(nid.szInfoTitle, L"SIMULATION NOTICE", _TRUNCATE);
    wcsncpy_s(nid.szInfo, message, _TRUNCATE);
    
    Shell_NotifyIcon(NIM_ADD, &nid);
    Sleep(5000);
    Shell_NotifyIcon(NIM_DELETE, &nid);
}

void PlayStartSound() {
    MessageBeep(MB_ICONEXCLAMATION);
}

void GetCurrentWallpaper(wchar_t* buffer, int bufferSize) {
    SystemParametersInfo(SPI_GETDESKWALLPAPER, bufferSize, buffer, 0);
}

void SetWallpaper(const wchar_t* path) {
    SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)path, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}

int GetDisplayOrientation() {
    DEVMODE dm = {0};
    dm.dmSize = sizeof(DEVMODE);
    if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
        return dm.dmDisplayOrientation;
    }
    return 0;
}

void SetDisplayOrientation(int orientation) {
    DEVMODE dm = {0};
    dm.dmSize = sizeof(DEVMODE);
    dm.dmFields = DM_DISPLAYORIENTATION;
    dm.dmDisplayOrientation = orientation;
    ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
}
