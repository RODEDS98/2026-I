#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = 0;
    }
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() {
        head = 0;
    }

    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void printForward() {
        Node* current = head;
        std::cout << "Lista: ";
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " -> ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void swapNodes(int x, int y) {
        std::cout << "  SWAP  " << std::endl;
        // find x 	//Node* head;
             //std::cout <<"  H  "<< std::endl;
        Node* *p = 0;            //std::cout <<"  P  "<< std::endl;
        Node* *q = 0;            // std::cout <<"  Q  "<< std::endl;
        bool b_x = 0;
        bool b_y = 0;
        // FIND  x, y:

        for (Node** h = &head; *h; h = &((*h)->next)) {
            //	std::cout <<"  H  "<< std::endl;
            if ((*h)->data == x && !b_x) {
                //Node** s = h;
                p = h;
                b_x = 1;
            }
            if ((*h)->data == y && !b_y) {
                q = h;
                b_y = 1;
            }
        }

        // FIND  x, y
        if (!b_x && !b_y)  return;
        else {
            Node* tmp_p = *p;
            Node* post_x = (*p)->next;
            Node* post_y = (*q)->next;
            
            *p = *q;   // vamos al y
             if ((*q)->next == 0) {
                 (*q)->next = post_x;
                 *q = tmp_p;   //
                 tmp_p->next = 0;
            }
            else {
                (*q)->next = post_x;
                *q = tmp_p;   //
                tmp_p->next = post_y;
            }
            



   }

}






    
};

int main() {
    SinglyLinkedList lista;

    // Crear lista: 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70
    lista.push_back(10);
    lista.push_back(20);
    lista.push_back(30);
    lista.push_back(40);
    lista.push_back(50);
    lista.push_back(60);
    lista.push_back(70);

    std::cout << "LISTA ORIGINAL" << std::endl;
    lista.printForward();
    std::cout << std::endl;

    std::cout << "1 - Swap con valor inexistente - swap(10, 999)" << std::endl;
    std::cout << "Antes:    10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70" << std::endl;
    std::cout << "Esperado: 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70" << std::endl;
    lista.swapNodes(10, 999);
    lista.printForward();
    std::cout << std::endl;

    std::cout << "2 - Swap del mismo valor - swap(30, 30)" << std::endl;
    std::cout << "Antes:    10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70" << std::endl;
    std::cout << "Esperado: 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70" << std::endl;
    lista.swapNodes(30, 30);
    lista.printForward();
    std::cout << std::endl;

    std::cout << "3 - Swap de dos nodos no adyacentes - swap(20, 50)" << std::endl;
    std::cout << "Antes:    10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70" << std::endl;
    std::cout << "Esperado: 10 -> 50 -> 30 -> 40 -> 20 -> 60 -> 70" << std::endl;
    lista.swapNodes(20, 50);
    lista.printForward();
    std::cout << std::endl;

    std::cout << "4 - Swap que involucra head (no adyacente) - swap(10, 40)" << std::endl;
    std::cout << "Antes:    10 -> 50 -> 30 -> 40 -> 20 -> 60 -> 70" << std::endl;
    std::cout << "Esperado: 40 -> 50 -> 30 -> 10 -> 20 -> 60 -> 70" << std::endl;
    lista.swapNodes(10, 40);
    lista.printForward();
    std::cout << std::endl;

    std::cout << "5 - Swap que involucra el último elemento (no adyacente) - swap(30, 70)" << std::endl;
    std::cout << "Antes:    40 -> 50 -> 30 -> 10 -> 20 -> 60 -> 70" << std::endl;
    std::cout << "Esperado: 40 -> 50 -> 70 -> 10 -> 20 -> 60 -> 30" << std::endl;
    lista.swapNodes(30, 70);
    lista.printForward();
    std::cout << std::endl;

    std::cout << "6 - Swap de head con el último elemento (no adyacentes) - swap(40, 30)" << std::endl;
    std::cout << "Antes:    40 -> 50 -> 70 -> 10 -> 20 -> 60 -> 30" << std::endl;
    std::cout << "Esperado: 30 -> 50 -> 70 -> 10 -> 20 -> 60 -> 40" << std::endl;
    lista.swapNodes(40, 30);
    lista.printForward();
    std::cout << std::endl;

    std::cout << "7 - Swap de nodos adyacentes en el medio - swap(70, 10)" << std::endl;
    std::cout << "Antes:    30 -> 50 -> 70 -> 10 -> 20 -> 60 -> 40" << std::endl;
    std::cout << "Esperado: 30 -> 50 -> 10 -> 70 -> 20 -> 60 -> 40" << std::endl;
    lista.swapNodes(70, 10);
    lista.printForward();
    std::cout << std::endl;

    std::cout << "8 - Swap de nodos adyacentes donde uno es head - swap(30, 50)" << std::endl;
    std::cout << "Antes:    30 -> 50 -> 10 -> 70 -> 20 -> 60 -> 40" << std::endl;
    std::cout << "Esperado: 50 -> 30 -> 10 -> 70 -> 20 -> 60 -> 40" << std::endl;
    lista.swapNodes(30, 50);
    lista.printForward();
    std::cout << std::endl;

    std::cout << "9 - Swap de nodos adyacentes donde uno es el último - swap(60, 40)" << std::endl;
    std::cout << "Antes:    50 -> 30 -> 10 -> 70 -> 20 -> 60 -> 40" << std::endl;
    std::cout << "Esperado: 50 -> 30 -> 10 -> 70 -> 20 -> 40 -> 60" << std::endl;
    lista.swapNodes(60, 40);
    lista.printForward();
    std::cout << std::endl;

    std::cout << "10 - Swap de head con su adyacente - swap(50, 30)" << std::endl;
    std::cout << "Antes:    50 -> 30 -> 10 -> 70 -> 20 -> 40 -> 60" << std::endl;
    std::cout << "Esperado: 30 -> 50 -> 10 -> 70 -> 20 -> 40 -> 60" << std::endl;
    lista.swapNodes(50, 30);
    lista.printForward();
    std::cout << std::endl;

    return 0;
}
