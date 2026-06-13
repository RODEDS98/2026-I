#include <SFML/Graphics.hpp>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;


struct AVLNode {
    int key;
    int h;
    AVLNode* ch[2]; // ch[0] = izquierdo, ch[1] = derecho
    
 
    float posX, posY;

    AVLNode(int v) {
        key = v;
        h = 1;
        ch[0] = ch[1] = nullptr;
        posX = posY = 0.0f;
    }
};

class CAVLTree {
private:
    AVLNode* treeRoot;

    int nodeHeight(AVLNode* n) { 
        return n ? n->h : 0; 
    }

    void recalculateHeight(AVLNode* n) {
        if (n) n->h = 1 + max(nodeHeight(n->ch[0]), nodeHeight(n->ch[1]));
    }

    AVLNode* executeRotation(AVLNode* x, int side) {
        int opposite = 1 - side;
        AVLNode* y = x->ch[opposite];
        x->ch[opposite] = y->ch[side];
        y->ch[side] = x;
        recalculateHeight(x);
        recalculateHeight(y);
        return y;
    }

    AVLNode* rebalanceNode(AVLNode* n) {
        if (!n) return nullptr;
        recalculateHeight(n);
        int balance = fetchBalance(n);

        if (balance > 1) {
            if (fetchBalance(n->ch[1]) < 0) n->ch[1] = executeRotation(n->ch[1], 1);
            return executeRotation(n, 0);
        }
        if (balance < -1) {
            if (fetchBalance(n->ch[0]) > 0) n->ch[0] = executeRotation(n->ch[0], 0);
            return executeRotation(n, 1);
        }
        return n;
    }

    AVLNode* insertValue(AVLNode* n, int val) {
        if (!n) return new AVLNode(val);
        if (val < n->key) n->ch[0] = insertValue(n->ch[0], val);
        else if (val > n->key) n->ch[1] = insertValue(n->ch[1], val);
        return rebalanceNode(n);
    }

    bool executeLeafPruning(AVLNode*& n) {
        if (!n) return false;

        // find hoja
        if (!n->ch[0] && !n->ch[1]) {
            delete n;
            n = nullptr;
            return true;
        }

        int currentBF = fetchBalance(n);
        int branchTarget = 0;

        // camino
        if (currentBF < 0) {
            branchTarget = 0;
        } else if (currentBF > 0) {
            branchTarget = 1;
        } else {
            // Si el balance es cero, decide basándose en qué rama tiene nodos reales
            if (nodeHeight(n->ch[1]) >= nodeHeight(n->ch[0])) {
                branchTarget = 1;
            } else {
                branchTarget = 0;
            }
        }

        // evita rama vacia
        if (!n->ch[branchTarget]) {
            branchTarget = 1 - branchTarget;
        }

        bool state = executeLeafPruning(n->ch[branchTarget]);
        if (state) {
            n = rebalanceNode(n);
        }
        return state;
    }

public:
    CAVLTree() { treeRoot = nullptr; }

    AVLNode* getRootPointer() { return treeRoot; }

    int fetchBalance(AVLNode* n) {
        return n ? nodeHeight(n->ch[1]) - nodeHeight(n->ch[0]) : 0;
    }

    void addMultiple(initializer_list<int> list) {
        for (int element : list) treeRoot = insertValue(treeRoot, element);
    }

    bool verifyZeroBalanceTotal(AVLNode* n) {
        if (!n) return true;
        if (fetchBalance(n) != 0) return false;
        return verifyZeroBalanceTotal(n->ch[0]) && verifyZeroBalanceTotal(n->ch[1]);
    }

    bool isTreeSymmetric() {
        if (!treeRoot) return true;
        return verifyZeroBalanceTotal(treeRoot);
    }

    void processSinglePrune() {
        if (treeRoot && !isTreeSymmetric()) {
            executeLeafPruning(treeRoot);
        }
    }

    void setupSpatialLayout(AVLNode* p, float currentX, float currentY, float gapX) {
        if (!p) return;
        p->posX = currentX;
        p->posY = currentY;
        setupSpatialLayout(p->ch[0], currentX - gapX, currentY + 85.0f, gapX * 0.5f);
        setupSpatialLayout(p->ch[1], currentX + gapX, currentY + 85.0f, gapX * 0.5f);
    }
};

// conexiones 
void renderTreeLines(sf::RenderWindow& display, AVLNode* root) {
    if (!root) return;
    for (int i = 0; i < 2; ++i) {
        if (root->ch[i]) {
            sf::Vertex link[] = {
                sf::Vertex(sf::Vector2f(root->posX, root->posY), sf::Color(60, 64, 73)),
                sf::Vertex(sf::Vector2f(root->ch[i]->posX, root->ch[i]->posY), sf::Color(60, 64, 73))
            };
            display.draw(link, 2, sf::Lines);
            renderTreeLines(display, root->ch[i]);
        }
    }
}


