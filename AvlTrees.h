//
// Created by gigib on 02/05/2023.
//

#ifndef MIVNEWET1_AVLTREES_H
#define MIVNEWET1_AVLTREES_H
#include <iostream>
#include "wet1util.h"



typedef enum {
    AVL_SUCCESS,
    AVL_NODE_ALREADY_EXISTS,
    AVL_NODE_NO_EXIST,
    AVL_NULL_ARGUMENT,
    AVL_NO_ALLOCATION,
} AVLResults;


template <class T>
class Node {
    int key;
    T element;
    int height;
    Node* father;
    Node* left_son;
    Node* right_son;
public:
    explicit Node(int key = -1, T element = nullptr, int height = 0, Node* father = nullptr, Node* left_son = nullptr,
         Node* right_son = nullptr);
    ~Node();
    void SetKey(int key);
    int GetKey() const;
    void SetKey(Node<T>* node);
    void SetElement(Node<T>* node);
    T& GetElement();
    void SetHeight(int new_height);
    int GetHeight();
    void SetNodeLeft(Node* left_son);
    Node* GetNodeLeft();
    void SetNodeRight(Node* right_son);
    Node* GetNodeRight();
    void SetFatherNode(Node* father);
    Node* GetFatherNode();
    int GetBalancedFactor();
    //int getHeight();
    Node* Get_Following_node();
    int SetNewHeight();
    Node* BuildAvlSubtree(int height_needed);
    Node<T>* GetPreviousNode();
};

template <class T>
class Avl_tree {
private:
    Node<T>* root;
    //Node<T>* CopyNodes(Node<T>* node);

public:
    Avl_tree();

    explicit Avl_tree(Node<T>* root);

    ~Avl_tree();

    void AuxDistructorTree(Node<T>* node);

    Node<T>* GetRoot();

    void SetRoot( Node<T>* new_root);

    Node<T>* FindNode(Node<T>* root, int key) const;

    Node<T>* FindNode(Node<T>* root, int key, int player_id);

    //findnode (root,key,grade,view)

    int InorderVisit(Node<T>* node, int* array, int i);

    int CountNodesOfTree(Node<T>* root);

    AVLResults InsertNode(int key, T& element, Node<T>* node_added);

    AVLResults InsertNode(Node<T>* node);

    AVLResults InsertNode(int key, T& element, int PlayerID, Node<T>* added_node);

    void Fix_BF_after_insert(Node<T>* check);

    AVLResults RemoveNode(int key);

    AVLResults RemoveNode(int key, int PlayerID);

    AVLResults Remove_Node_Leaf(Node<T>* node);

    AVLResults Remove_Node_With_Only_Child (Node<T>* node);

    void Swap(Node<T>* node_1, Node<T>* node_2);

    AVLResults RotateLL(Node<T>* node);

    AVLResults RotateLR(Node<T>* node);

    AVLResults RotateRL(Node<T>* node);

    AVLResults RotateRR(Node<T>* node);

 //   Node<T>* Get_smallest_node();

    Node<T>* Get_biggest_node();

    void ReverseInorder(Node<T>* node, int* i);

    void Inorder(Node<T>* node, Node<T>** array, int size);

    Node<T>* ReplaceNodeByAnother(Node<T>* last, Node<T>* new_node);
};



template <class T>
Node<T>::Node(int key, T element, int height, Node* father, Node* left_son, Node* right_son) :
        key(key), element(element), height(height), father(father), left_son(left_son), right_son(right_son) {}

template <class T>
Node<T>::~Node()
{
    delete element;
}

template <class T>
void Node<T>::SetKey(int key_to_set)
{
    key = key_to_set;
}

template <class T>
int Node<T>::GetKey() const
{
    return key;
}

template <class T>
T& Node<T>::GetElement()
{
    return element;
}

template <class T>
void Node<T>::SetHeight(int new_height)
{
    height = new_height;
}

