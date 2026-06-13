#include <SFML/Graphics.hpp>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct CustomNode {
    int data;
    CustomNode* links[3]; 
    bool is_charred;      
    float px, py;         

    CustomNode(int v, CustomNode* p = nullptr) {
        data = v;
        links[0] = links[1] = nullptr;
        links[2] = p; // Asignación directa del padre
        is_charred = false;
        px = py = 0.0f;
    }
};

class BurnTreeSimulation {
private:
    CustomNode* treeRoot;
    queue<CustomNode*> fireQueue; // Cola activa de propagación
    int timeStep;                 // Contador de momentos/minutos
    bool simulationStarted;

public:
    BurnTreeSimulation() {
        treeRoot = nullptr;
        timeStep = 0;
        simulationStarted = false;
    }

    bool append(int x) {
        if (!treeRoot) {
            treeRoot = new CustomNode(x);
            return true;
        }
        CustomNode* current = treeRoot;
        while (true) {
            if (x == current->data) return false;
            int path = (x > current->data); // 0 si es menor, 1 si es mayor
            if (!current->links[path]) {
                current->links[path] = new CustomNode(x, current);
                return true;
            }
            current = current->links[path];
        }
    }

    void buildFromList(initializer_list<int> set) {
        for (int x : set) append(x);
    }

    CustomNode* fetchRoot() { return treeRoot; }

    CustomNode* locate(int x) {
        CustomNode* current = treeRoot;
        while (current) {
            if (current->data == x) return current;
            current = current->links[x > current->data];
        }
        return nullptr;
    }

    // Inicializa el estado del incendio 
    void ignite(int targetValue) {
        CustomNode* target = locate(targetValue);
        if (!target) {
            cout << "Error: El objetivo inicial no existe en el arbol." << endl;
            return;
        }
        
        // Limpiamos colas anteriores 
        while (!fireQueue.empty()) fireQueue.pop();
        
        target->is_charred = true;
        fireQueue.push(target);
        timeStep = 1;
        simulationStarted = true;

        cout << "Momento 1 (Ignicion): " << target->data << endl;
    }

    // Avanza una etapa
    void advanceFireStage() {
        if (!simulationStarted || fireQueue.empty()) return;

        int activeNodes = fireQueue.size();
        timeStep++;
        
        cout << "Momento " << timeStep << " : ";

        for (int i = 0; i < activeNodes; ++i) {
            CustomNode* curr = fireQueue.front();
            fireQueue.pop();

            for (int direction = 0; direction < 3; ++direction) {
                CustomNode* neighbor = curr->links[direction];
                if (neighbor && !neighbor->is_charred) {
                    neighbor->is_charred = true;
                    fireQueue.push(neighbor);
                    cout << neighbor->data << " ";
                }
            }
        }
        cout << endl;
    }

    bool isExtinguished() {
        return simulationStarted && fireQueue.empty();
    }

    int getCurrentTime() { return timeStep; }

    void computeLayout(CustomNode* n, float x, float y, float hGap) {
        if (!n) return;
        n->px = x;
        n->py = y;
        computeLayout(n->links[0], x - hGap, y + 80.0f, hGap * 0.5f);
        computeLayout(n->links[1], x + hGap, y + 80.0f, hGap * 0.5f);
    }
};


void drawLayoutLines(sf::RenderWindow& targetWindow, CustomNode* root) {
    if (!root) return;
    for (int i = 0; i < 2; ++i) { // Solo itera 0 y 1 (hijos) para las líneas hacia abajo
        if (root->links[i]) {
            sf::Vertex edge[] = {
                sf::Vertex(sf::Vector2f(root->px, root->py), sf::Color(80, 85, 95)),
                sf::Vertex(sf::Vector2f(root->links[i]->px, root->links[i]->py), sf::Color(80, 85, 95))
            };
            targetWindow.draw(edge, 2, sf::Lines);
            drawLayoutLines(targetWindow, root->links[i]);
        }
    }
}

void drawLayoutNodes(sf::RenderWindow& targetWindow, CustomNode* root, sf::Font& displayFont) {
    if (!root) return;

    float rSize = 20.0f;
    sf::CircleShape token(rSize);
    token.setOrigin(rSize, rSize);
    token.setPosition(root->px, root->py);
    token.setOutlineThickness(2.5f);


    if (root->is_charred) {
        token.setFillColor(sf::Color(235, 77, 75));     // Rojo  
        token.setOutlineColor(sf::Color(255, 121, 63)); // Naranja Alerta
    } else {
        token.setFillColor(sf::Color(223, 228, 234));   // Gris Claro / Plata
        token.setOutlineColor(sf::Color(47, 53, 66));   // Gris Oscuro Metálico
    }
    targetWindow.draw(token);

    // Texto interior
    sf::Text coreText;
    coreText.setFont(displayFont);
    coreText.setString(to_string(root->data));
    coreText.setCharacterSize(15);
    coreText.setFillColor(root->is_charred ? sf::Color::White : sf::Color::Black);
    coreText.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = coreText.getLocalBounds();
    coreText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    coreText.setPosition(root->px, root->py);
    targetWindow.draw(coreText);

    // Recursión hacia los hijos
    drawLayoutNodes(targetWindow, root->links[0], displayFont);
    drawLayoutNodes(targetWindow, root->links[1], displayFont);
}

int main() {
    BurnTreeSimulation sim;
    sim.buildFromList({ 50, 30, 70, 20, 40, 60, 80, 15, 25, 35, 45, 55, 65, 75, 90, 12, 22, 28, 38, 42, 48, 52, 62, 68, 78, 85, 95 });

    int startNode = 40; // Nodo objetivo
    sim.ignite(startNode);

    sf::RenderWindow mainCanvas(sf::VideoMode(1200, 750), "Simulador de Propagacion de Incendios - Estructuras de Datos");
    mainCanvas.setFramerateLimit(60);

    sf::Font standardFont;
    if (!standardFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        if (!standardFont.loadFromFile("arial.ttf")) {
            return -1;
        }
    }

    sf::Text monitorLabel;
    monitorLabel.setFont(standardFont);
    monitorLabel.setCharacterSize(16);
    monitorLabel.setPosition(30.0f, 30.0f);

    while (mainCanvas.isOpen()) {
        sf::Event currentEvent;
        while (mainCanvas.pollEvent(currentEvent)) {
            if (currentEvent.type == sf::Event::Closed)
                mainCanvas.close();

          
            if (currentEvent.type == sf::Event::MouseButtonPressed) {
                if (currentEvent.mouseButton.button == sf::Mouse::Left) {
                    sim.advanceFireStage();
                }
            }
        }

        if (sim.fetchRoot()) {
            sim.computeLayout(sim.fetchRoot(), 600.0f, 100.0f, 290.0f);
        }

     
        if (sim.isExtinguished()) {
            monitorLabel.setString("SIMULACION: El arbol se ha quemado por completo en " + to_string(sim.getCurrentTime()) + " etapas.");
            monitorLabel.setFillColor(sf::Color(255, 100, 100));
        } else {
            monitorLabel.setString("CONTROL: Haz CLICK IZQUIERDO para avanzar al Momento " + to_string(sim.getCurrentTime() + 1));
            monitorLabel.setFillColor(sf::Color::White);
        }

        mainCanvas.clear(sf::Color(43, 47, 53)); 

        mainCanvas.draw(monitorLabel);
        drawLayoutLines(mainCanvas, sim.fetchRoot());
        drawLayoutNodes(mainCanvas, sim.fetchRoot(), standardFont);

        mainCanvas.display();
    }

    return 0;
}
