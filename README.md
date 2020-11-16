# Basic-Stats-Analyzer-and-Exporter-in-CPP
A simple terminal ui that allows a user to select from options to store and export data with some basic analyses computed.

The user can enter a series of integers with a dynamic limit. The user will be prompted to provide the number of integers to add and the values can either be stored in a vector or a pointer. A file path can be set for file output so that the values can be saved after entry. Upon entering the values; the min, max, range, mean, median, and mode for the series will be calculated and displayed, this will also be outputted in the file. Note: The file path should be set before entering the integers or the data won't be saved.

## Compiling / Running
The project can be built using your compiler and IDE of choice. I developed it in VS Code on MacOS 11.0 using the clang compiler with the C++ extension.
(Reference: [Configure VS Code for Clang/LLVM on macOS](https://code.visualstudio.com/docs/cpp/config-clang-mac))