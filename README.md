# LC3 Virtual Machine

This project implements a virtual machine for the LC3 (Little Computer 3) architecture, written in C. The virtual machine can load and execute LC3 machine code.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Requirements](#requirements)
- [Building](#building)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The LC3 Virtual Machine is a software-based simulation of the LC3 architecture. This project provides a platform for running LC3 machine code, supporting various LC3 operations and traps.

## Features

- Full support for LC3 instructions including arithmetic, logic, memory access, and control operations.
- Implementation of LC3 traps for input/output operations.
- Memory management and input buffering.
- Basic error handling and signal management.

## Requirements

- CMake (version 3.10 or higher)
- GCC or any compliant C compiler

## Building

To build the project, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/lc3-vm.git
    cd lc3-vm
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake to configure the build:
    ```sh
    cmake ..
    ```

4. Compile the project:
    ```sh
    make
    ```

## Usage

After building the project, you can run the LC3 virtual machine by passing LC3 object files as arguments:

```sh
./lc3 [image-file1] [image-file2] ...