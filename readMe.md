# Student Grade Management & Analysis System

### APM11A1 - Advanced Programming | Assignment 3

---

## What is this?

This is a Student Grade Management and Analysis System built in C++. It simulates a backend system that a university faculty admin would use to manage student records and perform various administrative tasks — from looking up a single student to generating every possible study group combination.

The system holds a list of students, each with a name, age, student number and grade. It then runs seven different algorithms against that data, each one solving a real administrative task while demonstrating a different time complexity class.

The data model is built using OOP with a three-level inheritance chain:

```
Person              ← abstract base class (name, age)
  └── Student       ← adds studentNumber, grade
        └── PostgradStudent  ← adds researchTopic
```

---

## Project Structure

```
Assignment3/
├── main.cpp                  ← all 7 algorithms + main function
└── models/
    ├── Person.h              ← abstract base class
    ├── Student.h             ← inherits Person
    └── PostgradStudent.h     ← inherits Student
```

---

## The Algorithms

### Algorithm 1 — O(1) Constant: Fixed Grade Dashboard

**Task:** Print a fixed 5×5 grade band summary table for the faculty.

**How it works:** Two for loops iterate over fixed-size arrays — always 5 grade bands and always 5 performance categories. The table is always 5×5 = 25 cells regardless of how many students are in the system.

**Why O(1):** The loop sizes never change. Whether there are 8 students or 80,000 students in the system, this function always does exactly 25 iterations — nothing more, nothing less. The number of students has zero effect on how long this takes to run. That is what constant time means.

```
Big-O: O(1)   Big-Θ: Θ(1)   Big-Ω: Ω(1)   Space: O(1)
```

---

### Algorithm 2 — O(log n) Logarithmic: Binary Search

**Task:** Find a specific student by their student number from a sorted list.

**How it works:** The array is first sorted by student number. Binary search then checks the middle element — if the target is smaller it discards the right half, if larger it discards the left half. It keeps halving the remaining search space until the student is found or confirmed absent.

**Why O(log n):** Each step cuts the remaining students in half. With 8 students you need at most 3 steps because you can halve 8 exactly 3 times before reaching 1. With 1024 students you need at most 10 steps. The work grows very slowly compared to the number of students — that is what logarithmic time means.

```
Big-O: O(log n)   Big-Θ: Θ(log n)   Big-Ω: Ω(1)   Space: O(1)
```

> Best case Ω(1) — the very first midpoint checked happens to be the target student.

---

### Algorithm 3 — O(n) Linear: Find Top Student

**Task:** Find the student with the highest grade from an unsorted list.

**How it works:** One pass through the entire array, keeping track of the highest grade seen so far. Every student is compared once against the current maximum.

**Why O(n):** There is no shortcut when the data is unsorted. Even if the top student happens to be the very first one in the list, every remaining student still needs to be checked to confirm no higher grade exists. The more students there are, the longer it takes — proportionally. That is what linear time means.

```
Big-O: O(n)   Big-Θ: Θ(n)   Big-Ω: Ω(n)   Space: O(1)
```

---

### Algorithm 4 — O(n log n) Log-Linear: Merge Sort

**Task:** Rank all students by grade from highest to lowest.

**How it works:** Repeatedly splits the student list in half until each piece has only one student in it. A single student is already in order by definition. It then merges those pieces back together in the correct order. Each merge step puts students in the right position as the pieces get combined back into a full sorted list.

**Why O(n log n):** The splitting keeps halving the list — the same slow growth as binary search. But unlike binary search, merging requires looking at every student at each level to put them in order. So you have the slow halving growth combined with looking at all students at each step. This makes it slightly worse than linear but far better than quadratic. It also performs exactly the same whether the list starts sorted or completely shuffled.

```
Big-O: O(n log n)   Big-Θ: Θ(n log n)   Big-Ω: Ω(n log n)   Space: O(n)
```

> Space is O(n) because the algorithm needs temporary holding space for students during each merge step.

---

### Algorithm 5 — O(n²) Quadratic: Bubble Sort

**Task:** Sort students by student number in ascending order so that binary search (Algorithm 2) can be applied to them.

