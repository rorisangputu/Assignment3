#include <iostream>
#include <vector>
#include <string>
#include "models/person.h"
#include "models/student.h"
#include "models/postgradStudent.h"

using namespace std;

// Helper functions

void printDivider(const string &title)
{
    cout << "\n"
         << string(60, '=') << "\n";
    cout << "  " << title << "\n";
    cout << string(60, '=') << "\n";
}

void printStudents(const vector<Student *> &students, const string &label)
{
    cout << "\n"
         << label << ":\n";
    for (const auto &s : students)
        s->getProfile();
}

void printAllProfiles(const vector<Person *> &people, const string &label)
{
    cout << "\n"
         << label << ":\n";
    for (const auto &p : people)
        p->getProfile(); // virtual dispatch — correct version called automatically
}

// =================================================
// ALGOS
// =================================================

//  ALGORITHM 1 — O(1): Fixed Grade Summary Dashboard
/*
 *  Prinst a fixed grade-band summary table for the faculty.
 *  The table dimensions are constants — they never
 *  change regardless of how many students are in the system.
 */
void fixedGradeDashboard()
{
    printDivider("ALGO 1: O(1) Constant — Fixed Grade Dashboard");

    const int BANDS = 5;
    const int CATS = 5;

    string bands[BANDS] = {"F (0-49)", "D (50-59)", "C (60-69)",
                           "B (70-79)", "A (80-100)"};
    string cats[CATS] = {"BelowAvg", "Average", "AboveAvg",
                         "Excellent", "Outstdng"};

    // Minimum threshold for each band/category intersection
    int thresholds[BANDS][CATS] = {
        {0, 10, 20, 30, 40},
        {50, 52, 54, 56, 58},
        {60, 62, 64, 66, 68},
        {70, 73, 75, 77, 79},
        {80, 84, 88, 92, 96}};

    // Loop 1: print header (always 5 iterations)
    cout << "\nGrade Band    ";
    for (int j = 0; j < CATS; j++)
        cout << cats[j] << "\t";
    cout << "\n"
         << string(70, '-') << "\n";

    // Loop 2: print rows (always 5x5 = 25 iterations total)
    for (int i = 0; i < BANDS; i++)
    {
        cout << bands[i] << "\t";
        for (int j = 0; j < CATS; j++)
            cout << thresholds[i][j] << "\t\t";
        cout << "\n";
    }

    cout << "\n[O(1): always exactly 25 iterations regardless of student count n]\n";
}

//  ALGORITHM 2 — O(log n): Binary Search by Student Number
/*
 *  Using sorted array of students, algo finds a student by their
 *  student number quickly. Used by admin to look up any record.
 */
int binarySearch(const vector<Student *> &students, int target)
{
    int low = 0;
    int high = (int)students.size() - 1;
    int steps = 0;

    while (low <= high)
    {
        steps++;
        int mid = low + (high - low) / 2; // safe midpoint (avoids overflow)

        if (students[mid]->getStudentNumber() == target)
        {
            cout << "  Found in " << steps << " step(s): ";
            students[mid]->getProfile();
            return mid;
        }
        else if (students[mid]->getStudentNumber() < target)
        {
            low = mid + 1; // discard left half
        }
        else
        {
            high = mid - 1; // discard right half
        }
    }
    cout << "  Not found after " << steps << " step(s).\n";
    return -1;
}

void runBinarySearch(const vector<Student *> &students)
{
    printDivider("ALGO 2: O(log n) Logarithmic — Binary Search");
    cout << "(Requires array sorted by student number (Algo 5: Bubble Sort))\n";

    cout << "\nSearching for student 23004:\n";
    binarySearch(students, 23004);

    cout << "\nSearching for student 99999 (does not exist):\n";
    binarySearch(students, 99999);
}

//  ALGORITHM 3 — O(n): Linear Search for Top Student
/*
 *  Finds the highest-scoring student from an the unsorted array.
 *  Since there is no ordering, every student must
 *  be viewed at least once to confirm the maximum.
 */
