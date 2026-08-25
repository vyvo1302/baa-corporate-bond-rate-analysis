# Baa Corporate Bond Rate Analyzer

[![C++](https://img.shields.io/badge/C%2B%2B-11%2B-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.15%2B-064F8C?logo=cmake&logoColor=white)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-lightgrey)]()

A lightweight, high-performance C++ analytical tool for historical corporate bond yield analysis. This program parses multi-decade macroeconomic yield rates of Moody's Seasoned Baa Corporate Bonds (Federal Reserve H.15 statistical release), calculates statistical benchmarks, and provides an interactive CLI engine to query yields and examine historical spread deviations.

---

## Key Features

- **Automated Data Ingestion**: Parses Federal Reserve H.15 format CSV data, handling multi-line metadata headers and extracting time-series pairs.
- **Benchmark Statistics**: Computes arithmetic mean and baseline yield metrics across the full historical dataset.
- **Interactive Query Engine**: Fast date-lookup system supporting `yyyy-mm` formatted queries.
- **Spread & Deviation Analysis**: Dynamically evaluates the difference between specific period yields and historical baselines.
- **Zero External Dependencies**: Implemented purely using the standard C++ library (`<vector>`, `<fstream>`, `<iostream>`, `<string>`).
- **Robust Error Handling**: Gracefully handles missing files, invalid input formats, unindexed dates, and EOF termination signals.

---

## Project Structure

```text
.
├── CMakeLists.txt                              # CMake build configuration
├── README.md                                   # Project documentation
├── .gitignore                                  # Git ignore rules
├── data/
│   └── H.15_Baa_Data.csv                       # Historical Federal Reserve H.15 dataset
├── docs/
│   └── Baa_Corporate_Bond_Rate_Analysis_Report.pdf # Detailed analytical report
└── src/
    └── bond_analyzer.cpp                       # Core C++ source implementation
```

---

## Dataset Overview

- **Source**: Federal Reserve Statistical Release H.15 / Moody's Analytics
- **Series**: *Moody's Yield on Seasoned Corporate Bonds – All Industries, Baa*
- **Identifier**: `H15/H15/RIMLPBAAR_N.M`
- **Unit**: Percent per year (annualized yield)
- **Time Horizon**: Monthly historical data from `1919-01` onwards

---

## Getting Started

### Prerequisites

- A modern C++ compiler supporting C++11 or later (`g++` or `clang++`).
- **CMake 3.15+**.

### Building the Project

#### Build with CMake (Standard)
```bash
cmake -B build
cmake --build build
```

#### Direct Compilation (Alternative)
```bash
g++ -std=c++11 -Wall -Wextra -Werror -O2 src/bond_analyzer.cpp -o bond_analyzer
```

---

## Usage

### Running the Analyzer

Run the compiled executable (defaults to loading `data/H.15_Baa_Data.csv`):
```bash
# When built with CMake:
./build/bond_analyzer

# When built directly with g++:
./bond_analyzer
```

You can also specify a custom dataset path:
```bash
./build/bond_analyzer path/to/custom_data.csv
```

### Interactive Query Example

```text
Enter date (yyyy-mm) or press Ctrl+D to exit: 
1919-04
The annual rate for the input date is 7.23%
The annual rate for the input date is higher than the average rate by 0.178599%

Enter date (yyyy-mm) or press Ctrl+D to exit: 
1981-09
The annual rate for the input date is 16.92%
The annual rate for the input date is higher than the average rate by 9.8686%

Enter date (yyyy-mm) or press Ctrl+D to exit: 
```

To exit the interactive prompt at any time, press **`Ctrl + D`**.

---

## Architecture & Implementation

1. **Vector Storage**: Ingests timestamp and yield records into parallel data structures (`std::vector<std::string>` and `std::vector<double>`), keeping memory footprint minimal.
2. **Mean Rate Computation**: `average()` computes historical benchmark averages across the dataset.
3. **Lookup Engine**: `find_rate()` executes linear search over indexed dates and returns yield values with fallback sentinel codes.
4. **Input Loop & Signal Processing**: Listens for interactive user queries on `std::cin`, handling stream termination (`cin.eof()`) cleanly.

---

## Author

- **Thanh Vy Vo** ([@vyvo1302](https://github.com/vyvo1302))

---

## License

This project is open-source and available under the [MIT License](LICENSE).

