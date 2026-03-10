#  Philosophers

---

##  Introduction

**Philosophers** is a 42 school project that addresses the classic **Dining Philosophers Problem**. The objective is to learn the basics of threading a process and how to work on the same memory space using mutexes to prevent data races and deadlocks.

---

##  The Problem

One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle. The philosophers alternatively **eat**, **think**, or **sleep**.

* There are as many forks as philosophers.
* A philosopher must take their right and left forks to eat.
* When they finish eating, they put their forks back on the table and start sleeping.
* Once awake, they start thinking.
* The simulation stops when a philosopher dies of starvation.

---

##  Features

* **Thread Management**: Each philosopher is represented by a dedicated thread.
* **Mutex Protection**: Forks are protected by mutexes to ensure they are never used by two philosophers at the same time.
* **Synchronized Logs**: All status changes (eating, sleeping, thinking, dying) are timestamped and displayed without overlapping, thanks to a dedicated writing mutex.
* **Death Monitoring**: A monitoring system checks in real-time if a philosopher has exceeded their time to die.

---

##  Installation

### 1. Clone the repository

git clone [https://github.com/slkrt111/Philosophers.git](https://github.com/slkrt111/Philosophers.git)
cd Philosophers

### 2. Compilation

Compile the program using the Makefile:
make

---

##  Usage

Run the program with the following arguments:
./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]

Example:
./philosophers 5 800 200 200

* 5: Number of philosophers.
* 800: Time (in ms) before a philosopher dies if they haven't started eating.
* 200: Time (in ms) it takes to eat.
* 200: Time (in ms) spent sleeping.

---

##  Technical Implementation

### 1. Threads (POSIX)

The project uses `pthread_create`, `pthread_join`, and `pthread_detach` to manage parallel execution.

### 2. Mutexes

Mutexes (`pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`) are used to protect the shared resources (forks) and to prevent **Data Races** when checking or updating shared variables (like the death flag or the last meal time).

### 3. Precision

Time management is handled using `gettimeofday` to ensure millisecond precision, which is crucial for the survival of the philosophers.
