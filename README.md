# 🏦 Advanced Banking Management System (C++)

## 📌 Description

A secure **console-based banking system** built using C++.

The system supports **client management**, **transactions**, and **user authentication with permission control** using bitwise authorization flags.

## 🔐 Security & Authentication

* Login system with username and password
* Role-based permission validation
* Full access or granular permission levels

## 👥 User Management Module

* List users
* Add new user
* Delete user (soft delete design)
* Update user information
* Search user

## 💰 Banking Operations

* Client management (CRUD)
* Deposit and withdrawal transactions
* Total balance reporting

## 🧠 Technical Highlights

* File-based persistence storage
* Bitwise permission system implementation
* Vector container memory handling
* Modular architecture design
* Authentication workflow

## 📂 Project Structure

* `main.cpp` → Core application logic
* `Clients.txt` → Clients database file
* `Users.txt` → Users database file

## 🚀 How to Run

Clone the repository from GitHub then compile:

```bash
g++ main.cpp -o banking_advanced
```

Run program:

```bash
./banking_advanced
```
