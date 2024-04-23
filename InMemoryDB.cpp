#include <iostream>
#include <unordered_map>
#include <stack>
#include <stdexcept>

class InMemoryDB {
private:
    std::unordered_map<std::string, int> data;
    bool inTransaction = false;
    std::unordered_map<std::string, int> transactionData;

public:
    void begin_transaction() {
        if (inTransaction) {
            throw std::runtime_error("Transaction already in progress");
        }
        inTransaction = true;
        transactionData.clear();
    }

    void put(const std::string& key, int val) {
        if (!inTransaction) {
            throw std::runtime_error("No transaction in progress");
        }
        transactionData[key] = val;
    }

    int get(const std::string& key) {
        if (transactionData.count(key) && inTransaction) {
            return transactionData[key];
        } else if (data.count(key)) {
            return data[key];
        } else {
            throw std::runtime_error("Key not found");
        }
    }

    void commit() {
        if (!inTransaction) {
            throw std::runtime_error("No transaction to commit");
        }
        for (auto& kv : transactionData) {
            data[kv.first] = kv.second;
        }
        inTransaction = false;
        transactionData.clear();
    }

    void rollback() {
        if (!inTransaction) {
            throw std::runtime_error("No transaction to rollback");
        }
        transactionData.clear();
        inTransaction = false;
    }
};

int main() {
    InMemoryDB db;
    std::cout << "\n--- Basic Operation Tests ---\n";
    try {
        std::cout << "Get non-existing key 'C': ";
        std::cout << db.get("C") << std::endl; 
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        db.put("C", 3); 
    } catch (const std::exception& e) {
        std::cout << "Attempt to put without transaction: " << e.what() << std::endl;
    }

    std::cout << "\n--- Transaction Tests ---\n";
    db.begin_transaction();
    db.put("A", 5);
    std::cout << "A = " << db.get("A") << " (uncommitted)" << std::endl;
    db.commit();

    std::cout << "A = " << db.get("A") << " (after commit)" << std::endl;

    try {
        db.put("A", 6);
    } catch (const std::exception& e) {
        std::cout << "Attempt to put without new transaction after commit: " << e.what() << std::endl;
    }

    db.begin_transaction();
    db.put("A", 10);
    db.put("B", 20); 
    std::cout << "A = " << db.get("A") << " (changed within transaction, uncommitted)" << std::endl;
    std::cout << "B = " << db.get("B") << " (new key within transaction, uncommitted)" << std::endl;
    db.rollback();

    try {
        std::cout << "A = " << db.get("A") << " (after rollback)" << std::endl;  
        std::cout << "B = " << db.get("B") << std::endl;  
    } catch (const std::exception& e) {
        std::cout << "Error after rollback (expected for 'B'): " << e.what() << std::endl;
    }

    std::cout << "\n--- Multiple Transaction Tests ---\n";
    db.begin_transaction();
    db.put("D", 40);
    db.begin_transaction();
    db.put("E", 50);
    db.commit();
    try {
        std::cout << "D = " << db.get("D") << std::endl;
        std::cout << "E = " << db.get("E") << std::endl; 
    } catch (const std::exception& e) {
        std::cout << "Nested transaction test: " << e.what() << std::endl;
    }

    return 0;
}