#include <iostream>
#include <cstdlib>
#include <string>
#include "steaventoolbox.h"

void displayMenu(const std::string& menu) {
    std::system("cls");
    std::system("color b");
    std::cout << menu;
}

void installFullRuntime() {
    std::system("choco install vcredist2005 vcredist2008 vcredist2010 vcredist2012 msvisualcplusplus2012-redist vcredist2013 vcredist2017 vcredist140 vcredist-all adoptopenjdk8openj9jre adoptopenjdk11openj9jre directx netfx-4.8.1 -y");
    std::system("DISM /Online /Enable-Feature /FeatureName:NetFx3");
    std::system("dism /Online /enable-feature /FeatureName:\"LegacyComponents\" /All");
    std::system("dism /Online /enable-feature /FeatureName:\"DirectPlay\" /All");
}

void installBrowsers() {
    clearScreen();
    std::system("color b");
    std::string choice;
    std::cout << "1. Firefox\n"
        << "2. Chrome\n"
        << "3. Brave\n"
        << "4. Ungoogled Chromium\n"
        << "5. Edge\n"
        << "6. Thorium\n"
        << "0. Go Back\n"
        << "Type the number: ";
    std::getline(std::cin, choice);

    switch (std::stoi(choice)) {
    case 1: std::system("winget install -e --id Mozilla.Firefox"); system("pause"); installBrowsers(); break;
    case 2: std::system("winget install -e --id Google.Chrome"); system("pause"); installBrowsers(); break;
    case 3: std::system("winget install -e --id BraveSoftware.BraveBrowser"); system("pause"); installBrowsers(); break;
    case 4: std::system("winget install -e --id eloston.ungoogled-chromium"); system("pause"); installBrowsers(); break;
    case 5: std::system("winget install -e --id Microsoft.Edge"); system("pause"); installBrowsers(); break;
    case 6: std::system("winget install -e --id EDRLab.Thorium"); system("pause"); installBrowsers(); break;
    case 0: return;
    default: std::cout << "Invalid choice, try again\n"; system("pause"); installBrowsers(); break;
    }
}

void installZipPrograms() {
    clearScreen();
    std::system("color b");
    std::string choice;
    std::cout << "1. NanaZip\n"
        << "2. 7-Zip\n"
        << "3. WinRAR\n"
        << "0. Go Back\n"
        << "Type the number: ";
    std::getline(std::cin, choice);

    switch (std::stoi(choice)) {
    case 1: std::system("winget install -e --id M2Team.NanaZip"); system("pause"); installZipPrograms(); break;
    case 2: std::system("winget install -e --id 7zip.7zip"); system("pause"); installZipPrograms(); break;
    case 3: std::system("winget install -e --id RARLab.WinRAR"); system("pause"); installZipPrograms(); break;
    case 0: return;
    default: std::cout << "Invalid choice, try again\n"; system("pause"); installZipPrograms(); break;
    }
}

void installMediaPrograms() {
    clearScreen();
    std::system("color b");
    std::string choice;
    std::cout << "1. VLC\n"
        << "2. MPV\n"
        << "3. Audacious\n"
        << "4. K-Lite Codec Pack Mega\n"
        << "0. Go Back\n"
        << "Type the number: ";
    std::getline(std::cin, choice);

    switch (std::stoi(choice)) {
    case 1: std::system("winget install -e --id VideoLAN.VLC"); system("pause"); installMediaPrograms(); break;
    case 2: std::system("choco install mpv.install -y"); system("pause"); installMediaPrograms(); break;
    case 3: std::system("winget install -e --id Audacious.MediaPlayer"); system("pause"); installMediaPrograms(); break;
    case 4: std::system("winget install -e --id CodecGuide.K-LiteCodecPack.Mega"); system("pause"); installMediaPrograms(); break;
    case 0: return;
    default: std::cout << "Invalid choice, try again\n"; system("pause"); installMediaPrograms(); break;
    }
}


