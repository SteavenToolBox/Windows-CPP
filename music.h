#pragma once
#include <string>

namespace Music
{
    bool play(const std::string& file, bool loop = false);
    void stop();
}

std::string GetExeDirectory();