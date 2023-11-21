# Package Manager README

This is a simple command-line package manager written in C++ to facilitate the installation, uninstallation, and listing of Python packages within a virtual environment. It also provides an option to resolve dependencies using the `--resolve` flag during installation.

## Usage

```
Usage: main.exe (--command <command>) [--virtualenv <virtual_env_path>] [options]

Commands:
  install [--package <package_name>] [--version <version>] [--resolve]
  uninstall [--package <package_name>]
  list
```

## Commands

### 1. Install

Installs a Python package within the specified virtual environment.

```
main.exe --command install --package <package_name> [--version <version>] [--resolve] --virtualenv <virtual_env_path>
```

- `--package <package_name>`: Specifies the name of the package to be installed.
- `--version <version>`: Optionally specifies the version of the package. If not provided, the latest version will be installed.
- `--resolve`: Optionally resolves dependencies using the `--use-feature=fast-deps` flag during installation.
- `--virtualenv <virtual_env_path>`: Specifies the path to the virtual environment where the package will be installed.

### 2. Uninstall

Uninstalls a previously installed Python package from the specified virtual environment.

```
main.exe --command uninstall --package <package_name> --virtualenv <virtual_env_path>
```

- `--package <package_name>`: Specifies the name of the package to be uninstalled.
- `--virtualenv <virtual_env_path>`: Specifies the path to the virtual environment from which the package will be uninstalled.

### 3. List

Lists all installed Python packages within the specified virtual environment.

```
main.exe --command list [--virtualenv <virtual_env_path>]
```

- `--virtualenv <virtual_env_path>`: Optionally specifies the path to the virtual environment. If not provided, the global environment's packages will be listed.

## Examples

### Install a package:

```
main.exe --command install --package requests --virtualenv path/to/venv
```

### Install a specific version of a package:

```
main.exe --command install --package numpy --version 1.19.4 --virtualenv path/to/venv
```

### Install a package with dependency resolution:

```
main.exe --command install --package pandas --resolve --virtualenv path/to/venv
```

### Uninstall a package:

```
main.exe --command uninstall --package requests --virtualenv path/to/venv
```

### List installed packages:

```
main.exe --command list --virtualenv path/to/venv
```

### List global installed packages:

```
main.exe --command list
```

## Notes

- Make sure to activate the virtual environment before running commands related to a specific environment.
- If package installation fails, the tool will attempt to install the package from GitHub as a fallback.
- For the `list` command, if no virtual environment is specified, it will list packages in the global environment.