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
    //Node<T>* biggestNodes;
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

    void Check_And_Fix_BF(Node<T>* check);

    AVLResults RemoveNode(int key);

    AVLResults RemoveNode(int key, int PlayerID);

    AVLResults Remove_Node_Leaf(Node<T>* node);

    AVLResults Remove_Node_With_Only_Child (Node<T>* node);

    void Swap(Node<T>* node_1, Node<T>* node_2);

    AVLResults RotateLL(Node<T>* B_node);

    AVLResults RotateLR(Node<T>* node);

    AVLResults RotateRL(Node<T>* node);

    AVLResults RotateRR(Node<T>* node);

 //   Node<T>* Get_smallest_node();

    Node<T>* Get_biggest_node();

    void ReverseInorder(Node<T>* node, int* i);

    void Inorder(Node<T>* node, Node<T>** array, int size);

   // Node<T>* ReplaceNodeByAnother(Node<T>* last, Node<T>* new_node);
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
    //case1 no father//
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
Node<T>* Node<T>::BuildAvlSubtree(int height_needed){///??

    if (height_needed <= 0)
        return nullptr;

    auto* new_node = new Node<T>();
    new_node->left_son = BuildAvlSubtree(height_needed-1);
    new_node->right_son = BuildAvlSubtree(height_needed-1);
    return new_node;
}



