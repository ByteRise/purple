#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: main.exe (command) [virtual_env_path] [options]" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    std::string venvPath = argv[2];

    if (command == "install") {
        if (argc < 5) {
            std::cout << "Usage: main.exe install (virtual_env_path) (package name) (version) [-resolve]" << std::endl;
            return 1;
        }

        std::string packageName = argv[3];
        std::string version = (argc >= 6) ? argv[4] : "latest";
        bool resolveConflicts = (argc >= 7) ? (std::string(argv[5]) == "-resolve") : false;

        std::string installCommand = "source " + venvPath + "/bin/activate && pip install ";
        if (resolveConflicts) {
            installCommand += "--use-feature=fast-deps ";
        }
        installCommand += packageName;
        if (version != "latest") {
            installCommand += "==" + version;
        }

        int result = std::system(installCommand.c_str());

        if (result == 0) {
            std::cout << "Package installation successful!" << std::endl;
        }
        else {
            std::cout << "Package installation failed. Trying to install from GitHub..." << std::endl;
            installCommand = "source " + venvPath + "/bin/activate && pip install git+https://github.com/ByteRise/purple-packages@" + packageName;
            result = std::system(installCommand.c_str());
            if (result == 0) {
                std::cout << "Package installation from GitHub successful!" << std::endl;
            }
            else {
                std::cout << "Package installation from GitHub failed. Apparently this package does not exist, check the name." << std::endl;
            }
        }
    }
    else if (command == "uninstall") {
        if (argc < 4) {
            std::cout << "Usage: main.exe uninstall (virtual_env_path) (package name)" << std::endl;
            return 1;
        }

        std::string packageName = argv[3];
        std::string uninstallCommand = "source " + venvPath + "/bin/activate && pip uninstall -y " + packageName;

        int result = std::system(uninstallCommand.c_str());

        if (result == 0) {
            std::cout << "Package uninstallation successful!" << std::endl;
        }
        else {
            std::cout << "Package uninstallation failed." << std::endl;
        }
    }
    else if (command == "list") {
        std::string listCommand = "source " + venvPath + "/bin/activate && pip list";
        std::system(listCommand.c_str());
    }
    else {
        std::cout << "Unrecognized command: " << command << std::endl;
    }

    return 0;
}
