# PurplePipManager

PurplePipManager is a C++ program that manages Python virtual environments and packages. 

## Usage

`main.exe (command) [virtual_env_path] [options]`

## Commands

### Install

To install a package:

`main.exe install (virtual_env_path) (package name) (version) [-resolve]`

- `(virtual_env_path)`: The path to the virtual environment where the package will be installed.
- `(package name)`: The name of the package to install.
- `(version)`: The version of the package to install. If not specified, the latest version is installed.
- `[-resolve]`: An optional flag that, if present, enables the use of the fast dependency resolver in pip.

### Uninstall

To uninstall a package:

`main.exe uninstall (virtual_env_path) (package name)`

- `(virtual_env_path)`: The path to the virtual environment from which the package will be uninstalled.
- `(package name)`: The name of the package to uninstall.

### List

To list installed packages:

`main.exe list (virtual_env_path)`

- `(virtual_env_path)`: The path to the virtual environment whose packages will be listed.

## Building the Project

Use your preferred C++ compiler to compile the `main.cpp` file.

Please note that this program uses the system's `pip` command to manage packages, so Python and pip must be installed on your system.

## Disclaimer

This program is a demonstration and not intended for production use.
