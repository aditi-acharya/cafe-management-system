# Cafe Management System (C, Console)

A menu-driven console app in C that simulates a small cafe workflow with **Admin** and **Employee** roles.

## How it works
- **Admin** logs in (`admin` / `abcde`) to manage menu items and view total sales.
- **Employee** takes customer orders, manages an **order queue**, edits orders, and generates bills.
- All data (menu, orders, queue) is stored in memory using linked lists.
- No file/database storage—state resets when program exits.

## Key data structures & concepts
- **Singly linked list** for menu items and customer orders.
- **Linked-list queue** for tracking customers waiting to be served.
- **Pointers & dynamic memory** with `malloc` / `free`.
- **Menu-driven CLI** with loops and `switch` statements.
- **Role-based flows** with basic authentication.

## Features
- **Admin:** Add, delete, and view menu items; check total sales.
- **Employee:** Take new orders, view/modify orders, calculate bills, manage customer queue.
- Pre-loaded menu at startup.
- Simple console interaction.

## Build & run
gcc cafe_management.c -o cafe_management
- ./cafe_management    # Linux/macOS
- .\cafe_management.exe  #Windows

## Limitations & ideas to extend
- **Current**: No quantities per order line, no data persistence, sales tracked only in session.
- **Possible extensions**: File/database storage, quantities, per-customer order history, improved input handling, modular code.

## What I learnt
- Implementing linked lists & queues in C.
- Using pointers and dynamic memory for flexible data.
- Designing role-based, menu-driven programs.
