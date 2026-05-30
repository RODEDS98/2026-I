#include <SFML/Graphics.hpp>
#include <iostream>
#include <initializer_list>
#include <queue>
#include <stack>
#include <string> 

using namespace std;

struct Node
{
    int value;
    Node* nodes[2];
    float x, y;
    bool is_perimeter;

    Node(int v) {
        value = v;
        nodes[0] = nodes[1] = nullptr;
        x = y = 0.0f;
        is_perimeter = false;
    }
};

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool find(int x, Node**& p);
    bool ins(int x);
    void ins(std::initializer_list<int> values);
    void print();
    void perimeter();
    void push_y_rotacion(queue<Node*>& cola, Node* n);
    void inorder(Node* n);

    Node* get_root() { return root; }
    void calculatePositions(Node* p, float x, float y, float offset_x);
    void resetPerimeter(Node* p);

private:
    Node* root;
};

CBinTree::CBinTree() { root = nullptr; }
CBinTree::~CBinTree() {}

bool CBinTree::find(int x, Node**& p)
{
    for (p = &root; *p && (*p)->value != x;
        p = &((*p)->nodes[x > (*p)->value]));
    return *p && (*p)->value == x;
}

bool CBinTree::ins(int x)
{
    Node** p;
    if (find(x, p)) return 0;
    *p = new Node(x);
    return 1;
}

void CBinTree::ins(std::initializer_list<int> values) { for (int x : values) ins(x); }
void CBinTree::print() { std::cout << "inorder: "; inorder(root); std::cout << "\n"; }

void CBinTree::resetPerimeter(Node* p) {
    if (!p) return;
    p->is_perimeter = false;
    resetPerimeter(p->nodes[0]);
    resetPerimeter(p->nodes[1]);
}

void CBinTree::perimeter()
{
    if (!root) return;
    resetPerimeter(root);

    queue<Node*> cola;
    queue<Node*> hojas;
    queue<Node*> izq;
    stack<Node*> der;
    cola.push(root);
    int cola_size = cola.size();

    while (!cola.empty()) {
        izq.push(cola.front());
        der.push(cola.back());

        Node* tmp_izq = cola.front();
        Node* tmp_der = cola.back();
        for (int i = 0; i < cola_size; i++) {
            Node* tmp_h = cola.front();
            if (tmp_h->nodes[0]) cola.push(tmp_h->nodes[0]);
            if (tmp_h->nodes[1]) cola.push(tmp_h->nodes[1]);
            if (tmp_h != tmp_izq && tmp_h != tmp_der) {
                if (!tmp_h->nodes[0] || !tmp_h->nodes[1]) {
                    push_y_rotacion(hojas, tmp_h);
                }
            }
            cola.pop();
        }
        cola_size = cola.size();
    }

    for (; !izq.empty(); ) { izq.front()->is_perimeter = true; izq.pop(); }
    for (; !hojas.empty(); ) { hojas.front()->is_perimeter = true; hojas.pop(); }
    for (; !der.empty(); ) { der.top()->is_perimeter = true; der.pop(); }
}

void CBinTree::push_y_rotacion(queue<Node*>& cola, Node* n) {
    if (cola.empty()) { cola.push(n); return; }
    int back_cola = cola.back()->value;
    int num_insertar = n->value;
    if (num_insertar >= back_cola) { cola.push(n); return; }
    else {
        bool insertado = false;
        int size_cola = cola.size();
        for (int i = 1; i <= size_cola; i++) {
            if (num_insertar < cola.front()->value && !insertado) {
                cola.push(n);
                insertado = true;
            }
            cola.push(cola.front());
            cola.pop();
        }
    }
}

void CBinTree::inorder(Node* n)
{
    if (!n) return;
    inorder(n->nodes[0]);
    std::cout << n->value << " ";
    inorder(n->nodes[1]);
}

void CBinTree::calculatePositions(Node* p, float x, float y, float offset_x) {
    if (!p) return;
    p->x = x;
    p->y = y;
    calculatePositions(p->nodes[0], x - offset_x, y + 80.0f, offset_x * 0.5f);
    calculatePositions(p->nodes[1], x + offset_x, y + 80.0f, offset_x * 0.5f);
}

void drawTreeEdges(sf::RenderWindow& window, Node* root) {
    if (!root) return;
    for (int i = 0; i < 2; ++i) {
        if (root->nodes[i]) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(root->x, root->y), sf::Color(120, 120, 120)),
                sf::Vertex(sf::Vector2f(root->nodes[i]->x, root->nodes[i]->y), sf::Color(120, 120, 120))
            };
            window.draw(line, 2, sf::Lines);
            drawTreeEdges(window, root->nodes[i]);
        }
    }
}

// Parametros de la fuente
void drawTreeNodes(sf::RenderWindow& window, Node* root, sf::Font& font) {
    if (!root) return;

    // Modificacion de radio
    float radius = 18.0f;
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(root->x, root->y);

    if (root->is_perimeter) {
        circle.setFillColor(sf::Color::Red);
    }
    else {
        circle.setFillColor(sf::Color::Blue);
    }
    window.draw(circle);

    // Configuracion de texto
    sf::Text text;
    text.setFont(font);
    text.setString(to_string(root->value));
    text.setCharacterSize(14); // Tamaño de la letra
    text.setFillColor(sf::Color::Black);

    // Centrar el texto del círculo
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(root->x, root->y);

    window.draw(text);

    // Recorrido recursivo del árbol
    drawTreeNodes(window, root->nodes[0], font);
    drawTreeNodes(window, root->nodes[1], font);
}

int main()
{
    CBinTree t1;
    t1.ins({ 50,
             30, 70,
             20, 40, 60, 80,
             15, 25, 35, 45, 55, 65, 75, 90,
             12, 17, 22, 28, 32, 38, 42, 48, 52, 58, 62, 68, 72, 78, 85, 95 , 10 , 55 , 91 , 62 , 55 , 44 , 88, 1000 , 1001 , 105 , 109 , 50, 21, 22 , 45, 46 , 41 });

    t1.perimeter();

    sf::RenderWindow window(sf::VideoMode(1500, 800), "Visualizador SFML");
    window.setFramerateLimit(60);


    sf::Font font;// CARGAR FUENTE

    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cout << "Error cargando la fuente. Se intentará abrir de manera local." << std::endl;
        if (!font.loadFromFile("arial.ttf")) {
            return -1;
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (t1.get_root()) {
            t1.calculatePositions(t1.get_root(), 750.0f, 60.0f, 360.0f);  // Ampliado el offset para balancear el nuevo tamaño de los nodos
        }

        window.clear(sf::Color(25, 25, 25));
        drawTreeEdges(window, t1.get_root());
        drawTreeNodes(window, t1.get_root(), font); // fuente cargada para pintar los textos

        window.display();
    }

    return 0;
}
