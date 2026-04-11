#include <iostream>
#include <list>
#include <vector>
#include <set>

// Clase adaptadora para std::list
template<class T>
class ListAdapter {
private:
    std::list<T> data;
public:
    void insert(const T& value) {
        data.push_back(value);
    }
    
    bool find(const T& value) const {
        for (const auto& item : data) {
            if (item == value) return true;
        }
        return false;
    }
    
    bool remove(const T& value) {
        auto it = std::find(data.begin(), data.end(), value);
        if (it != data.end()) {
            data.erase(it);
            return true;
        }
        return false;
    }
    
    T* get(const T& key) {
        for (auto& item : data) {
            if (item == key) return &item;
        }
        return nullptr;
    }
    
    void print() const {
        for (const auto& item : data) {
            std::cout << item << " ";
        }
    }
    
    bool empty() const {
        return data.empty();
    }
};

// Tabla Hash con templates
template<class T, class S, class F, size_t Z>
class CHashTable {
private:
    S table[Z];
    F hash_function;
    
public:
    void insert(const T& value) {
        size_t index = hash_function(value) % Z;
        table[index].insert(value);
    }
    
    bool remove(const T& value) {
        size_t index = hash_function(value) % Z;
        return table[index].remove(value);
    }
    
    T* find(const T& key) {
        size_t index = hash_function(key) % Z;
        return table[index].get(key);
    }
    
    void print_hash_table() {
        for (size_t i = 0; i < Z; ++i) {
            if (!table[i].empty()) {
                std::cout << "[" << i << "]: ";
                table[i].print();
                std::cout << std::endl;
            }
        }
    }
};

// Función de dispersión simple para int
struct SimpleHash
{   int operator()(int value)
    {   return value;   }
};

int main()
{
    std::cout << "=== Ejemplo de CHashTable con enteros ===" << std::endl;
    CHashTable<int, ListAdapter<int>, SimpleHash, 10> hashTable;
    
    hashTable.insert(5); hashTable.insert(15);
    hashTable.insert(25); hashTable.insert(7);
    hashTable.insert(17);
    
    std::cout << "Tabla Hash:" << std::endl;
    hashTable.print_hash_table();
    
    // Usando find() para buscar elementos
    std::cout << "\nUsando find():" << std::endl;
    int* ptr = hashTable.find(15);
    if (ptr != nullptr)
        std::cout << "Elemento 15 encontrado, valor: " << *ptr << std::endl;
    else
        std::cout << "Elemento 15 no encontrado" << std::endl;
    
    hashTable.remove(15);
    std::cout << "\nDespués de eliminar 15:" << std::endl;
    hashTable.print_hash_table();
    
    ptr = hashTable.find(15);
    if (ptr != nullptr)
        std::cout << "Elemento 15 encontrado, valor: " << *ptr << std::endl;
    else
        std::cout << "Elemento 15 no encontrado (nullptr)" << std::endl;
    std::cout <<"\n";

    return 0;
}
