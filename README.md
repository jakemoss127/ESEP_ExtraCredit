# In-Memory Database with Transaction Support (C++)
## Description
This project implements a simple in-memory key-value database in C++ that supports basic transaction functionalities including begin_transaction, commit, rollback, put, and get. The key-value pairs are stored in-memory, and transactions ensure that changes are either fully committed or rolled back to maintain data integrity.

## Setup and Running the Code
Prerequisites
C++ Compiler (GCC recommended)
Make (optional for compiling multiple files)

## Compilation
Navigate to the directory containing the source code and compile the project using the following command:

`g++ -o InMemoryDB InMemoryDB.cpp`

After compilation, you can run the program using:

`./InMemoryDB`

## Successful Test Execution
I have added a main to test some of the in memory database's functionality. Below is an screenshot successfully running the main. 
![Test Output](https://github.com/jakemoss127/ESEP_ExtraCredit/assets/93219053/b0cebf7d-2570-472b-b60a-67ed64f43ab5)

## Future Modification Ideas
In the future, providing a starter code for basic operations might help students focus more on the transaction logic rather than setup, which could help improve learning database operations.
Next semester maybe consider adding a GUI or command-line interface requirement for interactive testing and demonstration purposes, making the assignment more engaging and visually understandable.
I'd also consider the addition of multi-threading support to simulate more realistic transaction scenarios involving concurrency. We had an assigment in OS (COP4600) like this using multithreading and it was cool to learn.
