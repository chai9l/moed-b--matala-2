
#include "FamilyTree.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace family;

//worker function of addFather function.
void Tree::insertFather(family::Node *current, string son, string father) {

    //checks if the given node ptr is not empty, and the tree exists
    if(current == nullptr){
        return;
    }

    //checks if the given son's name matches the current node name, if so go in.
    if(son.compare(current->name)==0) {
        //checks if the current node we're looking at have a father.
        if(current->father != nullptr) {
            cout << "ERROR!, father already exists.\n";
            return;
        }
        //if there's no father creating a new father for the current node.
        else{
           Node* newNode = new Node(father);
           newNode->gender = 1; //declaring gender equals 1(male)
           root->sizeRight++; // adding to the right subtree size.
           current->father = newNode; //connecting the new node we created.
           current->father->relation = Tree::initRelation(father); //initializing relations.
           return;
        }
    }
    //traverse the tree via recursion and find the desired node via name given in argument.
    this->insertFather(current->father,son,father);
    this->insertFather(current->mother,son,father);
}

//Manager function, used to match demo.cpp, also looks clean.
Tree Tree::addFather(string son, string father) {
    Node* current = root;
    this->insertFather(current,son,father); //calling to the worker func explained above.
    return *this; //returning a ptr because the function it self return type is of "tree"
}

//Worker function of addMother function.
void Tree::insertMother(family::Node *current, string son, string mother) {

    //checking if the current node given via arguments actually exists
    if(current == nullptr) {
        return;
    }

    //compares the given son name via argument with the node we're currently looking at.
    if(son.compare(current->name)==0){

        //checks if the current node we're looking at has a mother.
        if(current->mother != nullptr) {
            cout << "Error!, mother is already exist!\n";
            return;
        }

        //if there's no mother node, creating a new mother node for the given current node.
        else {
            Node *newNode = new Node(mother);
            newNode->gender = 2;
            root->sizeLeft++;
            current->mother = newNode;
            current->mother->relation = Tree::initRelation(mother);
            return;
        }
    }
    //tree traverse via recursion, checking names both left and right until desired name is found.
    this->insertMother(current->mother,son,mother);
    this->insertMother(current->father,son,mother);
}

//Manager function of insertMother.
Tree Tree::addMother(string son, string mother) {
    Node*current = root;
    this->insertMother(current,son,mother);
    return *this;
}

//Worker function of display.
void Tree::displayPrint(family::Node *root, int space) {
    //checks that given root actually exists.
    //also works as an ending to the recursion used here.
    if(root == NULL)
        return;

    //adjusting amount of spaces each call.
    space += 10;

    //Tree traverse via recursion to the left.
    displayPrint(root->father,space);
    cout << endl;

    //amount of spaces before printing the name, used to display the tree as a tree VISUALLY.
    for(int i = 10; i < space; i++)
        cout<<" ";
    cout<<root->name<<endl; //name output.

    //Tree traverse via recursion to the right.
    displayPrint(root->mother,space);

}

//Manager function to displayPrint.
void Tree::display() {
    Tree::displayPrint(root, 0);
    cout << endl;
}

//Creating a string describing the relation between a given node and another node that has name like the in
//the given string.
//using recursion calls to traverse the tree, each call add one to the count for each level we go down
//then we're using count to describe the relation between given node and and given name.
//Also creating a node relation.
string Tree::createRelation(family::Node *current, string name, int count) {

    static string res = "";

    //checking if the node given by the node ptr as an argument exists
    if(current == NULL)
        return res;

    //checks if we're looking at the right node given to us via argument.
    if(name.compare(current->name) == 0) {
        //count <= 2 means the related family that is not great-xxxx.
        if((count >= 0) && (count <= 2)) {
            res = "";
            if (count == 0)
                res += "me";

            if ((count == 1) && (current->gender == 2))
                res += "mother";

            if ((count == 1) && (current->gender == 1))
                res += "father";

            if ((count == 2) && (current->gender == 2))
                res += "grandmother";

            if ((count == 2) && (current->gender == 1))
                res += "grandfather";
            current->relation = res;
            return res;
        }
        //if the count is greater or equal to 3 it means we're looking for a relation that has great-.. in it.
        else {
            res = "";
            for (int i = 3; i <= count; i++)
                res += "great-";

            if (current->gender == 2)
                res += "grandmother";

            if (current->gender == 1)
                res += "grandfather";

            current->relation = res;
            return res;
        }
    }
        count++;
        createRelation(current->father,name,count);
        createRelation(current->mother,name,count);
        return res;
}

