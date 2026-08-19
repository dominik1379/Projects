# Projects
Projects coded in C, JavaScript, SQL



SQL script defines a PostgreSQL relational database schema for an online accommodation booking system, complete with automated business logic and data validation mechanisms.

Database Architecture & Core Domain
The system centers around standard hotel/property reservation management with 7 primary tables:

Host & Accommodation Context: Host, Ubytovanie (Property), and Izba (Room).

Booking & Financials: Rezervacia (Reservation), Platba (Payment, 1:1 relationship with reservations), and Rezervacia_Izba (a many-to-many junction table resolving room assignments per booking).

Feedback System: Recenzia (Reviews) linked to both hosts and properties.

Key Technical Features & Engineering Patterns

Database Views: Implements specialized views covering single-table filters, relational JOINs, aggregations, set operations (INTERSECT), and dynamic subqueries for reporting and modular data access.

PL/pgSQL Triggers & Automation: Custom stored functions enforce business rules at the database level—such as recalculating average property ratings upon review submission and preventing double-booking overlaps for guests.

Custom Auto-Increment Logic: Uses dedicated PostgreSQL sequences (CREATE SEQUENCE) paired with BEFORE INSERT triggers to assign primary keys if omitted.

Stored Procedures & Functions: Contains procedure routines for high-value booking analysis and scalar functions (VYPOCITAJ_CELKOVU_CENU) to calculate aggregated guest expenditure.

Data Integrity: Strict constraints including Foreign Keys with ON DELETE CASCADE, UNIQUE keys, and numeric CHECK ranges (e.g., ratings between 0–5).
