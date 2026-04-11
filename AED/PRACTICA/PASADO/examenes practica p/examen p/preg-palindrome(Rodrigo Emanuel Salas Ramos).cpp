#include <iostream>
#include <deque>
#include <string>
#include <cctype>

template<class T>
class MyStack {
private:
    std::deque<T> data;
public:
    void push(T value) {
        // Implementar
        data.push_back(value);
    }

    void pop() {
        // Implementar
        if (!data.empty()) data.pop_back();
    }

    T top() {
        // Implementar
        if (!data.empty()) return data.back();
        return T();
    }

    bool empty() {
        // Implementar
        if (!data.empty()) return false;
        return true;
    }

    int size() {
        // Implementar
        if (!data.empty()) return data.size();
        return 0;
    }
};

template<class T>
class MyQueue {
private:
    std::deque<T> data;
public:
    void push(T value) {
        data.push_back(value);
        // Implementar
    }

    void pop() {
        // Implementar
        if (!data.empty()) data.pop_front();
    }

    T front() {
        // Implementar
        if (!data.empty()) {
            return data.front();
        }
        return T();
    }

    bool empty() {
        // Implementar
        if (!data.empty()) return false;
        return true;
    }

    int size() {
        // Implementar
        if (!data.empty()) return data.size();
        return 0;
    }
};

class PalindromeChecker {
private:
    MyStack<char> stack;
    MyQueue<char> queue;

public:
    bool isPalindrome(std::string s) {
        // Implementar
        // Llenar el stack y el queue con los caracteres
        for (char i : s) {
            queue.push(i);
            stack.push(i);
        }
        char p = stack.top();
        char q = queue.front();
        while (p == q) {
            p = stack.top();
            q = queue.front();
            stack.pop(); queue.pop();
            if ((stack.empty()) || (queue.empty())) return true;
        }
        while (!stack.empty()) {
            stack.pop();
        }
        while (!queue.empty()) {
            queue.pop();
        }
        return false;
    }
};

// Ejemplo simple de recorrido de string con []
void ejemploRecorridoString() {
    std::string palabra = "hola";

    std::cout << "=== Ejemplo: Recorrer string con [] ===" << std::endl;
    std::cout << "Palabra: " << palabra << std::endl;
    std::cout << "Caracteres:" << std::endl;

    for (int i = 0; i < palabra.length(); i++) {
        std::cout << "  palabra[" << i << "] = " << palabra[i] << std::endl;
    }

    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
}

int main() {
    // Mostrar ejemplo de recorrido
    ejemploRecorridoString();

    // Pruebas de palíndromos
    PalindromeChecker checker;

    std::cout << "=== Verificación de Palíndromos ===" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "oso: " << checker.isPalindrome("oso") << std::endl;
    std::cout << "reconocer: " << checker.isPalindrome("reconocer") << std::endl;
    std::cout << "neuquen: " << checker.isPalindrome("neuquen") << std::endl;
    std::cout << "radar: " << checker.isPalindrome("radar") << std::endl;
    std::cout << "salas: " << checker.isPalindrome("salas") << std::endl;
    std::cout << "somos: " << checker.isPalindrome("somos") << std::endl;
    std::cout << "anita: " << checker.isPalindrome("anita") << std::endl;
    std::cout << "python: " << checker.isPalindrome("python") << std::endl;
    std::cout << "racecar: " << checker.isPalindrome("racecar") << std::endl;
    std::cout << "hello: " << checker.isPalindrome("hello") << std::endl;
    std::cout << "level: " << checker.isPalindrome("level") << std::endl;
    std::cout << "world: " << checker.isPalindrome("world") << std::endl;

    return 0;
}
