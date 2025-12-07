# Banking System (CLI Simulation)

## Project Overview

This project is a simple, yet comprehensive, **Command-Line Interface (CLI)** simulation of a banking system, developed entirely in **C++**. It is designed to provide fundamental functionalities for managing user accounts and performing core financial transactions such as deposits and transfers, alongside a basic notification system.

The system is structured clearly and utilizes **CSV files** for data persistence, making it an excellent educational resource for students and novice developers interested in understanding the basics of data management, transaction logic, and interactive CLI development in C++.

## Key Features

The application provides a robust set of features for both regular users and administrators:

*   **User Management & Authentication:**
    *   Secure login mechanism for both standard users and administrators (Admin).
    *   Account status verification (Active/Inactive).
    *   Administrator tools for managing users (adding, deleting, and modifying accounts).
*   **Core Financial Transactions:**
    *   **Deposit:** Functionality to safely deposit funds into a user's account.
    *   **Transfer:** Capability to transfer funds between different user accounts within the system, with balance validation.
*   **Notification System:**
    *   A simple system to view transaction-related notices and alerts.
*   **Data Persistence:**
    *   All user data, transactions, and notifications are stored in CSV files (e.g., `note.csv`), ensuring data continuity across different sessions.
*   **Interactive CLI:**
    *   A straightforward and interactive command-line interface, enhanced with color support for a better user experience (Note: Color support is platform-dependent).

## Getting Started

### Prerequisites

To build and run this project, you will need:

*   A C++ compiler that supports the C++11 standard or newer (e.g., GCC or Clang).
*   **Platform Note:** The project uses the `windows.h` library for console color functions. To run the application with full functionality, a Windows environment is required. For Linux/macOS, you may need to modify the code to use platform-specific alternatives (like ANSI escape codes) or compile without the color functions.

