# Daily-Commit-Tracker

# App Installation
**Github Access Token**
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

# Binary Installation
**libcurl**
1. Download libcurl `curl-8.10.1`
 - [Site Link](https://curl.se/windows/)
 - [Download Link](https://curl.se/windows/dl-8.10.1_1/curl-8.10.1_1-win64-mingw.zip)
2. Extract zip file
3. Open the extracted folder and drag it into this folder
4. Run `curl.exe` inside `bin\`
5. Add the bin folder to your system environment variables under path
 - `{Whatever path you need}\Daily-Commit-Tracker\curl-8.10.1_1-win64-mingw\bin`

Note: Idk what I did different here but it worked after like the 7th tile :|


Directory Should Look Like:
Daily-Commit-Tracker
 | curl-8.10.1_1 (folder)
   | bin
     | curl.exe
 | README.md


 # Extra Notes
 https://api.github.com/users/AndrewRoddy/events