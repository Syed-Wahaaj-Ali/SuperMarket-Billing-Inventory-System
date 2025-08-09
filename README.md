# SuperMarket Billing & Inventory System 🛒

A **C++ command-line application** that manages billing and inventory operations for a supermarket. Built using **Object-Oriented Programming (OOP)** and **file handling** no external libraries or STL containers used.

---

## 🔧 Features

* 🔐 **Login system** (Admin & Cashier roles)
* 📦 **Product management**

  * Add, View, Update, Delete products
* 🧾 **Billing system**

  * Generate bills and deduct stock
  * Store bills in a folder
* 🏪 **Inventory tracking**

  * Stock levels and product info stored in `products.txt`
* 👨‍💼 **User management**

  * Admin & cashier credentials from `users.txt`
* 💾 Persistent data using simple `.txt` files

---

## 📁 File Structure

```
SuperMarket-Billing-Inventory-System/
│
├── main.cpp              → Main program code
├── products.txt          → Stores product records
├── users.txt             → Stores user credentials
├── bills/                → Stores generated bills
├── .gitignore            → Ignores .exe and temporary files
```

---

## 🚀 Getting Started

1. **Compile:**
   Use any C++ compiler like `g++`:

   ```bash
   g++ main.cpp -o supermarket.exe
   ```

2. **Run:**

   ```bash
   ./supermarket.exe
   ```

> 📝 Make sure `products.txt`, `users.txt`, and `bills/` folder exist in the same directory before running.

---

## 🎯 Concepts Used

* Object-Oriented Programming
* Encapsulation & Inheritance
* File Handling in C++
* Login/Role-based access
* CLI-based UI/UX

---

## 📄 License

This project is open for learning and personal use.
