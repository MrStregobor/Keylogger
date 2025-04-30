**Cpp Keylogger** is a lightweight, stealth-based keylogging application written in C++. Designed strictly for educational purposes,
this tool demonstrates how keyboard input can be captured and logged locally, with optional backup to a remote server over a secure LAN or VPN.
Features

    🔐 Logs all keyboard input to a local file in the same directory.

    📁 Option to backup logs to a custom server (must be on same LAN or connected via VPN).

    💻 Fully compatible with Windows.

    🛡️ Capable of bypassing Windows Defender on most configurations.

    👻 Operates silently in the background without alerting users.

Installation

    Open PowerShell and navigate to the project directory.

    Compile the source using g++:

```shell
g++ keylogger.cpp -o keylogger

Run the executable:

    ./keylogger
```

Usage

Once executed, the keylogger will begin recording keystrokes immediately. Logs are stored in a text file in the same directory.
For remote backup, set up a lightweight server (e.g., via Python HTTP server or any custom server) on the same LAN/VPN and configure the destination within the script.
Technologies Used

    Language: C++

    Platform: Windows

    Compiler: g++ (MinGW recommended)

Compatibility

    ✅ Windows 10 and above

    Requires: g++ compiler installed and added to PATH

Disclaimer

    ⚠️ This software is for educational and ethical hacking purposes only.
    The author is not responsible for any misuse or damages caused by this tool.
    Always ensure you have proper authorization before deploying this program.

Author

MR Stregobor
GitHub: [MRStregobor](https://github.com/MrStregobor)