void installChatPrograms() {
    clearScreen();
    std::system("color b");
    std::string choice;
    std::cout << "1. Discord\n"
        << "2. Element\n"
        << "3. Telegram Desktop\n"
        << "4. Whatsapp\n"
        << "0. Go Back\n"
        << "Type the number: ";
    std::getline(std::cin, choice);

    switch (std::stoi(choice)) {
    case 1: std::system("winget install -e --id Discord.Discord"); system("pause"); installChatPrograms(); break;
    case 2: std::system("winget install -e --id Element.Element"); system("pause"); installChatPrograms(); break;
    case 3: std::system("winget install -e --id Telegram.TelegramDesktop"); system("pause"); installChatPrograms(); break;
    case 4: std::system("winget install -e --id 9NKSQGP7F2NH"); system("pause"); installChatPrograms(); break;
    case 0: return;
    default: std::cout << "Invalid choice, try again\n"; system("pause"); installChatPrograms(); break;
    }
}


void installGames() {
    clearScreen();
    std::system("color b");
    std::string choice;
    std::cout << "1. Steam\n"
              << "2. Epic Games Launcher\n"
              << "3. Heroic Games Launcher\n"
              << "4. Ubisoft Connect\n"
              << "5. EA Desktop\n"
              << "6. Parsec\n"
              << "7. Moonlight\n"
              << "8. Sunshine\n"
              << "9. Minecraft Launcher\n"
              << "10. Prism Launcher\n"
              << "11. LabyMod Launcher\n"
              << "12. DuckStation\n"
              << "13. PCSX2\n"
              << "14. RPCS3\n"
              << "15. Dolphin\n"
              << "16. Cemu\n"
              << "17. Ryujinx\n"
              << "18. RetroArch\n"
              << "19. EmulationStation\n"
              << "0. Go Back\n"
              << "Type the number: ";
    std::getline(std::cin, choice);

    switch (std::stoi(choice)) {
        case 1: std::system("winget install -e --id Valve.Steam"); system("pause"); installGames(); break;
        case 2: std::system("winget install -e --id EpicGames.EpicGamesLauncher"); system("pause"); installGames(); break;
        case 3: std::system("winget install -e --id HeroicGamesLauncher.HeroicGamesLauncher"); system("pause"); installGames(); break;
        case 4: std::system("winget install -e --id Ubisoft.Connect"); system("pause"); installGames(); break;
        case 5: std::system("winget install -e --id ElectronicArts.EADesktop"); system("pause"); installGames(); break;
        case 6: std::system("winget install -e --id Parsec.Parsec"); system("pause"); installGames(); break;
        case 7: std::system("winget install -e --id MoonlightGameStreamingProject.Moonlight"); system("pause"); installGames(); break;
        case 8: std::system("winget install -e --id LizardByte.Sunshine"); system("pause"); installGames(); break;
        case 9: std::system("winget install -e --id Mojang.MinecraftLauncher"); system("pause"); installGames(); break;
        case 10: std::system("winget install -e --id PrismLauncher.PrismLauncher"); system("pause"); installGames(); break;
        case 11: std::system("winget install -e --id LabyMediaGmbH.LabyModLauncher"); system("pause"); installGames(); break;
        case 12: std::system("winget install -e --id stenzek.DuckStation"); system("pause"); installGames(); break;
        case 13: std::system("choco install pcsx2 -y"); system("pause"); installGames(); break;
        case 14: std::system("choco install rpcs3 --pre -y"); system("pause"); installGames(); break;
        case 15: std::system("choco install dolphin --pre -y"); system("pause"); installGames(); break;
        case 16: std::system("choco install cemu -y"); system("pause"); installGames(); break;
        case 17: std::system("choco install ryujinx -y"); system("pause"); installGames(); break;
        case 18: std::system("choco install retroarch -y"); system("pause"); installGames(); break;
        case 19: std::system("choco install emulationstation.install -y"); system("pause"); installGames(); break;
        case 0: return;
        default: std::cout << "Invalid choice, try again\n"; system("pause"); installGames(); break;
    }
}