template <class T>
Node<T>* Node<T>::GetPreviousNode(){///needed???
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
    node->SetNodeLeft(nullptr);
    node->SetNodeRight(nullptr);
    node->SetHeight(0);
    if (root== nullptr){
        node->SetFatherNode(nullptr);
        root = node;
        return AVL_SUCCESS;
    }
    Node<T>* current_node=root;
    while (current_node!= nullptr){
        if(current_node->GetKey() < node->GetKey()){
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
    if(current_node->GetKey() < node->GetKey()) {
        current_node->SetNodeRight(node);
    }
    if(current_node->GetKey() > node->GetKey()) {
        current_node->SetNodeLeft(node);
    }
    node->SetFatherNode(current_node);
    // time to check the BF
    this->Check_And_Fix_BF(node);
    return AVL_SUCCESS;
    }


template <class T>
AVLResults Avl_tree<T>::RemoveNode(int key_to_remove) {

    if (key_to_remove<0)
        return AVL_NULL_ARGUMENT;

    Node<T>* node_to_remove= FindNode(root, key_to_remove);
    if (node_to_remove== nullptr)
        return AVL_NODE_NO_EXIST;

    if (node_to_remove->GetNodeRight()== nullptr && node_to_remove->GetNodeLeft()== nullptr)
        return this->Remove_Node_Leaf(node_to_remove);

    else if (node_to_remove->GetNodeRight()== nullptr || node_to_remove->GetNodeLeft()== nullptr)
        return this->Remove_Node_With_Only_Child(node_to_remove);

    //The node has 2 children, we look for the "following" node and we swap them
    //then we delete the node to remove
    Node<T>* following_node= node_to_remove->Get_Following_node();
    /*there's a following node because if there's not it means the node_to_remove is the biggest
    node and that means it's the leaf at the right of the tree */
    Swap(node_to_remove, following_node);
    if(node_to_remove->GetFatherNode()== nullptr)
    {
        this->root=following_node;
        following_node->SetFatherNode(nullptr);
    }

    else if(node_to_remove->GetFatherNode()!= nullptr)
    {
        if(node_to_remove->GetNodeRight()== nullptr) {
            if (node_to_remove->GetFatherNode()->GetNodeRight() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeRight(nullptr);
            else if (node_to_remove->GetFatherNode()->GetNodeLeft() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeLeft(nullptr);
        }

        else if(node_to_remove->GetNodeRight() != nullptr)
        {
            node_to_remove->GetNodeRight()->SetFatherNode(node_to_remove->GetFatherNode());
            if (node_to_remove->GetFatherNode()->GetNodeRight() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeRight(node_to_remove->GetNodeRight());
            else if (node_to_remove->GetFatherNode()->GetNodeLeft() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeLeft(node_to_remove->GetNodeRight());
        }
    }

    //fix the heights of the fathers
    Node<T>* father = node_to_remove->GetFatherNode();
    Node<T>* temp =father;
    while(temp!= nullptr)
    {
        if(temp->SetNewHeight()==0)
            break;
        temp= temp->GetFatherNode();
    }

    //We now check the BF of all the nodes from here to the root
    if(father == nullptr)
    {
        return AVL_SUCCESS;
    }
    int BF = father->GetBF();

    while (true)
    {
        if (BF==2){
            if(father->GetNodeLeft() != nullptr) {

                if ((father->GetNodeLeft())->GetBF() == -1)
                    RotateLR(father);
                else if ((father->GetNodeLeft())->GetBF() >= 0)
                    RotateLL(father);
            }
        }

        if (BF==-2){
            if(father->GetNodeRight() != nullptr) {
                if ((father->GetNodeRight())->GetBF() == 1)
                    RotateRL(father);
                else if ((father->GetNodeRight())->GetBF() <= 0)
                    RotateRR(father);
            }
        }

        if (father->GetFatherNode()== nullptr)
            break;
        father=father->GetFatherNode();
        BF = father->GetBF();
    }

    delete node_to_remove;
    return AVL_SUCCESS;
}

//if it's a leaf, remove it and then check the BF of every node before and fix it.
template <class T>
AVLResults Avl_tree<T>::Remove_Node_Leaf(Node<T>* node) {
    if (node == nullptr)
        return AVL_NULL_ARGUMENT;

    //Remove the node
    Node<T>* father = node->GetFatherNode();

    if(father== nullptr) //the node is the root and has no son
    {
        this->root = nullptr;
        delete node;
        return AVL_SUCCESS;
    }

    //the node is a left leaf
    if (father->GetNodeLeft()==node) {
        father->SetNodeLeft(nullptr);
        if(father->GetNodeRight()== nullptr) {
            father->SetHeight(0);
            Node<T>* temp= father;
            while(temp->GetFatherNode()!= nullptr)
            {
                //if the node didnt change the height, we stop checking further
                if (temp->GetFatherNode()->SetNewHeight()==0)
                    break;
                temp= temp->GetFatherNode();
            }
        }
    }

    //the node is a right leaf
    if (father->GetNodeRight()==node) {
        father->SetNodeRight(nullptr);

        if (father->GetNodeLeft() == nullptr) { //change the height
            father->SetHeight(0);
            Node<T> *temp = father;
            while (temp->GetFatherNode() != nullptr) {
                //if the node didnt change the height, we stop checking further
                if (temp->GetFatherNode()->SetNewHeight() == 0)
                    break;
                temp = temp->GetFatherNode();
            }
        }
    }

    delete node;

    //then check the BF of every node from father to the root.
    int BF = father->GetBF();

    while (true)
    {
        if (BF==2){
            if(father->GetNodeLeft() != nullptr) {
                if ((father->GetNodeLeft()->GetBF() == -1))
                    RotateLR(father);
                else if ((father->GetNodeLeft())->GetBF() >= 0)
                    RotateLL(father);
            }
        }

        if (BF==-2){
            if(father->GetNodeRight() != nullptr) {
                if ((father->GetNodeRight())->GetBF() == 1)
                    RotateRL(father);
                else if ((father->GetNodeRight())->GetBF() <= 0)
                    RotateRR(father);
            }
        }

        if (father->GetFatherNode()== nullptr)
            break;
        father=father->GetFatherNode();
        BF = father->GetBF();
    }

    return AVL_SUCCESS;
}

//if there's one son, remove it and replace it in the "father" node with his son
// and then check the BF of every node before and fix it.
template <class T>
AVLResults Avl_tree<T>::Remove_Node_With_Only_Child(Node<T>* node) {
    if (node== nullptr)
        return AVL_NULL_ARGUMENT;

    Node<T>* father = node->GetFatherNode();
    if(father == nullptr) //node is root and has only one son
    {
        if (node->GetNodeRight() == nullptr)
        {
            this->root = node->GetNodeLeft();
            node->GetNodeLeft()->SetFatherNode(nullptr);
            delete node;
            return AVL_SUCCESS;
        }

        if (node->GetNodeLeft() == nullptr)
        {
            this->root = node->GetNodeRight();
            node->GetNodeRight()->SetFatherNode(nullptr);
            delete node;
            return AVL_SUCCESS;
        }
    }

    //first remove the node and replace it with his son.
    if(father->GetNodeLeft()==node) {
        if (node->GetNodeRight() == nullptr) {
            father->SetNodeLeft(node->GetNodeLeft());
            node->GetNodeLeft()->SetFatherNode(father);
        }
        else {
            father->SetNodeLeft(node->GetNodeRight());
            node->GetNodeRight()->SetFatherNode(father);
        }
    }

    else {
        if (node->GetNodeRight() == nullptr) {
            father->SetNodeRight(node->GetNodeLeft());
            node->GetNodeLeft()->SetFatherNode(father);
        }
        else {
            father->SetNodeRight(node->GetNodeRight());
            node->GetNodeRight()->SetFatherNode(father);
        }
    }

    //fix the heights of the fathers
    Node<T>* temp =father;
    while(temp!= nullptr)
    {
        if(temp->SetNewHeight()==0)
            break;
        temp= temp->GetFatherNode();
    }

    delete node;

    //then check the BF and fix it from father up to the root
    if(father == nullptr)
    {
        return AVL_SUCCESS;
    }
    int BF = father->GetBF();

    while (true)
    {
        if (BF==2){
            if(father->GetNodeLeft() != nullptr) {

                if ((father->GetNodeLeft())->GetBF() == -1)
                    RotateLR(father);
                else if ((father->GetNodeLeft())->GetBF() >= 0)
                    RotateLL(father);
            }
        }

        if (BF==-2){
            if(father->GetNodeRight() != nullptr) {

                if ((father->GetNodeRight())->GetBF() == 1)
                    RotateRL(father);
                else if ((father->GetNodeRight())->GetBF() <= 0)
                    RotateRR(father);
            }
        }

        if (father->GetFatherNode()== nullptr)
            break;
        father=father->GetFatherNode();
        BF = father->GetBF();
    }

    return AVL_SUCCESS;
}

template <class T> // not needed
void Avl_tree<T>::Swap(Node<T>* node_1, Node<T>* node_2){
    int temp_height = node_1->GetHeight;
    Node<T>* temp_left_son = node_1->GetNodeLeft();
    Node<T>* temp_right_son = node_1->GetNodeRight();
    Node<T>* temp_father_node = node_1->GetFatherNode();
    node_1->SetFatherNode(node_2->GetFatherNode());
    node_1->SetNodeRight(node_2->GetNodeRight());
    node_1->SetNodeLeft(node_2->GetNodeLeft());
    node_1->SetHeight(node_2->GetHeight());
    node_2->SetFatherNode(temp_father_node);
    node_2->SetNodeRight(temp_right_son);
    node_2->SetNodeLeft(temp_left_son);
    node_2->SetHeight(temp_height);
    Node<T>* father_node_1 = node_1->GetFatherNode();
    Node<T>* father_node_2 = node_2->GetFatherNode();
    if(father_node_1 == nullptr){
        this->SetRoot(node_1);
    }
    else{
        if(father_node_1->GetNodeRight() == node_2){
            father_node_1->SetNodeRight = node_1;
        }
        else father_node_1->SetNodeLeft = node_1;
    }
    if(father_node_2 == nullptr){
        this->SetRoot(node_2);
    }
    else{
        if(father_node_2->GetNodeRight() == node_1){
            father_node_2->SetNodeRight = node_2;
        }
        else father_node_2->SetNodeLeft = node_2;
    }
    Node<T>* right_son_1 = node_1->GetNodeRight();
    if(right_son_1 != nullptr){
        right_son_1->SetFatherNode(node_1);
    }
    Node<T>* left_son_1= node_1->GetNodeLeft();
    if(left_son_1 != nullptr){
        left_son_1->SetFatherNode(node_1);
    }
    Node<T>* right_son_2 = node_2->GetNodeRight();
    if(right_son_2 != nullptr){
        right_son_2->SetFatherNode(node_2);
    }
    Node<T>* left_son_2= node_2->GetNodeLeft();
    if(left_son_2 != nullptr){
        left_son_2->SetFatherNode(node_2);
    }
}
template <class T>
AVLResults Avl_tree<T>::RotateLL(Node<T>* B_node){
    Node<T>* A_node = B_node->GetNodeLeft();
    Node<T>* A_node_right = A_node->GetNodeRight();
    A_node->SetFatherNode(B_node->GetFatherNode());
    if(A_node->GetFatherNode() == nullptr){
        this->SetRoot(A_node);
    }
    else{
        if(A_node->GetFatherNode()->GetNodeLeft()== B_node){
            A_node->GetFatherNode()->SetNodeLeft(A_node);
        }
        else A_node->GetFatherNode()->SetNodeRight(A_node);
    }
    A_node->SetNodeRight(B_node);
    B_node->SetFatherNode(A_node);
    B_node->SetNodeLeft(A_node_right());
    if(A_node_right != nullptr){
        A_node_right->SetFatherNode(B_node);
    }
    A_node->SetNewHeight();
    B_node->SetNewHeight();
    return AVL_SUCCESS;
}

template <class T>
AVLResults Avl_tree<T>::RotateRR(Node<T>* B_node){
    Node<T>* A_node = B_node->GetNodeRight();
    Node<T>* A_node_left = A_node->GetNodeLeft();
    A_node->SetFatherNode(B_node->GetFatherNode());
    if(A_node->GetFatherNode() == nullptr){
        this->SetRoot(A_node);
    }
    else{
        if(A_node->GetFatherNode()->GetNodeLeft()== B_node){
            A_node->GetFatherNode()->SetNodeLeft(A_node);
        }
        else A_node->GetFatherNode()->SetNodeRight(A_node);
    }
    A_node->SetNodeLeft(B_node);
    B_node->SetFatherNode(A_node);
    B_node->SetNodeRight(A_node_Left());
    if(A_node_left != nullptr){
        A_node_left->SetFatherNode(B_node);
    }
    A_node->SetNewHeight();
    B_node->SetNewHeight();
    return AVL_SUCCESS;                                                                                                                                                                                                                                                                                                                                                                                                                       }

template <class T>
AVLResults Avl_tree<T>::RotateLR(Node<T>* C_node){
    Node<T>* A_node = C_node->GetNodeLeft();
    Node<T>* B_node = A_node->GetNodeRight();
    Node<T>* B_node_right = B_node->GetNodeRight();
    Node<T>* B_node_left = B_node->GetNodeLeft();
    B_node->SetFatherNode(C_node->GetFatherNode());
    if(B_node->GetFatherNode() == nullptr){
        this->SetRoot(B_node);
    }
    else{
        if(B_node->GetFatherNode()->GetNodeLeft()== C_node){
            B_node->GetFatherNode()->SetNodeLeft(B_node);
        }
        else B_node->GetFatherNode()->SetNodeRight(B_node);
    }
    B_node->SetNodeLeft(A_node);
    B_node->SetNodeRight(C_node);
    A_node->SetFatherNode(B_node);
    C_node->SetFatherNode(B_node);
    C_node->SetNodeLeft(B_node_right);
    if(B_node_right != nullptr){
        B_node_right->SetFatherNode(C_node);
    }
    A_node->SetNodeRight(B_node_left);
    if(B_node_left != nullptr){
        B_node_left->SetFatherNode(A_node);
    }
    A_node->SetNewHeight();
    C_node->SetNewHeight();
    B_node->SetNewHeight();
    return AVL_SUCCESS;                                                                                                                                                                                                                                                                                                                                                                                                                       }

template <class T>
AVLResults Avl_tree<T>::RotateRL(Node<T>* C_node){
    Node<T>* A_node = C_node->GetNodeRight();
    Node<T>* B_node = A_node->GetNodeLeft();
    Node<T>* B_node_right = B_node->GetNodeRight();
    Node<T>* B_node_left = B_node->GetNodeLeft();
    B_node->SetFatherNode(C_node->GetFatherNode());
    if(B_node->GetFatherNode() == nullptr){
        this->SetRoot(B_node);
    }
    else{
        if(B_node->GetFatherNode()->GetNodeLeft()== C_node){
            B_node->GetFatherNode()->SetNodeLeft(B_node);
        }
        else B_node->GetFatherNode()->SetNodeRight(B_node);
    }
    B_node->SetNodeRight(A_node);
    B_node->SetNodeLeft(C_node);
    A_node->SetFatherNode(B_node);
    C_node->SetFatherNode(B_node);
    C_node->SetNodeRight(B_node_left);
    if(B_node_left != nullptr){
        B_node_left->SetFatherNode(C_node);
    }
    A_node->SetNodeLeft(B_node_right);
    if(B_node_right != nullptr){
        B_node_right->SetFatherNode(A_node);
    }
    A_node->SetNewHeight();
    C_node->SetNewHeight();
    B_node->SetNewHeight();
    return AVL_SUCCESS;                                                                                                                                                                                                                                                                                                                                                                                                                       }

template <class T>
void Avl_tree<T>::Check_And_Fix_BF(Node<T>* check){
    while(check != nullptr){
        if(check->GetBalancedFactor() == 2){
            if(check->GetNodeLeft()->GetBalancedFactor() == -1){
                this->RotateLR(check);
            }
            else this->RotateLL(check);
        }
        else if(check->GetBalancedFactor() == -2){
            if(check->GetNodeRight()->GetBalancedFactor() == 1){
                this->RotateRL(check);
            }
            else this-> RotateRR:
        }
        else{
            check->SetNewHeight();
        }
        check = check->GetFatherNode;
    }
}






#endif //MIVNEWET1_AVLTREES_H