void linearSearchTopStudent(const vector<Student *> &students)
{
    printDivider("ALGO 3: O(n) Linear — Linear Search (Top Student)");

    int maxIdx = 0;
    int comparisons = 0;

    for (int i = 1; i < (int)students.size(); i++)
    {
        comparisons++;
        if (students[i]->getGrade() > students[maxIdx]->getGrade())
            maxIdx = i;
    }

    cout << "\n  Scanned " << comparisons << " students in one pass.\n";
    cout << "  Top student: ";
    students[maxIdx]->getProfile();
}

//  ALGORITHM 4 — O(n log n): Merge Sort by Grade (Descending)
/*
 *  Produces a class ranking by sorting all students by grade
 *  in descending order.
 */
void merge(vector<Student *> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Student *> L(arr.begin() + left, arr.begin() + left + n1);
    vector<Student *> R(arr.begin() + mid + 1, arr.begin() + mid + 1 + n2);

    int i = 0, j = 0, k = left;

    // Merge in DESCENDING order of grade
    while (i < n1 && j < n2)
    {
        if (L[i]->getGrade() >= R[j]->getGrade())
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<Student *> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);      // sort left half
        mergeSort(arr, mid + 1, right); // sort right half
        merge(arr, left, mid, right);   // merge both halves
    }
}

void runMergeSort(vector<Student *> &students)
{
    printDivider("ALGORITHM 4: O(n log n) — Merge Sort (by Grade)");
    printStudents(students, "Before Merge Sort");
    mergeSort(students, 0, (int)students.size() - 1);
    printStudents(students, "After Merge Sort (Descending by Grade)");
}

//  ALGORITHM 5 — O(n²): Bubble Sort by Student Number
/*
 *  Sorts students by student number in ascending order so that
 *  binary search (Algorithm 2) can be applied.
 */
void bubbleSort(vector<Student *> &students)
{
    printDivider("ALGO 4: O(n^2) Quadratic — Bubble Sort (by Student Number)");

    int n = (int)students.size();
    int totalSwaps = 0;

    printStudents(students, "Before Bubble Sort (shuffled)");

    for (int i = 0; i < n - 1; i++)
    { // outer loop
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        { // inner loop
            if (students[j]->getStudentNumber() >
                students[j + 1]->getStudentNumber())
            {
                swap(students[j], students[j + 1]);
                swapped = true;
                totalSwaps++;
            }
        }
        if (!swapped)
            break; // early exit if already sorted
    }

    printStudents(students, "After Bubble Sort (Ascending by Student Number)");
    cout << "\n  Total swaps: " << totalSwaps << "\n";
}

//  ALGORITHM 6 — O(2^n): Study Group Subset Generator
/*
 *  Generate every possible study group combination from a
 *  shortlist of top students.
 */
void generateSubsets(const vector<Student *> &students)
{
    printDivider("ALGORITHM 6: O(2^n) — Study Group Subset Generator");

    int n = (int)students.size();
    int total = 1 << n; // 2^n via bit shift

    cout << "\n  " << total << " possible combinations for "
         << n << " students:\n\n";

    for (int mask = 0; mask < total; mask++)
    {
        cout << "  Subset " << mask << ": { ";
        bool empty = true;
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            { // is bit i set?
                cout << students[i]->getName() << " ";
                empty = false;
            }
        }
        if (empty)
            cout << "(empty)";
        cout << "}\n";
    }
}

//  ALGORITHM 7 — O(n!): Presentation Order Generator
/*
 *  Generate every possible presentation order for a small
 *  group of students.
 */
int permCount = 0;

void generatePermutations(vector<Student *> &students, int start)
{
    if (start == (int)students.size())
    {
        permCount++;
        cout << "  Order " << permCount << ": ";
        for (int i = 0; i < (int)students.size(); i++)
        {
            cout << students[i]->getName();
            if (i < (int)students.size() - 1)
                cout << " -> ";
        }
        cout << "\n";
        return;
    }
    for (int i = start; i < (int)students.size(); i++)
    {
        swap(students[start], students[i]);        // choose
        generatePermutations(students, start + 1); // recurse
        swap(students[start], students[i]);        // backtrack
    }
}