void InstallPrograms() {
    std::string choice;
    while (true) {
        displayMenu("---------------------------------------------------------------------------------------------------------------------\n"
                    "1. Full Runtime\n"
                    "2. Web Browsers\n"
                    "3. Zip Programs\n"
                    "4. Media Programs\n"
                    "5. Chat Programs\n"
                    "6. Games\n"
                    "7. Install Windows Subsystem for Linux\n"
                    "8. Resource Hacker\n"
                    "9. Process Hacker\n"
                    "10. Kde Connect\n"
                    "11. Nilesoft Shell\n"
                    "12. Windows Terminal\n"
                    "13. Starship\n"
                    "14. yt-dlp\n"
                    "15. WingetUi\n"
                    "16. Intel Support Assistant\n"
                    "17. Hp Smart\n"
                    "18. NextCloud Desktop\n"
                    "19. OBS Studio\n"
                    "20. Kdenlive\n"
                    "21. GIMP (Stable)\n"
                    "22. GIMP (Nightly)\n"
                    "23. Krita\n"
                    "24. Visual Studio 2022 Community\n"
                    "25. Visual Studio Code\n"
                    "26. Github Desktop\n"
                    "27. Ubuntu 22.04 Wsl\n"
                    "28. Martinrotter RSSGuard\n"
                    "0. Go back\n"
                    "---------------------------------------------------------------------------------------------------------------------\n"
                    "Type the number: ");

        std::getline(std::cin, choice);
        if (choice == "0") break;

        switch (std::stoi(choice)) {
            case 1: installFullRuntime(); break;
            case 2: installBrowsers(); break;
            case 3: installZipPrograms(); break;
            case 4: installMediaPrograms(); break;
            case 5: installChatPrograms(); break;
            case 6: installGames(); break;
            case 7: std::system("wsl --install"); system("pause"); break;
            case 8: std::system("winget install --id=AngusJohnson.ResourceHacker -e"); system("pause"); break;
            case 9: std::system("choco install processhacker -y"); system("pause"); break;
            case 10: std::system("winget install -e --id 9N93MRMSXBF0"); system("pause"); break;
            case 11: std::system("winget install -e --id Nilesoft.Shell"); system("pause"); break;
            case 12: std::system("winget install -e --id Microsoft.WindowsTerminal"); system("pause"); break;
            case 13: std::system("winget install -e --id Starship.Starship"); system("pause"); break;
            case 14: std::system("winget install -e --id yt-dlp.yt-dlp"); system("pause"); break;
            case 15: std::system("winget install -e --id SomePythonThings.WingetUIStore"); system("pause"); break;
            case 16: std::system("winget install -e --id Intel.IntelDriverAndSupportAssistant"); system("pause"); break;
            case 17: std::system("winget install -e --id 9WZDNCRFHWLH"); system("pause"); break;
            case 18: std::system("winget install -e --id Nextcloud.NextcloudDesktop"); system("pause"); break;
            case 19: std::system("winget install -e --id OBSProject.OBSStudio"); system("pause"); break;
            case 20: std::system("winget install -e --id KDE.Kdenlive"); system("pause"); break;
            case 21: std::system("winget install -e --id GIMP.GIMP"); system("pause"); break;
            case 22: std::system("winget install -e --id GIMP.GIMP.Nightly"); system("pause"); break;
            case 23: std::system("winget install -e --id KDE.Krita"); system("pause"); break;
            case 24: std::system("winget install -e --id Microsoft.VisualStudio.2022.Community"); system("pause"); break;
            case 25: std::system("winget install -e --id Microsoft.VisualStudioCode"); system("pause"); break;
            case 26: std::system("winget install -e --id GitHub.GitHubDesktop"); system("pause"); break;
            case 27: std::system("winget install -e --id Canonical.Ubuntu.2204"); system("pause"); break;
            case 28: std::system("winget install -e --id martinrotter.RSSGuard"); system("pause"); break;
            default: std::cout << "Invalid choice, try again\n"; system("pause"); break;
        }
    }
}