**How it works:** Two nested loops repeatedly compare neighbouring students and swap them if they are out of order. The largest unsorted student bubbles to their correct position at the end of the list on each outer pass. An early-exit check stops the sort immediately if the list becomes fully sorted before all passes are complete.

**Why O(n²):** There is a loop inside a loop and both depend on how many students there are. Double the students and the work roughly quadruples. This is why bubble sort becomes very slow on large datasets compared to merge sort — both sort the same students, but bubble sort does far more work to get there.

```
Big-O: O(n²)   Big-Θ: Θ(n²)   Big-Ω: Ω(n)   Space: O(1)
```

> Best case Ω(n) — if the list is already sorted, the early-exit check fires after just one pass through all students.

---

### Algorithm 6 — O(2^n) Exponential: Study Group Subset Generator

**Task:** Generate every possible combination of students that could form a study group from a shortlist of top performers.

**How it works:** For each student the algorithm asks one question — is this student in the group or not? That gives two possibilities per student. All those possibilities combined produce every possible grouping. Each combination is generated by treating each student as a yes or no decision and working through all possible combinations of those decisions.

**Why O(2^n):** Every time you add one more student to the shortlist, the number of possible combinations doubles. With 2 students there are 4 combinations. With 3 there are 8. With 4 there are 16. With 10 there would be 1024. This is why the algorithm is intentionally run on only 4 students — at larger numbers it becomes completely impractical very quickly.

```
Big-O: O(2^n)   Big-Θ: Θ(2^n)   Big-Ω: Ω(2^n)   Space: O(n)
```

---

### Algorithm 7 — O(n!) Factorial: Presentation Order Generator

**Task:** Generate every possible order in which a group of students could present their projects to the class.

**How it works:** The algorithm places one student in the first position, then generates every possible ordering of the remaining students for the positions that follow. It then tries the next student in the first position and does the same thing again, repeating until every possible ordering has been produced.

**Why O(n!):** With 1 student there is only 1 possible order. With 2 students there are 2 orders. With 3 students there are 6. With 4 there are 24. With 5 there are 120. The number of orderings grows explosively — each additional student multiplies the total by one more. This is why the algorithm is intentionally run on only 3 students. At 8 students it would produce 40,320 orderings; at 12 students, nearly 500 million.

```
Big-O: O(n!)   Big-Θ: Θ(n!)   Big-Ω: Ω(n!)   Space: O(n)
```

> Space is O(n) because each recursive call adds one level to the call stack, and the stack only ever grows as deep as the number of students.

---

## How to Run

### Prerequisites

You need a C++ compiler installed. On Mac, open Terminal and run:

```bash
xcode-select --install
```

Verify it installed correctly:

```bash
g++ --version
```

You should see a version number. If you do, you are ready.

---

### Step 1 — Get the files

Make sure your folder structure looks exactly like this:

```
Assignment3/
├── main.cpp
└── models/
    ├── Person.h
    ├── Student.h
    └── PostgradStudent.h
```

The `models` folder must be a subfolder inside `Assignment3`. Do not put all files in the same directory.

---

### Step 2 — Open the folder in VS Code

In VS Code: **File → Open Folder** and select your `Assignment3` folder.

---

### Step 3 — Open the terminal

In VS Code press `` Ctrl+` `` to open the integrated terminal. Make sure you are inside the `Assignment3` folder. You can confirm this by running:

```bash
pwd
```

It should show a path ending in `Assignment3`. If not, navigate there with `cd`.

---

### Step 4 — Compile

```bash
g++ -std=c++17 -o run main.cpp
```

If no output appears, the compilation was successful.

---

### Step 5 — Run

```bash
./run
```

You will see all 7 algorithms execute in sequence with full output for each one.

---

### Recompiling after changes

Any time you edit a file, recompile before running again:

```bash
g++ -std=c++17 -o run main.cpp && ./run
```

This compiles and immediately runs in one command.

---

## OOP Summary

| Concept       | Where it appears                                                                |
| ------------- | ------------------------------------------------------------------------------- |
| Abstraction   | `Person` is abstract — cannot be instantiated directly                          |
| Inheritance   | `Student` extends `Person`, `PostgradStudent` extends `Student`                 |
| Polymorphism  | `getProfile()` is virtual — correct override called based on actual object type |
| Encapsulation | All fields are private/protected, accessed only through getters                 |