template <class T>
int Node<T>::GetHeight()
{
    return height;
}
template <class T>
void Node<T>::SetKey(Node<T>* node)
{
    key = node->GetKey();
}

template <class T>
void Node<T>::SetElement(Node<T>* node)
{
    element = node->GetElement();
}

template <class T>
void Node<T>::SetNodeLeft(Node* left_son_to_set)
{
    left_son = left_son_to_set;
}

template <class T>
Node<T>* Node<T>::GetNodeLeft()
{
    return left_son;
}

template <class T>
void Node<T>::SetNodeRight(Node* right_son_to_set)
{
    right_son = right_son_to_set;
}

template <class T>
Node<T>* Node<T>::GetNodeRight()
{
    return right_son;
}

template <class T>
void Node<T>::SetFatherNode(Node* father_to_set)
{
    father = father_to_set;
}

template <class T>
Node<T>* Node<T>::GetFatherNode()
{
    return father;
}

template <class T>
int Node<T>::GetBalancedFactor() {
    int height_left=-1;
    if (left_son!= nullptr){
        height_left=left_son->GetHeight();
    }

    int height_right=-1;
    if (right_son!= nullptr){
        height_right= right_son->getHeight();
    }
    return (height_left-height_right);
}

template <class T>
Node<T>* Node<T>::Get_Following_node(){
    //case1 no father
    Node<T>* following_node;
    if(father== nullptr){
        if (right_son== nullptr){
            return nullptr;
        }
        following_node=right_son;
        while (true) {
            if (following_node->left_son == nullptr) //smallest after him
                break;
            following_node = following_node->left_son;
        }
        return following_node;
    }
    else{    //case2 there is a father

        if ( right_son != nullptr){
            following_node=right_son;
            while (true) {
                if (following_node->left_son == nullptr) //smallest after him
                    break;
                following_node = following_node->left_son;
            }
            return following_node;
        }
        else {
            //There's no right son but there's a father
            if (father->left_son == this) //node if a left son
            {
                return father;
            }
            else if (father->right_son == this) //right son
            {
                Node<T> *grandfather = father->father;

                while (true) {
                    if (grandfather == nullptr) {
                        return nullptr;
                    }

                    if (grandfather->left_son == father) {
                        return grandfather;
                    }

                    if (grandfather->left_son != father) {
                        grandfather = grandfather->father;
                        father = father->father;
                    }
                }
            }
        }
    }
    return nullptr;
}


template <class T>
int Node<T>::SetNewHeight(){
    if (this == nullptr)
        return -1;

    int previous_height = this->GetHeight();

    int height_right=-1;
    int height_left=-1;
    if(this->GetNodeRight()!=nullptr)
        height_right=this->GetNodeRight()->GetHeight();
    if(this->GetNodeLeft()!=nullptr)
        height_left=this->GetNodeLeft()->GetHeight();

    int new_height= std::max(height_right, height_left)+1;
    this->SetHeight(new_height);

    if(previous_height == this->GetHeight()) //if there wasnt any change
        return 0;
    return 1; //we changed it
}


template <class T>
Node<T>* Node<T>::BuildAvlSubtree(int height_needed){

    if (height_needed <= 0)
        return nullptr;

    auto* new_node = new Node<T>();
    new_node->left_son = BuildAvlSubtree(height_needed-1);
    new_node->right_son = BuildAvlSubtree(height_needed-1);
    return new_node;
}



template <class T>
Node<T>* Node<T>::GetPreviousNode(){
    Node<T> *following;
    if (father == nullptr) {
        if (left_son == nullptr) //there's no smallest after him and there's no father
        {
            return nullptr;
        }

        following = left_son; //smallest

        while (true) {
            if (following->right_son == nullptr) //smallest after him
                break;
            following = following->right_son;
        }
        return following;
    }

    else  //there's a father
    {
        if (left_son != nullptr) //there's a left son
        {
            following = left_son;

            while (true) {
                if (following->right_son == nullptr) //smallest after him
                    break;
                following = following->right_son;
            }
            return following;
        }
        else {//There's no left son but there's a father
            if (father->right_son == this) //node is a right son
            {
                return father;
            }
            else if (father->left_son == this) //left son
            {
                Node<T> *grandfather = father->father;

                while (true) {
                    if (grandfather == nullptr)
                        return nullptr;

                    if (grandfather->right_son == father) {
                        return grandfather;
                    }

                    if (grandfather->right_son != father) {
                        grandfather = grandfather->father;
                        father = father->father;
                    }
                }
            }
        }
    }
    return nullptr;
}

