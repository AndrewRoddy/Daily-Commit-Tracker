# Daily-Commit-Tracker

## TODO
1. Create anything in the taskbar tray
2. Implement taskbar changes to code
3. Create method to type in or change information on first startup
4. Create GUI element that runs on first open or when green square is pressed
5. Add Minecraft Integration / Kahn Academy Integration / Quizlet maybe
6. Link Patreon subscription status to product
7. Add texture changes available for subscribers (icon color / style)

*Anytime*
 - Optimize Json getting order (make recent commits more favorable)
 - Add a commit "streak" feature
 - 4+ Allow option to show number of days in a row you commited in the bottom right
 - Delete old .json files on checking
 - Stop checking for commits if day is the same and commited today

## App Installation
###### **Github Access Token**
If you want to count commits for private repositories use this method
1. Go to [Github Developer Settings](https://github.com/settings/tokens)
2. Click `Generate new token (classic)`
3. Name the token
4. Set the expiration to any time. 
 - Longer experiration: less hassle
 - Shorter expiration: more secure
5. Under select scopes check [X]`repo:status`
7. Generate Token
8. Place your token in the "TOKEN.env" file

###### **libcurl**
1. Download libcurl `curl-8.10.1`
 - [Site Link](https://curl.se/windows/)
 - [Download Link](https://curl.se/windows/dl-8.10.1_1/curl-8.10.1_1-win64-mingw.zip)
2. Extract zip file
3. Open the extracted folder and drag it into this folder
4. Run `curl.exe` inside `bin\`
5. Add the bin folder to your system environment variables under path
 - `{Whatever path you need}\Daily-Commit-Tracker\bin\curl-8.10.1_1-win64-mingw\bin`
6. Make a `cacert.pem` file and place it in the `Daily-Commit-Tracker` folder

Daily-Commit-Tracker
| lib
| | curl-8.10.1_1 (folder)
| | | bin
|README.md

*If you want to change directory make sure you update the environment variables and the .vscode/tasks.json*

## Binary Installation / Instructions
###### **nlohmann**
1. Download `nlohmann\json.hpp`
 - [Site Link](https://github.com/nlohmann/json/releases)
 - [Download Link](https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp)
2. Place it in the nlohmann folder

###### **wxWidgets**
1. Download source code
  - [Website](https://www.wxwidgets.org/downloads/)
  - [Direct](https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.6/wxWidgets-3.2.6.zip)
2. Extract .zip file