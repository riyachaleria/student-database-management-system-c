# 🎓 Student Management Database System in C

Welcome to the **Student Management Database System**, a menu-driven console application built entirely in C. It allows users to manage student records with powerful features such as dynamic subject handling, sorting, searching, result analysis, and file backup — all implemented with **Dynamic Memory Allocation (DMA)** and **Binary File Handling**.

---

## 🚀 Features

- ✅ Add, View, Update, and Delete Student Records
- ✅ Dynamic Subject Count per Student
- ✅ Percentage Calculation
- ✅ Sorting by:
  - Name (A–Z / Z–A)
  - Roll Number (Asc / Desc)
  - Percentage (Topper / Weakest)
- ✅ Search by Name or Roll Number
- ✅ Result Analysis:
  - Toppers (90%+)
  - Pass List (All Marks ≥ 35)
  - Fail List (Any Mark < 35)
- ✅ Backup to Binary File
- ✅ Export to CSV File
- ✅ Clean and Structured Output

## 📂 File Structure

📁 Student-Management-System/
│
├── sourcecode.c ← Main source code 🧠
├── sourcecode.exe ← Executable file (Windows) ⚙️
├── README.md ← This beautiful documentation (We Are Here) ✨
├── studentdata.csv ← Auto-created after CSV export [NOT shared]
├── studentsdata.bin ← Auto-created after saving records [NOT shared]
├── backup_history.bin ← Auto-created after backup [NOT shared]

> ⚠️ Only `sourcecode.c` and `sourcecode.exe` are included in the repository.  
> Your personal `.csv` and `.bin` files remain on your system and are never shared.

## 🔧 Compilation Instructions

If you're compiling manually using GCC:
```bash
gcc student.c -o student.exe

./student.exe


    Menu Overview
----------Main Menu----------
1 - Add New Students
2 - View All Students
3 - Search Student
4 - Update Student Info
5 - Delete a Student
6 - Sort Students
7 - Topper / Fail List
8 - Save Records to File
9 - Export to CSV
0 - Exit

📌 Notes

CSV Export and Binary Backup require confirmation before proceeding.
Subject count and marks are validated (no negative values).
Percentage is automatically calculated after entry/update.
Uses qsort() for efficient sorting.
File-safe and memory-safe practices followed.

## 🤝 Contributing

This is a solo project for learning and showcasing C skills. In future versions, contributions or suggestions 
are welcome!

##  License

This project is currently not licensed for reuse. Please do not copy, distribute, or modify without explicit 
permission.

Note: This program auto-generates `studentsdata.bin', `backup_history.bin`, and `studentdata.csv` files on first use. 
These files are local to your system and are not shared publicly or stored in this repository.

**Author**
**RIYA CHALERIA**❤️