//--------------------------------AVL TREES--------------------------------------------


template <class T>
Avl_tree<T>::Avl_tree(): root(nullptr) {}

template <class T>
Avl_tree<T>::Avl_tree(Node<T>* root) : root(root) {}

template <class T>
Avl_tree<T>::~Avl_tree() = default;


template <class T>
void Avl_tree<T>::SetRoot( Node<T>* new_root)
{
    this->root = new_root;
}


template <class T>
Node<T>* Avl_tree<T>::FindNode(Node<T>* given_root, int key_to_find) const{
    if (root == nullptr)
    {
        return nullptr;
    }
    if(given_root == nullptr)
    {
        return nullptr;
    }

    Node<T>* node_to_return;
    int current_key= given_root->GetKey();
    if(key_to_find==current_key) {
        node_to_return = given_root ;
        return node_to_return;
    }
    while (key_to_find!=current_key && node_to_return != nullptr){
        if(key_to_find<current_key){
            node_to_return=node_to_return->GetNodeLeft();
            current_key=node_to_return->GetKey();
        }
        else {
            node_to_return=node_to_return->GetNodeRight();
            current_key=node_to_return->GetKey();
        }
    }
    return node_to_return;
}

template <class T>
AVLResults Avl_tree<T>::InsertNode(Node<T>* node){

    //rajouter les cas ou le AVL fail

    if (root== nullptr){
        node->SetHeight(0);
        node->SetFatherNode(nullptr);
        node->SetNodeLeft(nullptr);
        node->SetNodeRight(nullptr);
        root = node;
        return AVL_SUCCESS;
    }
    Node<T>* current_node=root;
    while (current_node!= nullptr){
        if(current_node->GetKey()<node->GetKey()){
            if (current_node->GetNodeRight()== nullptr){
                break;
            }
            current_node=current_node->GetNodeRight();
            continue;
        }
        else{
            if (current_node->GetNodeLeft()== nullptr){
                break;
            }
            current_node=current_node->GetNodeLeft();
            continue;
        }
    }
    if(current_node->GetKey()<node->GetKey()) {
        current_node->SetNodeRight(node);
    }
    if(current_node->GetKey()>node->GetKey()) {
        current_node->SetNodeLeft(node);
    }

    node->SetHeight(0);
    node->SetFatherNode(current_node);
    node->SetNodeLeft(nullptr);
    node->SetNodeRight(nullptr);

    //update height of the tree before BF
    Node<T>* temp = node;
    while (temp->GetFatherNode() != nullptr)
    {
        temp->GetFatherNode()->SetNewHeight();
        temp = temp->GetFatherNode();
    }

    // time to check the BF
    Node<T>* node_to_balance = node;
    int BF;
    while (node_to_balance!= nullptr){
        BF=node_to_balance->GetBalancedFactor();
        if(BF==2 || BF==-2){
            Fix_BF_after_insert(current_node);//current node is the father of node_to_balance
        }
        node_to_balance=node_to_balance->GetFatherNode();
        current_node=current_node->GetFatherNode();
    }

    //update height of the tree after BF
    temp = node;
    while (temp->GetFatherNode() != nullptr)
    {
        temp->GetFatherNode()->SetNewHeight();
        temp = temp->GetFatherNode();
    }
    return AVL_SUCCESS;
}



template <class T>
AVLResults Avl_tree<T>::Remove_Node_Leaf(Node<T> *node) {

}








#endif //MIVNEWET1_AVLTREES_H
