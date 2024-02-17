# MacOS WiFi Connector Cased on Qt
In some situations，WiFi may not work as expected in old MacBooks with MacOS Catalina. This app can fix this problem.

## How to build
```bash
cmake -S . -B build
cmake --build build
macdeployqt build/example.app
```