#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: main.exe install (package name) (version)" << std::endl;
        return 1;
    }

    std::string packageName = argv[2];
    std::string version = (argc >= 4) ? argv[3] : "latest";

    std::string command = "pip install --upgrade https://github.com/ByteRise/purple-packages/" + packageName + "/" + packageName + "_" + version + ".whl";
    int result = std::system(command.c_str());

    if (result == 0) {
        std::cout << "Package installation successful!" << std::endl;
    } else {
        std::cout << "Package installation failed." << std::endl;
    }

    return 0;
}
