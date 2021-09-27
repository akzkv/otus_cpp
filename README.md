# otus_cpp
Exercises and homework from OTUS C++ courses

1. Build

To build have cmake.exe installed in PATH and run corresponding .cmd files.

To build with VSCode CMake Extension set its Settings.Cmake.Generators to "MinGW Makefiles"

To build with VSCode build task (MinGW), open .cpp file and call Terminal/Run Build Task... See also .vscode/tasks.json

Cmake build actions for GitHub are configured in .github\workflows\cmake.yml 

2. Installer

.cmd files will create a CPack ZIP packages on Windows.

.github\workflows\release.yml configures GitHub Action to build sources and create CPack debian package. 
* install WSL
* download otus_cpp-0.0.6-Linux.deb somewhere to mnt/c
* sudo dpkg -i otus_cpp-0.0.6-Linux.deb
* hello