void renderTreeGraph(sf::RenderWindow& display, AVLNode* root, sf::Font& textFont, CAVLTree& logicRef) {
    if (!root) return;

    float nodeRadius = 20.0f;
    sf::CircleShape geometryNode(nodeRadius);
    geometryNode.setOrigin(nodeRadius, nodeRadius);
    geometryNode.setPosition(root->posX, root->posY);
    
    geometryNode.setFillColor(sf::Color(0, 168, 204)); 
    geometryNode.setOutlineThickness(3.0f);
    geometryNode.setOutlineColor(sf::Color(20, 40, 80));
    display.draw(geometryNode);

    // numero entral 
    sf::Text mainValueText;
    mainValueText.setFont(textFont);
    mainValueText.setString(to_string(root->key));
    mainValueText.setCharacterSize(15);
    mainValueText.setFillColor(sf::Color::Black); // Cambiado a negro
    mainValueText.setStyle(sf::Text::Bold);
    
    sf::FloatRect bounds = mainValueText.getLocalBounds();
    mainValueText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    mainValueText.setPosition(root->posX, root->posY);
    display.draw(mainValueText);

    //  Balanceo
    int balanceValue = logicRef.fetchBalance(root);
    string balanceString = (balanceValue > 0) ? "+" + to_string(balanceValue) : to_string(balanceValue);

    sf::Text factorIndicator;
    factorIndicator.setFont(textFont);
    factorIndicator.setString(balanceString);
    factorIndicator.setCharacterSize(13);
    factorIndicator.setFillColor(sf::Color(225, 95, 65)); // Color Coral / Naranja llamativo
    factorIndicator.setStyle(sf::Text::Bold);
    
    // Posicionado la derecha
    factorIndicator.setPosition(root->posX + nodeRadius + 4.0f, root->posY - nodeRadius - 8.0f);
    display.draw(factorIndicator);

    // Recursión de graficado
    renderTreeGraph(display, root->ch[0], textFont, logicRef);
    renderTreeGraph(display, root->ch[1], textFont, logicRef);
}

int main() {
    CAVLTree myTree;
    myTree.addMultiple({ 22, 18, 28, 9, 16, 30, 6 });

    sf::RenderWindow viewWindow(sf::VideoMode(1000, 650), "Dashboard - Balanceo Simetrico AVL");
    viewWindow.setFramerateLimit(60);

    sf::Font standardFont;
    if (!standardFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        if (!standardFont.loadFromFile("arial.ttf")) {
            std::cout << "Error critico cargando archivo tipografico." << std::endl;
            return -1;
        }
    }

    sf::Text interfaceLabel;
    interfaceLabel.setFont(standardFont);
    interfaceLabel.setCharacterSize(16);
    interfaceLabel.setPosition(25.0f, 25.0f);
    interfaceLabel.setStyle(sf::Text::Italic);

    while (viewWindow.isOpen()) {
        sf::Event currentEvent;
        while (viewWindow.pollEvent(currentEvent)) {
            if (currentEvent.type == sf::Event::Closed)
                viewWindow.close();

            // CLICK IZQUIERDO DEL MOUSE
            if (currentEvent.type == sf::Event::MouseButtonPressed) {
                if (currentEvent.mouseButton.button == sf::Mouse::Left) {
                    myTree.processSinglePrune();
                }
            }
        }

        if (myTree.getRootPointer()) {
            myTree.setupSpatialLayout(myTree.getRootPointer(), 500.0f, 110.0f, 230.0f);
        }

     
        if (!myTree.getRootPointer()) {
            interfaceLabel.setString("Estado: Estructura vacia.");
            interfaceLabel.setFillColor(sf::Color(180, 50, 50));
        } else if (myTree.isTreeSymmetric()) {
            interfaceLabel.setString("Estado: Estructura simetrica alcanzada (Balances = 0).");
            interfaceLabel.setFillColor(sf::Color(30, 130, 70));
        } else {
            interfaceLabel.setString("Instruccion: Haz CLICK IZQUIERDO en la pantalla para podar una hoja.");
            interfaceLabel.setFillColor(sf::Color(60, 64, 73));
        }

    
        viewWindow.clear(sf::Color(240, 242, 245)); 

        // Dibujar en orden jerárquico
        viewWindow.draw(interfaceLabel);
        renderTreeLines(viewWindow, myTree.getRootPointer());
        renderTreeGraph(viewWindow, myTree.getRootPointer(), standardFont, myTree);

        viewWindow.display();
    }

    return 0;
}
