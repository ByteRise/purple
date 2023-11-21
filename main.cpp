#include <iostream>
#include <cstdlib>
#include <cstring>

int main(int argc, char* argv[]) {
    const char* usage = "Usage: main.exe (--command <command>) [--virtualenv <virtual_env_path>] [options]\n"
        "Commands:\n"
        "  install [--package <package_name>] [--version <version>] [--resolve]\n"
        "  uninstall [--package <package_name>]\n"
        "  list\n";

    const char* command = nullptr;
    const char* venvPath = nullptr;
    const char* packageName = nullptr;
    const char* version = nullptr;
    bool resolveConflicts = false;

    // Process command line arguments
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--command") == 0 && i + 1 < argc) {
            command = argv[++i];
        }
        else if (strcmp(argv[i], "--virtualenv") == 0 && i + 1 < argc) {
            venvPath = argv[++i];
        }
        else if (strcmp(argv[i], "--package") == 0 && i + 1 < argc) {
            packageName = argv[++i];
        }
        else if (strcmp(argv[i], "--version") == 0 && i + 1 < argc) {
            version = argv[++i];
        }
        else if (strcmp(argv[i], "--resolve") == 0) {
            resolveConflicts = true;
        }
    }

    if (!command) {
        std::cerr << "Error: Command not specified.\n" << usage;
        return 1;
    }

    if (!venvPath && strcmp(command, "list") != 0) {
        std::cerr << "Error: Virtual environment path not specified.\n" << usage;
        return 1;
    }

    if (strcmp(command, "install") == 0) {
        if (!packageName) {
            std::cerr << "Error: Package name not specified for install command.\n" << usage;
            return 1;
        }

        std::string installCommand = "source ";
        installCommand += venvPath;
        installCommand += "/bin/activate && pip install";

        if (resolveConflicts) {
            installCommand += " --use-feature=fast-deps";
        }

        installCommand += " ";
        installCommand += packageName;

        if (version) {
            installCommand += "==";
            installCommand += version;
        }

        int result = std::system(installCommand.c_str());

        if (result == 0) {
            std::cout << "Package installation successful!" << std::endl;
        }
        else {
            std::cout << "Package installation failed. Trying to install from GitHub..." << std::endl;
            installCommand = "source " + std::string(venvPath) + "/bin/activate && pip install git+https://github.com/ByteRise/purple-packages@" + packageName;
            result = std::system(installCommand.c_str());
            if (result == 0) {
                std::cout << "Package installation from GitHub successful!" << std::endl;
            }
            else {
                std::cout << "Package installation from GitHub failed. Apparently this package does not exist, check the name." << std::endl;
            }
        }
    }
    else if (strcmp(command, "uninstall") == 0) {
        if (!packageName) {
            std::cerr << "Error: Package name not specified for uninstall command.\n" << usage;
            return 1;
        }

        std::string uninstallCommand = "source ";
        uninstallCommand += venvPath;
        uninstallCommand += "/bin/activate && pip uninstall -y ";
        uninstallCommand += packageName;

        int result = std::system(uninstallCommand.c_str());

        if (result == 0) {
            std::cout << "Package uninstallation successful!" << std::endl;
        }
        else {
            std::cout << "Package uninstallation failed." << std::endl;
        }
    }
    else if (strcmp(command, "list") == 0) {
        if (venvPath) {
            std::string listCommand = "source ";
            listCommand += venvPath;
            listCommand += "/bin/activate && pip list";
            std::system(listCommand.c_str());
        }
        else {
            std::string listCommand = "pip list";
            std::system(listCommand.c_str());
        }
    }
    else {
        std::cerr << "Error: Unrecognized command: " << command << "\n" << usage;
        return 1;
    }

    return 0;
}