### Building and Running

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/Ahmed-Senan-Al-Aini/Banking-system.git
    cd Banking-system
    ```

2.  **Compile the Code (using GCC as an example):**
    ```bash
    g++ system-bank.cpp -o banking_system
    ```
    *Note: You might need to add specific compilation flags depending on your environment.*

3.  **Run the Application:**
    ```bash
    ./banking_system
    ```

## Project Structure

The project is composed of two main files, separating core logic from utility functions:

| File | Description |
| :--- | :--- |
| `system-bank.cpp` | Contains the main application logic, including data structures (`User`, `Transfer`, `Notice`), data persistence functions (load/save), transaction logic, and the primary application entry point (`main`). |
| `tools.h` | A header file containing utility functions for console interaction, such as setting colors and secure input handling with error checking. |
| `README.md` | This documentation file. |

## Usage (Interactive Guide)

The system operates entirely through an interactive Command-Line Interface (CLI), requiring numerical input to select options from menus.

### 1. Startup and Login

Upon running the compiled program (`./banking_system`), the system will prompt you to log in:

1.  **Login Screen:** You will be asked to enter your **ID Number** and **Password**.
2.  **User Types:**
    *   **Regular User:** Can perform financial transactions and view notifications.
    *   **Administrator (Admin):** Has access to the system management menu.

### 2. Regular User Menu

Once successfully logged in as a regular user, the main menu will offer the following options:

*   **Deposit:** Add a specified amount of money to your account balance.
*   **Transfer:** Transfer funds to another user's account within the system.
*   **View Notifications:** Review your transaction history and system alerts.
*   **Logout.**

### 3. Administrator (Admin) Menu

The Admin menu provides access to system-level management functions:

*   **User Management:** Add new users, delete existing users, or modify their details and account status (activate/deactivate).
*   **Comprehensive View:** Review all transactions and notifications across the entire system.

**Important Note:** All user, transaction, and notification data is automatically saved to CSV files to ensure data persistence between sessions.

## Tech Stack and Design Decisions

This project utilizes a focused set of technologies and design choices to achieve its goal as a simple, yet functional, banking simulation.

### 1. Core Technologies

| Technology | Purpose | Rationale |
| :--- | :--- | :--- |
| **C++** | Core development language for system logic and performance. | Chosen for its low-level control and suitability for developing efficient, standalone applications. Standard C++ features like `struct`, `vector`, and `fstream` are heavily utilized. |
| **CSV Files** | Data Persistence Mechanism. | Selected for simplicity and ease of integration with C++ file streams, making it ideal for small, educational projects where a full database is overkill. |
| **Command-Line Interface (CLI)** | Primary User Interaction Interface. | Used to simplify development and focus efforts on the backend transaction and data management logic. |
| **`windows.h`** | Console User Experience Enhancement. | Used specifically for implementing console color changes, indicating that the primary target environment for the full experience is Windows. |

### 2. Key Design Decisions

*   **Separation of Concerns:** Utility functions for user interface interaction (like input validation and color utilities) are isolated in the `tools.h` header file, keeping the core banking logic clean within `system-bank.cpp`.
*   **In-Memory Data Management:** The system relies on `std::vector` to store all user and transaction data in memory during runtime. This allows for fast data access and modification, with persistence handled only at startup (load) and shutdown (save).
*   **Robust Input Validation:** Dedicated utility functions (`chose`, `chose2`, `chose3`) are implemented in `tools.h` to ensure that user input is valid and within acceptable ranges, significantly reducing runtime errors.
*   **Data Integrity:** The load/save mechanism using CSV files ensures that all user balances, transaction records, and notifications are preserved, maintaining the state of the banking system across executions.

## Code Snippets

To illustrate the project's structure and core functions, here are key code snippets:

### 1. Essential Data Structure (`system-bank.cpp`)

The `User` struct defines the blueprint for a user account, central to the system's account management:

```cpp
struct User {
    string username;
    string password;
    string phoneNumber;
    bool isActive;
    int number;
    double balanc = 0.0;
    string userType; // Admin or regular user
    int puk;
};
```

### 2. Main Application Entry Point (`system-bank.cpp`)

The `main` function manages the application's lifecycle, from data loading to the main loop and final data saving:

```cpp
int main() {
    // Load data from CSV files
    loadUsersFromFile(users);
    loadtransFromFile(trans);
    loadnoteFromFile(note);
    
    // Check for admin user existence
    checkadmin(users);
    
    // Start the main application loop (login/menu)
    start_main();
    
    // Save data before exiting
    saveUsersToFile(users);
    savetrans(users, trans);
    savenote(users, note);
    
    return 0;
}
```

### 3. Utility Function Example (Color Utility) (`tools.h`)

This function demonstrates the use of the platform-specific `windows.h` library for console output enhancement:

```cpp
#include <windows.h>

void setcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
```

## Functions Reference

This section provides a comprehensive list of the main functions used in the project, categorized by their purpose, now including a simple code snippet for clarity.

### 1. Data Persistence Functions

These functions handle the loading and saving of system data (users, transactions, notifications) to and from CSV files.

| Function | File | Description | Snippet |
| :--- | :--- | :--- | :--- |
| `loadUsersFromFile` | `system-bank.cpp` | Loads all user data from the CSV file into a `vector<User>` object in memory. | `loadUsersFromFile(users);` |
| `saveUsersToFile` | `system-bank.cpp` | Saves all user data from memory back to the CSV file. | `saveUsersToFile(users);` |
| `loadtransFromFile` | `system-bank.cpp` | Loads all transaction records from the CSV file into memory. | `loadtransFromFile(trans);` |
| `savetrans` | `system-bank.cpp` | Saves all transaction records from memory back to the CSV file. | `savetrans(users, trans);` |
| `loadnoteFromFile` | `system-bank.cpp` | Loads all notification/note records from the CSV file into memory. | `loadnoteFromFile(note);` |
| `savenote` | `system-bank.cpp` | Saves all notification/note records from memory back to the CSV file. | `savenote(users, note);` |

### 2. User Management & Control Functions

These functions manage account validation, user administration, and program flow control.

| Function | File | Description | Snippet |
| :--- | :--- | :--- | :--- |
| `login` | `system-bank.cpp` | Handles the login process for both users and administrators, validating credentials. | `login(users, trans, note);` |
| `start_main` | `system-bank.cpp` | The primary application loop that presents the interactive menus after successful login. | `start_main();` |
| `checkadmin` | `system-bank.cpp` | Ensures an Administrator account exists in the system. | `checkadmin(users);` |
| `editUser` | `system-bank.cpp` | Allows modification of an existing user's details (typically used by the Admin). | `editUser(users, trans, note);` |
| `datelise` | `system-bank.cpp` | Toggles the active status of a user account (activate/deactivate). | `datelise(users);` |
| `deleteUser` | `system-bank.cpp` | Permanently removes a user account from the system. | `deleteUser(users);` |
| `isValidPhoneNumber` | `system-bank.cpp` | Validates the format of the entered phone number. | `if (isValidPhoneNumber(phone)) { ... }` |
| `isValidNumber` | `system-bank.cpp` | Validates the format of the entered account number. | `if (isValidNumber(accNum)) { ... }` |
| `checkerror` | `system-bank.cpp` | A general utility function for checking errors in numerical input. | `if (checkerror(input)) { ... }` |

### 3. Transactions & Core Logic Functions

These functions execute the fundamental financial operations of the banking system.

| Function | File | Description | Snippet |
| :--- | :--- | :--- | :--- |
| `depositmoney` | `system-bank.cpp` | Processes the deposit of funds into a user's account, updating the balance. | `depositmoney(users, trans, note);` |
| `transf` | `system-bank.cpp` | Manages the transfer of funds from the current user's account to a recipient's account. | `transf(users, trans, note);` |
| `receiveTransfer` | `system-bank.cpp` | Updates the recipient's balance and records the incoming transfer. | `receiveTransfer(users, trans, note);` |
| `TransferNumber` | `system-bank.cpp` | Generates a unique identifier for a new transaction record. | `int id = TransferNumber(trans);` |
| `findUserIndex` | `system-bank.cpp` | Searches for and returns the index of a specific user based on their account number. | `int index = findUserIndex(users, accNum);` |
| `findtransIndex` | `system-bank.cpp` | Searches for and returns the index of a specific transaction record. | `int index = findtransIndex(trans, id);` |
| `deletetrans` | `system-bank.cpp` | Removes a transaction record from the system. | `deletetrans(trans, id);` |

### 4. Display Functions

These functions are responsible for presenting information and reports to users and administrators.

| Function | File | Description | Snippet |
| :--- | :--- | :--- | :--- |
| `displaytransfer` | `system-bank.cpp` | Displays the transaction history for the currently logged-in user. | `displaytransfer(trans);` |
| `showadmin` | `system-bank.cpp` | Displays the Administrator's main menu and available management options. | `showadmin(users, trans, note);` |
| `displaynote` | `system-bank.cpp` | Displays the notifications and alerts associated with the user's account. | `displaynote(note);` |

### 5. Utility Functions (`tools.h`)

These functions enhance the user experience and provide general-purpose utilities.

| Function | File | Description | Snippet |
| :--- | :--- | :--- | :--- |
| `setcolor` | `tools.h` | Changes the text color in the console (Windows-dependent). | `setcolor(10); // Green` |
| `chose` | `tools.h` | A general selection function that validates user input against a specified range. | `int choice = chose(1, 5);` |
| `chose2` | `tools.h` | A specialized selection function for validating input within the range 0-6. | `int choice = chose2();` |
| `chose3` | `tools.h` | A specialized selection function for validating ID/Account number input. | `int id = chose3();` |
| `gettime` | `tools.h` | Retrieves the current date and time as a string for transaction logging. | `string time = gettime();` |
| `sleeps` | `tools.h` | Pauses the program execution for a specified duration. | `sleeps(2); // Pause for 2 seconds` |

## Contribution

Contributions are welcome! If you have suggestions for improvement, wish to report a bug, or want to add new features, please feel free to open an "Issue" or submit a "Pull Request."
