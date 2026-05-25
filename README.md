# Nexus Smart Home Hub (OOP C++ Simulation)

Welcome to the **Nexus Smart Home Hub**, a console-based Object-Oriented Programming (OOP) simulation written entirely in C++. This repository models an intelligent building ecosystem, managing multiple room layouts, security authentication frames, automated hardware state triggers, and dynamic telemetry data logging.

This project showcases clean C++ design patterns, robust dynamic memory allocations, standard input sanitation streams, and decoupled structural class architectures.

---

## 🚀 System Features

- **Multi-Level User Security Matrix**: Enforces a strict verification runtime loop featuring distinct authentication boundaries (e.g., `admin`, `owner`, and `guest` credentials).
- **Dynamic Architectural Node Mapping**: Dynamically registers newly allocated `Room` blocks onto the central home engine array without risking compilation size or manual index bottlenecks.
- **Bi-Category Hardware Separation**: Seamlessly handles granular workflows for standard `SmartDevice` components (e.g., toggles, reboots, and metrics updates) alongside functional `SmartAppliance` modules (featuring unique macro operations like `startCycle()`).
- **Global Override Messaging**: Broadcasts immediate safety routines (`turnAllOff`) sequentially down into every attached sub-device in the room array matrix with a single transaction hook.
- **Telemetry Data & Analytics Engine**: Seeds dynamic metric log structures (`EnergyLog`) into historical framework vectors to filter energy consumption metrics by targeted billing period benchmarks.

---

## 🛠️ Class Architecture & Design Layout

The project leverages a decoupled, cohesive object structure designed to maximize modularity:

* `UserAuthentication`: Manages runtime profiles, handles validation passes, and generates runtime security overrides or privilege key expansion metrics.
* `SmartHome`: The core structural controller. Houses data registers for individual tracking rooms and provides the dynamic orchestration layer for the central dashboards.
* `Room`: Represents a specific geometric sector (e.g., Lounge, Kitchen). Manages active nested vectors of pointer streams pointing to physical components.
* `SmartDevice` (Base / Component Class): Represents standard hardware units. Exposes state interfaces for status queries, runtime logic reports, toggles, and warm reboots.
* `SmartAppliance` (Derived / Specialization Class): Inherits core status frameworks from the base device profile while introducing dedicated physical mechanics like cycle telemetry mapping.
* `EnergyLog`: Captures physical usage metrics (Kilowatt Hours) stamped against standardized `YYYY-MM-DD` billing markers.

---

## 📋 Prerequisites & Compilation

To build and run this simulation context locally, ensure you have a standard modern C++ compiler supporting **C++11 or higher** (such as `gcc`, `clang`, or MSVC).

---

## ⚙️ How to Build & Run (Windows)

### 1. Install dependencies
Make sure you have installed:
- CMake
- MinGW (GCC compiler)
- Git
- VS Code (optional)

---

### 2. Clone the repository

```bash
git clone https://github.com/zayanwaris7-hash/Home-Simulation-Oops-Cpp.git
cd Home-Simulation-Oops-Cpp
```

### 3. Create build folder
```bash
mkdir build
cd build
```

### 4. Generate build files using CMake
```bash
cmake .. -G "MinGW Makefiles"
```

### 5. Compile the project
```bash
cmake --build .
```

### 6. Run the program
```bash
./Home-Simulation-Oops-Cpp.exe
```
---
## 💻 Operation Guide
Once inside the central dashboard, you can interact with the system using the unified command loop options:

###Manage Rooms & Hardware Devices:
Step deep into specific room indexes to dynamically toggle state metrics, review live reporting diagnostics, add internal structural nodes, or remove standard hardware IDs.

### Create and Register a New Room:
Extends structural boundaries dynamically. Includes an automated duplication parser (isDuplicate) to protect memory layers from overlapping unique string identifiers.

### Broadcast Command (Turn All Devices OFF):
Emergency system-wide global reset that targets all active rooms simultaneously.

Open Central Energy Dashboard: Filters tracked usage history matching target string criteria (e.g., 2026-05).

### Add Manual Energy Log Entry:
Custom telemetry injection that creates standard snapshot objects and binds them to the hub.

### Security (Provision Guest Access Keys): 
Temporarily extends operational access keys to third-party endpoints.

### Shut Down System Hub & Exit:
Triggers full user logout and handles orderly framework de-initialization routines.
---
## 🔒 Memory Allocation Disclaimers
This simulation framework relies actively on dynamic memory management rules (new keywords) to construct structural tracking vectors. Developers expanding upon the active codebase or linking it to explicit execution drivers should verify that proper traversal routines are integrated within parent destructors (delete keywords) to prevent runtime memory leakages.
