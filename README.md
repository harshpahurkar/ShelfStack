# ShelfStack

A console-based library management application built in **C++11** — handles book inventory, membership tracking, checkout/return workflows, and persistent data storage.

---

## Features

- **Publication Management** — Add, remove, and search books and periodicals in the library catalog
- **Membership System** — Track member checkouts with 5-digit membership IDs
- **Search & Filter** — Search by title keyword across the entire catalog with type filtering (Book / Publication)
- **Check Out / Return** — Full checkout and return workflow with date tracking
- **Persistent Storage** — All records saved to disk (`data/LibRecs.txt`) and loaded on startup
- **Interactive Menus** — Clean, navigable console menus with input validation
- **Change Tracking** — Prompts to save unsaved changes on exit

## Architecture

```
┌──────────────────────────────────────────────┐
│                   LibApp                      │
│         (Application Controller)              │
│                                               │
│  ┌─────────┐  ┌──────────┐  ┌─────────────┐  │
│  │  Menu   │  │   Book   │  │ Publication  │  │
│  │ System  │  │          │  │  Selector    │  │
│  └────┬────┘  └────┬─────┘  └──────┬──────┘  │
│       │            │               │          │
│       ▼            ▼               ▼          │
│  ┌─────────────────────────────────────────┐  │
│  │          Publication (Base)              │  │
│  │     Streamable  ·  Date  ·  Lib         │  │
│  └─────────────────────────────────────────┘  │
└──────────────────────────────────────────────┘
```

## Project Structure

```
ShelfStack/
├── include/              # Header files
│   ├── Book.h            # Book class (extends Publication)
│   ├── Date.h            # Date handling utilities
│   ├── Lib.h             # Global constants
│   ├── LibApp.h          # Main application controller
│   ├── Menu.h            # Menu & MenuItem classes
│   ├── Publication.h     # Base publication class
│   ├── PublicationSelector.h  # Search result selector
│   └── Streamable.h      # I/O interface
├── src/                  # Implementation files
│   ├── Book.cpp
│   ├── Date.cpp
│   ├── LibApp.cpp        # Core application logic
│   ├── LibAppMain.cpp    # Entry point (main)
│   ├── Menu.cpp
│   ├── Publication.cpp
│   ├── PublicationSelector.cpp
│   └── Streamable.cpp
├── data/
│   └── LibRecs.txt       # Persistent library records
├── LICENSE
└── README.md
```

## Tech Stack

| Component | Technology |
|---|---|
| Language | C++11 |
| Paradigm | Object-Oriented (inheritance, polymorphism, encapsulation) |
| I/O | File streams, console I/O with `Streamable` interface |
| Build | g++ / clang++ |
| Platform | Cross-platform (Linux, macOS, Windows) |

## Build & Run

**Prerequisites:** A C++11 compatible compiler (GCC 4.8+, Clang 3.3+, or MSVC 2015+).

```bash
# Compile
g++ -Wall -std=c++11 -g -I include -o LibApp src/*.cpp

# Run
./LibApp
```

**Windows (MSVC):**
```powershell
cl /EHsc /std:c++11 /I include src\*.cpp /Fe:LibApp.exe
.\LibApp.exe
```

## Usage

On launch, the application loads existing records from `data/LibRecs.txt` and presents the main menu:

```
ShelfStack
 1- Add New Publication
 2- Remove Publication
 3- Checkout publication from library
 4- Return publication to library
 0- Exit
>
```

| Action | Description |
|---|---|
| **Add** | Add a new Book or Publication with title, author, shelf number |
| **Remove** | Search and remove a publication from the catalog |
| **Checkout** | Search for a publication and check it out to a member ID |
| **Return** | Return a checked-out publication |
| **Exit** | Save changes (if any) and exit |

## Design Patterns

- **Template Method** — `Streamable` defines the I/O interface; `Publication` and `Book` implement specific serialization
- **Composition** — `LibApp` composes `Menu`, `PublicationSelector`, and `Publication` arrays
- **Polymorphism** — Base `Publication*` pointers handle both `Book` and `Publication` objects transparently

## License

MIT License — see [LICENSE](LICENSE) for details.
