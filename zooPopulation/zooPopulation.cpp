// Name: Gavyn Sanbrano
// Class: CIT 66
// Module 04 Activity
// Description: Reads animal data from a file, stores it in objects,
// and outputs a report of animals and species counts.
// This program reads animal data from a file and creates Animal objects.
// I experimented with different data structures including a vector, map,
// and linked lists. I originally used a vector to store all animals,
// but in this version I use linked lists to create a separate list for
// each species. A map is still used to count how many animals there are
// for each species.

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

// Base class
class Animal {
private:
    string name;
    int age;
    string species;

public:
    Animal(string n, int a, string s) {
        name = n;
        age = a;
        species = s;
    }

    string getName() { return name; }
    int getAge() { return age; }
    string getSpecies() { return species; }

    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setSpecies(string s) { species = s; }

    // Virtual function (polymorphism)
    virtual void makeSound() {
        cout << "Animal sound" << endl;
    }
};

// Subclasses
class Hyena : public Animal {
public:
    Hyena(string n, int a) : Animal(n, a, "Hyena") {}
};

class Lion : public Animal {
public:
    Lion(string n, int a) : Animal(n, a, "Lion") {}
};

class Tiger : public Animal {
public:
    Tiger(string n, int a) : Animal(n, a, "Tiger") {}
};

class Bear : public Animal {
public:
    Bear(string n, int a) : Animal(n, a, "Bear") {}
};

// Node structure for linked list
// Each node stores one animal and points to the next node
struct Node {
    Animal* animal;
    Node* next;
};

// Function to add a node to the linked list
void addNode(Node*& head, Animal* animal) {
    Node* newNode = new Node;
    newNode->animal = animal;
    newNode->next = head;
    head = newNode;
}

// Function to print a linked list
void printList(Node* head, ofstream& outFile) {
    Node* current = head;
    while (current != nullptr) {
        outFile << current->animal->getSpecies() << " - "
                << current->animal->getName() << " - Age: "
                << current->animal->getAge() << endl;
        current = current->next;
    }
}

int main() {

    // Separate linked lists for each species
    // This replaces the vector used in the previous version
    Node* lionHead = nullptr;
    Node* tigerHead = nullptr;
    Node* hyenaHead = nullptr;
    Node* bearHead = nullptr;

    // Map used to count how many animals belong to each species
    map<string, int> speciesCount;

    ifstream inFile("../arrivingAnimals.txt");
    ofstream outFile("newAnimals.txt");

    if (!inFile) {
        cout << "Error opening input file." << endl;
        return 1;
    }

    string species, name;
    int age;

    // Read file line by line and create animal objects
    // Each animal is added to its species-specific linked list
    while (inFile >> species >> name >> age) {

        if (species == "Lion") {
            addNode(lionHead, new Lion(name, age));
        }
        else if (species == "Tiger") {
            addNode(tigerHead, new Tiger(name, age));
        }
        else if (species == "Hyena") {
            addNode(hyenaHead, new Hyena(name, age));
        }
        else if (species == "Bear") {
            addNode(bearHead, new Bear(name, age));
        }

        speciesCount[species]++;
    }

    // Write report to file
    outFile << "New Animal Report\n\n";

    outFile << "Lions:\n";
    printList(lionHead, outFile);

    outFile << "\nTigers:\n";
    printList(tigerHead, outFile);

    outFile << "\nHyenas:\n";
    printList(hyenaHead, outFile);

    outFile << "\nBears:\n";
    printList(bearHead, outFile);

    outFile << "\nTotal Animals by Species:\n";
    for (auto pair : speciesCount) {
        outFile << pair.first << ": " << pair.second << endl;
    }

    inFile.close();
    outFile.close();

    cout << "Report created in newAnimals.txt" << endl;

    return 0;
}