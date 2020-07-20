#ifndef ANCESTOR_TREE_A_MASTER_FAMILYTREE_HPP
#define ANCESTOR_TREE_A_MASTER_FAMILYTREE_HPP

#include <string>
using namespace std;

namespace family {

    class Node {
    public:
            string name;
            string relation;
            int gender;
            int sizeRight, sizeLeft;
            Node *father;
            Node *mother;
            //a Node constructor
            Node(string data) {
                this->name = data;
                this->mother = nullptr;
                this->father = nullptr;
            }
    };

    class Tree {
    public:
        //create a new tree & insert root
        Node* root;
        Tree(string rootName) {
            Node* newNode = new Node(rootName);
            this->root = newNode;
            this->root->relation = initRelation(rootName);
        }
        Tree addFather(string son, string father);
        Tree addMother(string son, string mother);
        void display();
        void remove(string name);
        string relation(string name);
        string find(string name);
    private:
        //New Nodes
        void insertFather(Node* root, string son, string father); //Worker function of addFather
        void insertMother(Node* root, string son, string mother); //Worker function of addMother
        string initRelation(string name);//Worker function that manages createRelation
        string createRelation(Node* current, string name, int count); //worker function that creates a relation.

        //Display
        void displayPrint(Node* root, int count); //Worker function of display.
        //Removal
        void removeFamily(Node* current, string name); //Worker function of remove.
        //Search
        string findRelation(Node* current, string name);//worker function that find relation.
        string findName(Node* current,string name);//worker function that finds a name.
        //Boolean checks
        bool checkName(Node* current, string name); //Overall function that checks if the name exists
        bool checkRelation(Node* current, string name); //Overall function that checks if a relation exists
    };
}
#endif //ANCESTOR_TREE_A_MASTER_FAMILYTREE_HPP
