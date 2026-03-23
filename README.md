# Mission Planner (C Project)

## 📌 Overview

The *Mission Planner* is a command-line application written in standard C that helps users create, manage, and track personal goals. This project was designed as a practical application of core programming concepts, combining structured data management, dynamic memory allocation, and file persistence.

Built within a ~6-hour development window, this project reflects both technical growth and personal motivation—focusing on productivity, organization, and continuous improvement.

---

## Purpose

The goal of this project was to:

* Apply concepts learned in class to a real-world problem
* Explore *new features of the C language and standard library*
* Build something meaningful and personally relevant

Inspired by principles of self-direction and thoughtful problem-solving, this project emphasizes initiative, creativity, and learning by doing.

---

## Problem Statement

Managing multiple goals can become overwhelming without a structured system. There is a need for a simple, lightweight tool that:

* Stores goals with deadlines
* Tracks completion status
* Provides progress insights
* Persists data between sessions

---

## Solution

The Mission Planner allows users to:

* Add and describe goals
* Assign due dates
* Track completion status
* View remaining time for each goal
* Save and reload goals from a file
* Generate a progress report

All features are implemented using standard C, ensuring portability across systems.

---

## Features

*  Dynamic goal management (auto-resizing array)
*  Date parsing and formatting (YYYY-MM-DD)
*  Countdown of days remaining
*  Mark goals as completed
*  Save/load goals using file I/O
*  Progress report with completion percentage

---

##  Technologies Used

* Language: C (ANSI standard only)
* Libraries:

  * `stdio.h` (input/output)
  * `stdlib.h` (memory management)
  * `string.h` (string handling)
  * `time.h` (date and time operations)

No external libraries or platform-specific features (e.g., `windows.h`, `conio.h`, `system()`)

---

## Project Structure

```
Task.c        # Main program file
goals.txt     # Data file (generated at runtime)
```

---

## How to Run

1. Compile the program:

```bash
gcc Task.c -o mission_planner
```

2. Run the executable:

```bash
./mission_planner
```

---

## Example Menu

```
Mission Planner Menu
1. Add Goal
2. View Goals
3. Mark Goal as Completed
4. Save Goals
5. Load Goals
6. Progress Report
7. Exit
```

---

## Key Learning Outcomes

This project incorporates several *new concepts not previously covered in class*:

###  Dynamic Memory Allocation

* Used `malloc()` and `realloc()` to create a flexible, resizable list of goals
* Ensures efficient memory usage as the number of goals grows

###  Time and Date Handling

* Parsed user input into structured time using `mktime()`
* Calculated time differences with `difftime()`
* Formatted dates using `strftime()`

###  File Input/Output

* Implemented persistent storage using:

  * `fopen()`
  * `fprintf()`
  * `fscanf()`
* Allows saving and loading goals between sessions

These additions demonstrate independent learning and exploration beyond course material.

---

##  Program Behavior

* Automatically resizes memory when capacity is reached
* Validates date input format
* Handles empty states (no goals available)
* Provides real-time feedback to the user

---

## Limitations & Future Improvements

* No input validation for extremely large text inputs
* File format is plain text (could be improved with structured formats)
* No sorting/filtering of goals

### Future Enhancements

* Add priority levels for goals
* Implement sorting by due date
* Add search functionality
* Improve user interface

---

## Rubric Alignment

✔️ Proper scope (non-trivial, multi-feature system)
✔️ Compiles and runs without critical warnings
✔️ Uses only standard C libraries
✔️ Demonstrates new learning beyond course material

---

## Reflection

This project strengthened my understanding of how low-level programming concepts—like memory management and file handling—can be combined to build practical applications. It also reinforced the importance of planning, problem-solving, and learning independently.
