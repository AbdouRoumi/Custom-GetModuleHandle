# CustomGetModuleHandle

## [![Typing SVG](https://readme-typing-svg.demolab.com?font=JetBrains+Mono&weight=2000&pause=1000&width=435&lines=Welcome+to+Custom-GetModuleHandle+Repo!!!;Check+my+Repos+for+some+Malwares;This+will+be+used+in+the+next+techniques)](https://git.io/typing-svg)


## Overview
The **CustomGetModuleHandle** project demonstrates how to manually enumerate loaded modules in a Windows process using the Process Environment Block (PEB). Unlike the standard `GetModuleHandleW` API, this custom implementation directly accesses internal Windows structures to retrieve module information, a common technique used in malware development and anti-analysis strategies.

This technique can bypass certain API hooks set by antivirus or EDR (Endpoint Detection and Response) tools, making it a valuable concept for both red team operators and malware analysts.

## Table of Contents
- [Overview](#overview)
- [Purpose](#purpose)
- [How It Works](#how-it-works)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Code Explanation](#code-explanation)
- [Disclaimer](#disclaimer)
- [License](#license)

## Purpose
- Demonstrate manual DLL enumeration using PEB.
- Bypass potential hooks on standard APIs.
- Serve as an educational example for reverse engineers and malware analysts.

## How It Works
1. Access the **Process Environment Block (PEB)** using architecture-specific offsets.
2. Traverse the `InMemoryOrderModuleList` to enumerate loaded modules.
3. Compare module names with the target DLL name.
4. Return the module base address if found.

## Requirements
- Windows Operating System
- Visual Studio (or compatible IDE)
- Basic knowledge of Windows Internals
- Understanding of PEB structures

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/YourUsername/CustomGetModuleHandle.git
   ```
2. Open the project in **Visual Studio**.
3. Build the project in **Debug** or **Release** mode.

## Usage
Run the compiled executable and observe the outputs:
```plaintext
[i] Original 0x00007FF8C40D0000
[i] Replacement 0x00007FF8C40D0000
```
The output will display the original API result and the custom implementation's result.

## Code Explanation
### Key Functions
- **IsStringEqual:** Compares two wide strings case-insensitively.
- **CustomGetModuleHandle:** Traverses `InMemoryOrderModuleList` to find the target module.

### Key Concepts
- **PEB (Process Environment Block)**: Internal Windows structure containing process-specific data.
- **LDR_DATA_TABLE_ENTRY:** Structure containing information about each loaded module.

## Disclaimer
This project is intended for **educational and research purposes only**. Misuse of this code for malicious purposes is strictly prohibited.

## License
This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---
**Happy Coding! 🛡️🔍**

