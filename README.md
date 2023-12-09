# Python Package Manager (PyPM) Utility

This is a simple command-line utility for managing Python packages, providing a convenient interface for common tasks such as installing, uninstalling, and listing packages. The utility also includes additional features like specifying a virtual environment, resolving conflicts during installation, and installing Python itself.

## Usage

```plaintext
main.exe (--command <command>) [--virtualenv <virtual_env_path>] [options]

Commands:
  install [--package <package_name>] [--version <version>] [--resolve]
  uninstall [--package <package_name>]
  list
  python [--version <python_version>] [--silentinstall]
```

### Commands

- **install**: Installs a Python package. You can specify the package name, version, and whether to resolve conflicts during installation.

  Example:
  ```bash
  main.exe --command install --package requests --version 2.26.0 --resolve
  ```

- **uninstall**: Uninstalls a Python package. Specify the package name to remove.

  Example:
  ```bash
  main.exe --command uninstall --package requests
  ```

- **list**: Lists installed Python packages.

  Example:
  ```bash
  main.exe --command list
  ```

- **python**: Downloads and installs a specific version of Python. You can also perform a silent installation.

  Example:
  ```bash
  main.exe --command python --version 3.9.7 --silentinstall
  ```

### Options

- **--virtualenv**: Specifies the path to a virtual environment.

- **--package**: Specifies the name of the Python package.

- **--version**: Specifies the version of the Python package or Python itself.

- **--resolve**: Resolves conflicts during package installation.

- **(any symbol on 5th argument, for example, i chose --silentinstall)**: Performs a silent installation of Python.

## Examples

1. Install a package with version and resolve conflicts:
   ```bash
   main.exe --command install --package numpy --version 1.21.2 --resolve
   ```

2. Uninstall a package:
   ```bash
   main.exe --command uninstall --package numpy
   ```

3. List installed packages:
   ```bash
   main.exe --command list
   ```

4. Install a specific version of Python with silent installation:
   ```bash
   main.exe --command python 3.8.12 --silentinstall
   ```

Feel free to explore the various commands and options to efficiently manage your Python environment.