void runPermutations(vector<Student *> students)
{
    printDivider("ALGORITHM 7: O(n!) — Presentation Order Generator");

    int n = (int)students.size();
    int fact = 1;
    for (int i = 1; i <= n; i++)
        fact *= i;

    cout << "\n  Generating all " << fact
         << " orderings for " << n << " students:\n\n";

    permCount = 0;
    generatePermutations(students, 0);
}

//  POLYMORPHISM DEMO
//  Store both Student and PostgradStudent in a vector<Person*>
//  and call getProfile() — the correct override fires for each.
void polymorphismDemo(const vector<Person *> &people)
{
    printDivider("OOP DEMO — Polymorphism via virtual getProfile()");
    cout << "\n  Calling getProfile() on a vector<Person*> that holds\n";
    cout << "  both Student and PostgradStudent objects:\n\n";
    for (const auto &p : people)
        p->getProfile(); // runtime dispatch — correct version called
    cout << "\n  Notice: same function call, different output per type.\n";
}

// ============================================================
//  MAIN
// ============================================================
int main()
{
    cout << "=====================================================\n";
    cout << "   STUDENT GRADE MANAGEMENT & ANALYSIS SYSTEM\n";
    cout << "   APM11A1 - Assignment 3\n";
    cout << "=====================================================\n";

    // Student dataset
    // Mix of Student and PostgradStudent objects
    Student *s1 = new Student("Rorisang Putu", 26, 23001, 72);
    Student *s2 = new Student("Michael Bay", 28, 23002, 55);
    Student *s3 = new Student("Patrick Bateman", 22, 23003, 88);
    Student *s4 = new Student("Miles Morales", 23, 23004, 91);
    Student *s5 = new Student("Martin Madrazo", 20, 23005, 63);
    Student *s6 = new Student("Big Zulu", 24, 23006, 47);

    PostgradStudent *p1 = new PostgradStudent("Grace Ndlovu", 26, 23007, 79,
                                              "Machine Learning");
    PostgradStudent *p2 = new PostgradStudent("Hiro Patel", 28, 23008, 84,
                                              "Cloud Computing");

    // Working array for algorithms (Student* so we can access grade/number)
    vector<Student *> students = {s1, s2, s3, s4, s5, s6, p1, p2};

    // Polymorphism demo array (Person* — holds both types)
    vector<Person *> people = {s1, s2, s3, s4, s5, s6, p1, p2};

    // ── OOP / Polymorphism demo
    polymorphismDemo(people);

    //  Algorithm 1: O(1) - Constant
    fixedGradeDashboard();

    // ── Algorithm 2: O(log n) -- Logarithmic
    // Needs sorted array — sort first using bubble sort (Algo 5)
     vector<Student *> shuffled = {s6, s3, p2, s1, s5, p1, s2, s4};
    bubbleSort(shuffled);
    runBinarySearch(shuffled);

    // ── Algorithm 3: O(n) -- Linear
    linearSearchTopStudent(students);

    // ── Algorithm 4: O(n log n) -- Log Linear
    vector<Student *> toMergeSort = students;
    runMergeSort(toMergeSort);

    // ── Algorithm 5: O(n²) ─- Quadratic
    // Shuffle so the sort is non-trivial
    vector<Student *> mixed = {s6, s3, p2, s1, s5, p1, s2, s4};
    bubbleSort(mixed);

    // ── Algorithm 6: O(2^n) -- Exponentials
    // Only top 4 students (2^4 = 16 subsets)
    vector<Student *> topFour = {s4, s3, p2, p1};
    generateSubsets(topFour);

    // ── Algorithm 7: O(n!) -- Factorial
    // Only 3 students (3! = 6 permutations)
    vector<Student *> presenters = {s4, s3, p2};
    runPermutations(presenters);

    // ── Clean up heap memory
    delete s1;
    delete s2;
    delete s3;
    delete s4;
    delete s5;
    delete s6;
    delete p1;
    delete p2;

    cout << "\n=====================================================\n";
    cout << "   ALL ALGORITHMS EXECUTED SUCCESSFULLY\n";
    cout << "=====================================================\n";

    return 0;
}