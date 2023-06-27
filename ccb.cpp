#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <windows.h>

void CopyToClipboard(const std::string& text) {
    if (OpenClipboard(nullptr)) {
        EmptyClipboard();

        HGLOBAL clipboard_data = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
        if (clipboard_data != nullptr) {
            char* clipboard_text = static_cast<char*>(GlobalLock(clipboard_data));
            if (clipboard_text != nullptr) {
                std::memcpy(clipboard_text, text.c_str(), text.size() + 1);
                GlobalUnlock(clipboard_data);
                SetClipboardData(CF_TEXT, clipboard_data);
            } else {
                std::cerr << "Failed to lock clipboard memory." << std::endl;
            }
        } else {
            std::cerr << "Failed to allocate clipboard memory." << std::endl;
        }

        CloseClipboard();
    } else {
        std::cerr << "Failed to open clipboard." << std::endl;
    }
}


int main() {
    std::ifstream file("data.txt");
    if (!file.is_open()) {
    	std::cerr << "Failed to open file." << std::endl;
    	return 1;
    }


    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    int lineCount = lines.size();

    int input;
    std::cout << "Enter a number from 1 to " << lineCount << ": ";
    if (!(std::cin >> input)) {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        return 1;
    }


    std::string selectedLine = lines[input - 1];

    CopyToClipboard(selectedLine);

    std::cout << "Copied to clipboard: " << selectedLine << std::endl;

    return 0;
}
