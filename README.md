# Daily-Commit-Tracker
 
# Binary Installation
**libcurl**
1. Download git
2. Add curl to system enviroment variables 
 - `C:\Program Files\Git\mingw64\bin\curl.exe`
1. Download libcurl `curl-8.10.1`
 - [Site Link](https://curl.se/windows/)
 - [Download Link](https://curl.se/windows/dl-8.10.1_1/curl-8.10.1_1-win64-mingw.zip)
2. Drag the zip file into the `curl` folder
3. Extract zip file
4. Open `curl.exe`
 - curl-8.10.1_1-win64-mingw/curl-8.10.1_1-win64-mingw/bin/curl.exe`


1. Open *MSYS2 UCRT64* or `ucrt64`
2. Use `git clone https://github.com/Microsoft/vcpkg.git` 
   - (if git not found use `pacman -S git` first)
3. `cd vcpkg`

Directory Should Look Like:
Daily-Commit-Tracker
 | curl-8.10.1 (folder)
   | include
     | curl.h
 | README.md