# 🧠 Philosophers

A project from the 42 curriculum exploring **multithreading, synchronization, and concurrency** through the classic **Dining Philosophers Problem**.

---

## 📘 Overview

The **Philosophers** project aims to simulate a group of philosophers sitting around a table, alternating between **thinking**, **eating**, and **sleeping** — all while sharing limited resources (forks).  
The main goal is to ensure that no philosopher **dies of starvation** and that there are **no data races or deadlocks**.

---

## 🧩 Project Objectives

- Understand and apply the concepts of **threads** and **mutexes**.  
- Manage **shared resources** safely.  
- Implement **precise timing and synchronization**.  
- Learn how to design concurrent programs in **C**.

---

## ⚙️ How It Works

Each philosopher is represented by a **thread**, and forks are represented by **mutexes**.  
The simulation follows these rules:

1. A philosopher must pick up both forks to eat.
2. After eating, they put the forks back down and go to sleep.
3. If a philosopher doesn’t eat within the time defined by `time_to_die`, they die.
4. The program stops when a philosopher dies or when all have eaten enough times (optional depending on project requirements).

---


## 🏗️ Compilation

Run the following command to compile:

```bash
make
```

This will create the executable:

```bash
./philo
```

---

## 🚀 Usage

**Parameters:**

`number_of_philosophers` — total number of philosophers (and forks)

`time_to_die` — time (in ms) a philosopher can go without eating

`time_to_eat` — time (in ms) spent eating

`time_to_sleep` — time (in ms) spent sleeping

`number_of_meals` (optional) — if provided, simulation stops once all philosophers have eaten this many times

Run the program like this:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

Example:

```bash
./philo 5 800 200 200
```

