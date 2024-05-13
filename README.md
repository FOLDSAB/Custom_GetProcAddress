
# Custom GetProcAddress WinAPI

## Introduction
This project demonstrates a custom implementation of the `GetProcAddress` function from the Windows API. The `GetProcAddress` function retrieves the address of an exported function or variable from the specified dynamic-link library (DLL). This custom implementation allows for dynamically loading and accessing functions from a DLL without directly calling the standard `GetProcAddress` function provided by the Windows API.

## Prerequisites
To compile and use this project, you'll need:
- A Windows operating system
- A C compiler (e.g., Visual Studio, MinGW, Cygwin)

## Compilation
Follow these steps to compile the project:
1. Open a command prompt.
2. Navigate to the directory containing the source code files.
3. Run the following command to compile the source code:
    ```
    gcc source.c -o custom_getprocaddress
    ```
    Replace `gcc` with your C compiler if necessary.

## Usage
Once the project is compiled successfully, you can use it to retrieve function addresses from dynamic-link libraries.

### Syntax
```
custom_getprocaddress <DLL_Name> <Function_Name>
```

### Parameters
- `DLL_Name`: The name of the dynamic-link library (DLL) from which you want to retrieve the function address.
- `Function_Name`: The name of the function whose address you want to retrieve.

### Example
Suppose you have a DLL named `example.dll` and you want to retrieve the address of a function named `MyFunction`:
```
custom_getprocaddress example.dll MyFunction
```

## Notes
- Ensure that the specified DLL exists in the current directory or is accessible from the system's PATH.
- The function names are case-sensitive.
- If the specified function name is found in the DLL, the tool will print its ordinal and address.
- If the function name is not found, no output will be generated.


---
