#include "music.h"
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

namespace
{
    const char* alias = "mp3_music";
    std::string currentFile = "";
}

bool Music::play(const std::string& file, bool loop)
{
    // If same music already playing → don't restart
    if (currentFile == file)
        return true;

    // Stop previous music if different
    std::string closeCmd = "close " + std::string(alias);
    mciSendStringA(closeCmd.c_str(), NULL, 0, NULL);

    // Open new file
    std::string openCmd = "open \"" + file + "\" type mpegvideo alias " + std::string(alias);
    if (mciSendStringA(openCmd.c_str(), NULL, 0, NULL) != 0)
        return false;

    // Play (loop forever if requested)
    std::string playCmd;
    if (loop)
        playCmd = "play " + std::string(alias) + " repeat";
    else
        playCmd = "play " + std::string(alias);

    if (mciSendStringA(playCmd.c_str(), NULL, 0, NULL) != 0)
        return false;

    currentFile = file;

    return true;
}

void Music::stop()
{
    std::string stopCmd = "stop " + std::string(alias);
    mciSendStringA(stopCmd.c_str(), NULL, 0, NULL);

    std::string closeCmd = "close " + std::string(alias);
    mciSendStringA(closeCmd.c_str(), NULL, 0, NULL);

    currentFile = "";
}

std::string GetExeDirectory()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);

    std::string path = buffer;
    size_t pos = path.find_last_of("\\/");

    return path.substr(0, pos);
}