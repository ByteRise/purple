#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <filesystem>
#include <regex>
#include <set>
#include <fstream>



int main(int argc, char* argv[]) {
    const char* usage = "Usage: main.exe (--command <command>) [--virtualenv <virtual_env_path>] [options]\n"
        "Commands:\n"
        "  install [--package <package_name>] [--version <version>] [--resolve]\n"
        "  uninstall [--package <package_name>]\n"
		"  gen-reqs [path to .py file]\n"
        "  list\n"
		"Options:\n"
		"  --virtualenv <virtual_env_path>   Path to the virtual environment.\n"
		"  --package <package_name>          Name of the package.\n"
		"  --version <version>                Version of the package.\n"
		"  --resolve                          Resolve conflicts.\n";
	if (argc < 2) {
		std::cerr << usage;
		return 1;
	}

    const char* command = nullptr;
    const char* venvPath = nullptr;
    const char* packageName = nullptr;
    const char* version = nullptr;
    bool resolveConflicts = false;
    const char* pythonVersion = nullptr;


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

    if (strcmp(command, "install") == 0) {
        if (!packageName) {
            std::cerr << "Error: Package name not specified for install command.\n" << usage;
            return 1;
        }

        std::string installCommand = "";
        if (venvPath) {
            installCommand += venvPath;
            installCommand += "/scripts/activate && ";
        }
        installCommand += "pip install";


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

        std::string uninstallCommand = "";
        if (venvPath) {
            uninstallCommand += venvPath;
            uninstallCommand += "/scripts/activate && ";
        }
        uninstallCommand += "pip uninstall -y ";
        uninstallCommand += packageName;

        int result = std::system(uninstallCommand.c_str());

        if (result == 0) {
            std::cout << "Package uninstallation successful!" << std::endl;
        }
        else {
            std::cout << "Package uninstallation failed." << std::endl;
        }
    }


    else if (strcmp(command, "python") == 0) {
        const char* version = argv[3];
        const char* silentinstall = argv[4];
        if (!version) {
            std::cerr << "Error: Python version not specified.\n";
            return 1;
        }

        std::string pythonVersion = version;
        std::string downloadUrl = "https://www.python.org/ftp/python/" + pythonVersion + "/python-" + pythonVersion + ".exe";

        std::string command = "powershell -c \"(New-Object System.Net.WebClient).DownloadFile('" + downloadUrl + "', 'python-" + pythonVersion + ".exe')\"";
        
        int result = std::system(command.c_str());

        if (result == 0) {
            std::cout << "Python exe file downloaded successfully!" << std::endl;
			if (silentinstall) {
				command = "python-" + pythonVersion + ".exe /quiet InstallAllUsers=0 Include_launcher=0 Shortcuts=0";
				result = std::system(command.c_str());
				if (result == 0) {
					std::cout << "Python installation successful!" << std::endl;
				}
				else {
					std::cout << "Python installation failed." << std::endl;
				}
			}
        }
        else {
            std::cout << "Python exe file download failed." << std::endl;
        }


    }

    else if (strcmp(command, "gen-reqs") == 0) {
        if (argc < 4) {
            std::cerr << "Error: Path to the source code directory not provided.\n";
            return 1;
        }

        const char* srcDirectory = argv[3];
        std::filesystem::path srcPath(srcDirectory);
        if (!std::filesystem::exists(srcPath) || !std::filesystem::is_directory(srcPath)) {
            std::cerr << "Error: The provided path is not a valid directory.\n";
            return 1;
        }

        std::regex importRegex("import (.*?)$");
        std::set<std::string> dependencies;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(srcPath)) {
            if (entry.path().extension() == ".py" || entry.path().extension() == ".pyw") {
                std::ifstream file(entry.path());
                std::string line;
                while (std::getline(file, line)) {
                    std::smatch matches;
                    if (std::regex_search(line, matches, importRegex)) {
                        for (size_t i = 1; i < matches.size(); ++i) {
                            dependencies.insert(matches[i].str());
                        }
                    }
                }
            }
        }

        std::ofstream reqFile("requirements.txt");
        for (const auto& dep : dependencies) {
            reqFile << dep << std::endl;
        }
        reqFile.close();

        std::cout << "requirements.txt has been generated successfully.\n";
    }

    else if (strcmp(command, "list") == 0) {
        if (venvPath) {
            std::string listCommand = "";
            listCommand += venvPath;
            listCommand += "/scripts/activate && pip list";
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
