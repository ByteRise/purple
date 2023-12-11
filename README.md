# Package Manager Utility

This C++ program is a simple package manager utility designed to manage Python packages within a virtual environment. It supports various commands and options to perform tasks like installing, uninstalling, generating requirements, and listing installed packages.

## Usage

```
Usage: main.exe (--command <command>) [--virtualenv <virtual_env_path>] [options]
Commands:
  install [--package <package_name>] [--version <version>] [--resolve]
  uninstall [--package <package_name>]
  gen-reqs [path to file]
  list
Options:
  --virtualenv <virtual_env_path>   Path to the virtual environment.
  --package <package_name>          Name of the package.
  --version <version>               Version of the package.
  --resolve                         Resolve conflicts.
```

## Commands and Options

- **install**: Installs a Python package. Supports specifying package name, version, and resolving conflicts.

  Example:
  ```
  main.exe --command install --package requests --version 2.26.0 --resolve
  ```

- **uninstall**: Uninstalls a Python package. Requires specifying the package name.

  Example:
  ```
  main.exe --command uninstall --package requests
  ```

- **gen-reqs**: Generates a `requirements.txt` file based on the Python source code in the specified directory.

  Example:
  ```
  main.exe --command gen-reqs [path to .py file]
  ```

- **list**: Lists installed Python packages in the virtual environment.

  Example:
  ```
  main.exe --command list
  ```

## Options

- **--virtualenv**: Specifies the path to the virtual environment.

  Example:
  ```
  main.exe --command install --package requests --virtualenv /path/to/virtualenv
  ```

- **--package**: Specifies the name of the Python package.

  Example:
  ```
  main.exe --command install --package requests
  ```

- **--version**: Specifies the version of the Python package.

  Example:
  ```
  main.exe --command install --package requests --version 2.26.0
  ```

- **--resolve**: Resolves package installation conflicts.

  Example:
  ```
  main.exe --command install --package requests --resolve
  ```

## Example Usages

1. **Install a package**:
   ```
   main.exe --command install --package requests
   ```

2. **Uninstall a package**:
   ```
   main.exe --command uninstall --package requests
   ```

3. **Generate requirements file**:
   ```
   main.exe --command gen-reqs /path/to/source/code
   ```

4. **List installed packages**:
   ```
   main.exe --command list
   ```

## Notes

- This utility assumes a virtual environment for managing Python packages.
- It can handle package installations, uninstallations, generating requirements, and listing packages.
- The `gen-reqs` command generates a `requirements.txt` file based on Python source code in the specified directory.
- It provides options for specifying virtual environment path, package name, package version, and conflict resolution during installation.

- VERY IMPORTANT NOTE!!!
- I began to change frequently readme.md so if you didn't find what you were looking for in the latest version of this readme, just go to the commits and look for past updates, there will definitely be instructions for certain commands and examples of their uses