//Boolean function to check if a given name exists in the tree.
bool Tree::checkName(family::Node *current, string name) {

        if(current == NULL)
            return false;

        if(name.compare(current->name) == 0)
            return true;

        //recursive calls to traverse the tree to check if the name exists
        bool res1 = checkName(current->father,name);
        if(res1)
            return true;
        bool res2 = checkName(current->mother,name);
            return res2;
}

//Manager worker, it uses check name on the given string via argument.
//if the name exists in the tree we're using our worker relation func to create the relation.
//this function works when we're adding a new node via addFather, addMother.
string Tree::initRelation(string name) {
    int count = 0;
    Node* current = root;
    if(Tree::checkName(current,name)) {
        string result = createRelation(current, name, count);
        return result;
    }
    //if the name cant be found inside the tree, we're printing Unrelated.
    else{
        return "Unrelated";
    }
}

//Worker function that get a node ptr and a name via string,
//the function creates a new string and whenever we find a node that matches the given string
//we're copying its relation and returning it.
string Tree::findRelation(family::Node *current, string name) {
    static string find = "";
    if(current == NULL)
        return find;

    if(name.compare(current->name) == 0) {
        find = "";
        find += current->relation;
    }

    findRelation(current->father,name);
    findRelation(current->mother,name);
    return find;
}

//Manager function that uses check name to check if the given name exists in the family tree
//and then uses its worker function findrelation to copy the desired relation from the node that matches
//the given string's name.
string Tree::relation(string name) {
    Node* current = root;
    if(Tree::checkName(current,name)){
        string result = findRelation(current,name);
        return result;}
    else {
        return "Undefined";
    }
}

//Worker function, this function find the desired node's name
//we're providing a node ptr to the root and a string describing the RELATION.
string Tree::findName(family::Node *current, string name) {
    static string fname = "";
    if(current == NULL)
        return fname;

    if((current->relation).compare(name) == 0) {
        fname = "";
        fname += current->name;
        return fname;
    }
    findName(current->father,name);
    findName(current->mother,name);
    return fname;
}

//Bool function to check if the given relation actually exists in the tree given by the node ptr.
bool Tree::checkRelation(family::Node *current, string name) {
    if(current == NULL)
        return false;

    if(name.compare(current->relation) == 0)
        return true;

    bool res1 = checkRelation(current->father,name);
    if(res1)
        return true;
    bool res2 = checkRelation(current->mother,name);
    return res2;
}

//Manager function of checkRelation and findName.
//this function takes a string describing relation, checks if it exists via checkRelation
//if it does it create a new string that copies the name of the node that answers the relation given
//in the argument, if it doesnt it returns undefined.
string Tree::find(string name) {
    Node* current = root;
    if(Tree::checkRelation(current,name)){
    string result = findName(current,name);
    return result;}
    else {
        return "Undefined";
    }
}

//worker function that takes the tree's root and a string describing a name.
//this function traverse the tree via recursion until it finds a node that match the name given via argument
//when the desired node is found the function sets it to null, it also checks the current node's father
//and mother.
void Tree::removeFamily(family::Node *current, string name) {
    if(current == NULL)
        return;

    if(name.compare(root->name) == 0) {
        root = NULL;
        return;
    }
    if(name.compare(current->father->name) == 0) {
        current->father = NULL;
        return;
    }
    if(name.compare(current->mother->name) == 0) {
        current->mother = NULL;
        return;
    }
    if(current->father != NULL) {
        removeFamily(current->father, name);
    }
    else if(current->mother != NULL) {
        removeFamily(current->mother, name);
    }else {
        return;
    }
}

//Manager function that takes a name via argument
//it checks if the given name exists in the tree, if it does it calls removeFamily function to delete
//the matched node and the subtree under it.
void Tree::remove(string name) {
    Node *current = root;
    if(Tree::checkName(current,name)) {
        Tree::removeFamily(current,name);
    }
    else {
        cout<< "Didn't find the specified name \n";
    }
}
