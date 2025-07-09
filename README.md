# JSON Parser (C++)

A custom JSON parser implemented in C++ for the Programmazione e Laboratorio (PEL) course.

---

## Table of Contents

* [Introduction](#introduction)
* [Features](#features)
* [JSON Data Types Supported](#json-data-types-supported)
* [Project Structure](#project-structure)
* [Building and Running](#building-and-running)
* [Usage Example](#usage-example)
* [Error Handling](#error-handling)
* [Author](#author)
* [License](#license)

---

## Introduction

This project is a custom **JSON (JavaScript Object Notation)** parser developed in C++ as part of the "Programmazione e Laboratorio" (PEL) course at Università Ca' Foscari Venezia. Its primary goal is to demonstrate a fundamental understanding of data structures, dynamic memory management, and parsing techniques in C++.

The parser provides a custom `json` class capable of representing any valid JSON data type. It can read JSON data from input streams (like files or strings) and serialize JSON objects back to output streams. The internal representation leverages dynamically allocated linked lists to manage JSON arrays and objects.

---

## Features

This custom JSON parser offers a range of functionalities for handling JSON data:

* **Custom `json` Class:** A central class (`json.hpp`) that can hold and manage different JSON data types (null, numbers, strings, booleans, lists, and dictionaries).
* **Parsing Capability:** Reads and interprets JSON formatted data from `std::istream` objects, allowing you to load JSON from files or in-memory strings.
* **Serialization:** Converts `json` objects back into their string representation and writes them to `std::ostream`.
* **Type Verification:** Provides methods like `is_null()`, `is_number()`, `is_string()`, `is_bool()`, `is_list()`, and `is_dictionary()` to check the current data type stored in a `json` object.
* **Value Accessors:** Includes getter and setter methods (`get_number()`, `set_string()`, etc.) to interact with the underlying data value based on its type.
* **List (JSON Array) Management:**
    * `push_front()` and `push_back()`: Add new `json` elements to the beginning or end of a JSON list.
    * **Iterators:** `list_iterator` and `const_list_iterator` enable traversal through the elements of a JSON list.
* **Dictionary (JSON Object) Management:**
    * `insert()`: Add new key-value pairs (`std::pair<std::string, json>`) to a JSON dictionary.
    * **`operator[]`:** Provides convenient C++-style access to dictionary values using string keys. If a key doesn't exist for a non-const object, it will be added.
    * **Iterators:** `dictionary_iterator` and `const_dictionary_iterator` allow iteration over the key-value pairs within a JSON dictionary.
* **Robust Memory Management:** Employs the **Pimpl Idiom** (`struct json::impl`) to abstract implementation details and facilitate proper resource management (constructors, destructor, and assignment operators handle memory allocation and deallocation for internal data structures).

---

## JSON Data Types Supported

The parser fully supports the core JSON data types as defined by the JSON standard:

* **Null:** Represented by the keyword `null`.
* **Number:** Double-precision floating-point numbers (e.g., `123`, `123.45`, `-6`).
* **String:** Sequences of Unicode characters enclosed in double quotes (e.g., `"hello world"`, `"with\\nescapes"`). Supports standard JSON escape sequences.
* **Boolean:** Logical values `true` or `false`.
* **List (Array):** An ordered collection of zero or more JSON values, enclosed in square brackets `[]` and separated by commas.
* **Dictionary (Object):** An unordered collection of zero or more key-value pairs, enclosed in curly braces `{}`. Keys are strings, and values are any JSON type.


---

## Building and Running

This project is written in **C++11** and can be compiled using a standard C++ compiler, such as G++.

**Prerequisites:**

* **G++ (or any C++11 compliant compiler):** Ensure you have a C++ compiler installed and accessible from your command line.

**Steps:**

1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/Vor7reX/Json-Parser.git](https://github.com/Vor7reX/Json_Parser.git)
    cd Json_Parser
    ```

    **Example modification in `src/json.cpp`:**
    ```cpp
    // In json.cpp, inside the main() function:
    // Change this:
    // std::string newFile = "  "+std::to_string(i);
    // To something like this (if your test files are in the 'examples' folder relative to your executable):
    std::string newFile = "examples/json_test" + std::to_string(i) + ".json"; // Or .txt if you prefer
    // Make sure your test files are named e.g., test1.json, test2.json, etc.
    // Or if you only have one test file:
    // std::string newFile = "examples/your_test_file.json";
    ```
    Ensure your test files (e.g., `test1.json`, `test2.json`, ..., `test100.json`) actually exist in the specified `examples/` directory.

4.  **Compile the Project:**
    Navigate to the project's root directory in your terminal:
    ```bash
    g++ -std=c++11  src/json.cpp -o json_parser
    ```
    * `-std=c++11`: Ensures the compiler uses the C++11 standard, which is required for features like `std::to_string`.
    * `-o json_parser`: Specifies the name of the output executable.

5.  **Run the Executable:**
    ```bash
    ./json_parser
    ```
    This will execute the `main` function, which attempts to parse the test files and print their content to the console.

---

## Usage Example

Here's a quick example of how you might use the `json` class in your own C++ code:

```cpp
#include "json.hpp" // Include your custom JSON header
#include <iostream>
#include <sstream> // For parsing from strings

int main() {
    // --- INSERT HERE PATH FOR FOLDER ---
    // Option A: Recommended for portability (relative path).
    // Assumes 'json_test' folder is located in the same directory as your executable,
    // or adjusted as needed if you place it within 'examples/'.
    // Example: If your executable is in 'Json-Parser/' and 'json_test' is in 'Json-Parser/examples/json_test/',
    // then the base_path might be "examples/json_test/".
    std::string base_path = "examples//json_test/"; // <-- Adjust this path if 'json_test' is nested (e.g., "examples/json_test/")

    for (int i = 1; i < 101; i++) {
        std::string newFile = base_path + std::to_string(i) + ".txt";
        
        std::cout << "\n\n"; // Added newlines for better readability in console output
        std::cout << "Opening file " << newFile << std::endl; // Displays the full path being opened
        
        std::ifstream file(newFile);
        if (!file.is_open()) {
            std::cerr << "Error: Failed to open the file: " << newFile << std::endl; // Use cerr for errors
            // If any file in the loop fails, we might want to continue to the next or exit.
            // For now, it returns 1 on first failure, stopping the whole loop.
            return 1; 
        }
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();

        json data;
        try {
            ss >> data;
            std::cout << data << std::endl;
        } catch (const json_exception& e) {
            std::cerr << "Error parsing " << newFile << ": " << e.msg << std::endl;
            return 1; // Exit on parsing error
        }
    }
    std::cout << "\n\nAll JSON files parsed successfully!" << std::endl; // More encouraging message
    return 0;
}
```

**Error Handling**
The parser implements a simple exception mechanism using the json_exception struct. This is thrown in cases of:

Type Mismatch: Attempting to retrieve a value of a type different from what the json object currently holds (e.g., calling get_number() on a JSON string).

Key Not Found: Accessing a non-existent key in a JSON dictionary using the const version of operator[].

Parsing Errors: Encountering malformed JSON syntax during input stream processing.

When an exception is thrown, it carries a std::string msg with a descriptive error message to help in debugging and understanding the cause of the failure.

**Author**
Haddaoui Hakim - Student at Università Ca' Foscari Venezia

Matricola: 892639

Progetto per il corso di Programmazione e Laboratorio (PEL)

**License**
This project is open-source and available under the MIT License. For more details, see the LICENSE file in the root of the repository.
