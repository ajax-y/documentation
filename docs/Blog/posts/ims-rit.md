---
date: 2026-05-29
slug: ims-rit
categories:
  - Projects
tags:
  - Python
  - SQLite
  - React
authors:
  - aj4y
hide:
  - navigation
---

# Designing IMS: An Administrative Command Center for RIT, Chennai 🏫

Efficient academic operations require robust tracking of student enrollment databases, semester schedules, faculty course maps, and department limits. To move away from manual paperwork and messy excel lists, I built **IMS (Institutional Management System)**—a clean, lightweight student and staff record registry custom-tailored for the administrative structure of **Rajalakshmi Institute of Technology (RIT), Chennai**.

In this article, we will examine the system architecture, SQLite relational database structure, and the Vite React admin interface.

<!-- more -->

---
<a href="https://github.com/ajax-y/ims" class="github-card" target="_blank" rel="noopener"><div class="github-card-content"><div class="github-card-icon">📁</div><div class="github-card-info"><h4>ajax-y/ims</h4><p>IMS: A collegiate profile, course enrollment, and directory dashboard built using React Vite, Python, and serverless SQLite database structures.</p></div></div><div class="github-card-action">View on GitHub ➔</div></a>
---

## 💡 What is IMS?

IMS is designed as a centralized record dashboard for university administrators. It provides separate views and management boards to perform daily institutional tracking:

```
                            ┌────────────────────────┐
                            │    IMS ADMIN PORTAL    │
                            └───────────┬────────────┘
                                        │
             ┌──────────────────────────┴──────────────────────────┐
             ▼                                                     ▼
┌────────────────────────┐                            ┌────────────────────────┐
│ Student Database       │                            │ Faculty Directory      │
│ - Course Enrollments   │                            │ - Departmental Mapping │
│ - Grade Tracking       │                            │ - Schedule Rosters     │
└────────────────────────┘                            └────────────────────────┘
```

*   **Student Registry Panel:** Manage academic profiles, handle student enrollments, record major/minor divisions, and track marks.
*   **Faculty Roster Management:** Monitor active academic professors, map their specialized courses, and coordinate departmental teaching hours.
*   **Security Control Center:** A secure admin credentials checkpoint ensuring that sensitive academic lists cannot be modified without permission.

---

## 🛠️ Lightweight Architecture Blueprint

To ensure the system is easy to run on regular admin computers without complex cloud environments, the architecture was designed to be lightweight:

*   **Vite React Frontend:** Renders a fast, responsive dashboard using structured admin panels.
*   **Python (FastAPI / Flask logic):** Powers the backend, handling queries, authenticating sessions, and serving database payloads.
*   **SQLite Relational Database (`ims.db`):** A serverless SQL database engine. The entire database is stored as a single file on the local computer, meaning zero database server setup time and exceptionally simple backup creation.

---

## 🗄️ Database Design (SQLite)

The backend interacts with a relational database layout mapping students, faculty, and academic departments:

```sql
-- Departments Table
CREATE TABLE departments (
  dept_id INTEGER PRIMARY KEY AUTOINCREMENT,
  dept_name VARCHAR(100) UNIQUE NOT NULL,
  dept_code VARCHAR(10) UNIQUE NOT NULL
);

-- Students Table tracking academic statuses
CREATE TABLE students (
  student_id INTEGER PRIMARY KEY AUTOINCREMENT,
  enrollment_no VARCHAR(20) UNIQUE NOT NULL,
  first_name VARCHAR(50) NOT NULL,
  last_name VARCHAR(50),
  email VARCHAR(100) UNIQUE,
  dept_id INTEGER,
  current_semester INTEGER DEFAULT 1,
  academic_status VARCHAR(20) DEFAULT 'ACTIVE',
  FOREIGN KEY(dept_id) REFERENCES departments(dept_id)
);

-- Faculty directory and academic titles
CREATE TABLE faculty (
  faculty_id INTEGER PRIMARY KEY AUTOINCREMENT,
  employee_code VARCHAR(20) UNIQUE NOT NULL,
  first_name VARCHAR(50) NOT NULL,
  last_name VARCHAR(50),
  email VARCHAR(100) UNIQUE,
  dept_id INTEGER,
  designation VARCHAR(50) NOT NULL,
  FOREIGN KEY(dept_id) REFERENCES departments(dept_id)
);

-- Course registries connected to teachers
CREATE TABLE courses (
  course_id INTEGER PRIMARY KEY AUTOINCREMENT,
  course_code VARCHAR(15) UNIQUE NOT NULL,
  course_name VARCHAR(150) NOT NULL,
  credits INTEGER NOT NULL CHECK (credits > 0),
  faculty_id INTEGER,
  FOREIGN KEY(faculty_id) REFERENCES faculty(faculty_id)
);
```

---

## 🎨 The Vite React Admin Experience

To give admins a beautiful, distraction-free work environment, the frontend was designed to be clean and easy to use:
*   **Search Filters:** Type-ahead filters on the Student and Faculty panels let admins instantly find entries using names, registration numbers, or departments.
*   **Status Indicators:** Color-coded status markers quickly show key information (e.g., active students are shown in green, while graduated profiles are marked in soft blue).
*   **Data Forms:** Clean, interactive modal forms handle all data entry with built-in validation checks, preventing typos or missing details.

---

## 🚦 How to Launch IMS Locally

Setting up the project on an administrative computer is straightforward:

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/ajax-y/ims.git
    cd ims
    ```
2.  **Launch the Backend Logic:**
    ```bash
    python main.py
    ```
3.  **Start the Vite Frontend Panel:**
    ```bash
    npm install
    npm run dev
    ```

IMS demonstrates how simple Python utilities and lightweight relational databases can be turned into highly useful tools for schools and universities by adding clean, user-friendly frontend dashboards!
