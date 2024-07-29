#include <iostream>
#include <cstdlib> // For system()

void RepairWindows() {
    std::cout << "Running sfc /scannow...\n";
    int result = system("sfc /scannow");
    if (result != 0) {
        std::cerr << "Error executing sfc /scannow\n";
        return;
    }

    std::cout << "Running DISM /Online /Cleanup-Image /RestoreHealth...\n";
    result = system("DISM /Online /Cleanup-Image /RestoreHealth");
    if (result != 0) {
        std::cerr << "Error executing DISM command\n";
        return;
    }

    std::cout << "Running sfc /scannow again...\n";
    result = system("sfc /scannow");
    if (result != 0) {
        std::cerr << "Error executing sfc /scannow\n";
    }
}