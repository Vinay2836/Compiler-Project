Build and Run Instructions
Pre-requisites:

A Linux environment (Debian-based recommended).
GCC (g++) compiler.
Basic C++ libraries.
Build Instructions: Run the following commands in the project directory to build the compiler:

make clean    # Clean previous build files (optional)
make          # Compile and build the executable
Run the Compiler: To run the compiler on a source file, use the following command:

./compiler.exe <source_file>
For example:


./compiler.exe tests/correct/iterativeFib.src
Output: The compiler will generate a file named output.cpp containing the equivalent C++ code for the given source program. If there are any errors, they will be displayed on the console.
