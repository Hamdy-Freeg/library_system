# Library Management System

A (CLI) Library Management System developed in C++. This project is designed to manage books, users, and borrowing operations while maintaining data consistency and optimal performance.

## Project Overview

This system allows administrators to track library inventory and user borrowing histories. It moves beyond basic array manipulation by implementing efficient searching algorithms and persisting data via CSV files, ensuring that no information is lost between sessions.

## Core Features

* **Inventory & User Management:** Add new books with quantities and register users with unique IDs. The system ensures no duplicate users are created.
* **Optimized Searching:** Implements custom Binary Search and C++ `std::lower_bound` to achieve O(log N) time complexity for book prefix searching and user validation.
* **Borrowing & Returning System:** * Handles checkout and return operations logically.
  * Prevents users from borrowing the same book twice.
  * Maintains strict data consistency by mapping relationships via IDs (instead of duplicating entire objects in memory).
* **Data Persistence (File Handling):** Automatically loads existing data upon startup and saves all modifications to `data/books.csv` and `data/users.csv` upon exiting the system safely.

## Directory Structure

To ensure a clean working environment, the project separates source code, compiled binaries, and data files:

```text
library_system/
├── src/
│   └── main.cpp
├── build/
│   └── main (Executable)
├── data/
│   ├── books.csv
│   └── users.csv
└── README.md
```

## Installation & Setup

Follow these steps to clone the repository, compile the code, and run the system on your local machine.

**1. Clone the repository:**
```bash
git clone https://github.com/Hamdy-Freeg/library_system
cd library_system
```

**2. Prepare the environment:**
Ensure the `build` and `data` directories exist before compiling.
```bash
mkdir -p build data
touch data/books.csv data/users.csv
```

**3. Compile the code:**
Compile the source file using `g++` and output the executable to the `build` directory. Must be run from the root directory of the project.
```bash
g++ src/main.cpp -o build/main
```

**4. Run the system:**
```bash
./build/main
```
