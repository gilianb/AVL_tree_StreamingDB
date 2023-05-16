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
    double key_grade;
    int key_view;
    T element;
    int height;
    Node* father;
    Node* left_son;
    Node* right_son;
public:
    explicit Node(int key = -1,double key_grade = -1, int key_view = -1, T element = nullptr, int height = 0, Node* father = nullptr, Node* left_son = nullptr,
                  Node* right_son = nullptr);
    ~Node();
    void SetKey(int key);
    int GetKey() const;
    void SetKeyView(int key);
    int GetKeyView() const;
    void SetKeyGrade(double key);
    double GetKeyGrade() const;
    void SetElement(T element_to_set);
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
    int SetNewHeight();
};

template <class T>
class Avl_tree {
private:
    Node<T>* root;
    Node<T>* biggest_node;
    //Node<T>* CopyNodes(Node<T>* node);
public:
    Avl_tree();

    explicit Avl_tree(Node<T>* root);

    ~Avl_tree();

    void AuxDistructorTree(Node<T>* node);

    Node<T>* GetRoot() ;

    Node<T>* GetBiggestNode() const;

    void SetRoot( Node<T>* new_root);

    void SetBiggestNode(Node<T>* new_biggest);

    Node<T>* FindPreviousNode(Node<T>* node) const;

    Node<T>* FindNode(int key) const;

    Node<T>*  FindNodeInGenre(int key, double rate , int view);


    AVLResults InsertNode(Node<T>* node);

    AVLResults InsertNodeInGenre(Node<T>* node);

    void Check_And_Fix_BF(Node<T>* check);

    AVLResults RemoveNode(int key);

    AVLResults RemoveNode(int key, int PlayerID);

    AVLResults RemoveNode(Node<T>* node_to_remove);

    AVLResults Remove_Node_Leaf(Node<T>* node);

    AVLResults Remove_Node_With_Only_Child (Node<T>* node);

    void Swap(Node<T>* node_1, Node<T>* node_2);

    AVLResults RotateLL(Node<T>* B_node);

    AVLResults RotateLR(Node<T>* node);

    AVLResults RotateRL(Node<T>* node);

    AVLResults RotateRR(Node<T>* node);

    void ReverseInorder(int* array, int size);

    // Node<T>* ReplaceNodeByAnother(Node<T>* last, Node<T>* new_node);
};



template <class T>
Node<T>::Node(int key, double key_grade, int key_view, T element, int height, Node* father, Node* left_son, Node* right_son) :
        key(key),key_grade(key_grade), key_view(key_view), element(element), height(height), father(father), left_son(left_son), right_son(right_son) {}

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
void Node<T>::SetKeyGrade(double key_to_set)
{
    key_grade = key_to_set;
}

template <class T>
double Node<T>::GetKeyGrade() const
{
    return key_grade;
}

template <class T>
void Node<T>::SetKeyView(int key_to_set)
{
    key_view = key_to_set;
}

template <class T>
int Node<T>::GetKeyView() const
{
    return key_view;
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
void Node<T>::SetElement(T element_to_set)
{
    element = element_to_set;
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
        height_right= right_son->GetHeight();
    }
    return (height_left-height_right);
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


//--------------------------------AVL TREES--------------------------------------------


template <class T>
Avl_tree<T>::Avl_tree(): root(nullptr) {}

template <class T>
Avl_tree<T>::Avl_tree(Node<T>* root) : root(root) {}

template <class T>
Avl_tree<T>::~Avl_tree(){
    this->AuxDistructorTree(root);
}

template <class T>
void Avl_tree<T>::AuxDistructorTree( Node<T>* node){
    if(node == nullptr) return;
    AuxDistructorTree(node->GetNodeLeft());
    AuxDistructorTree(node->GetNodeRight());
    delete node;

}
template <class T>
void Avl_tree<T>::SetRoot( Node<T>* new_root)
{
    this->root = new_root;
}

template<class T>
Node<T>* Avl_tree<T>::GetBiggestNode() const{
    return this->biggest_node;
}
template<class T>
void Avl_tree<T>::SetBiggestNode(Node<T>* new_biggest) {
    this->biggest_node = new_biggest;
}

template <class T>
Node<T>* Avl_tree<T>::FindPreviousNode(Node<T>* node) const{
    if(node->GetNodeLeft()!=nullptr && node->GetNodeLeft()->GetNodeRight()==nullptr) return node->GetNodeLeft();
    if(node->GetNodeLeft()!=nullptr && node->GetNodeLeft()->GetNodeRight()!=nullptr){
        node = node->GetNodeLeft()->GetNodeRight();
        while(node->GetNodeRight()!=nullptr) node = node ->GetNodeRight();
        return node;
    }
    while(node->GetFatherNode()->GetNodeLeft()== node && node->GetFatherNode()!=nullptr) node = node->GetFatherNode();
    if((node->GetFatherNode()=nullptr)) return nullptr; // which means we arrived at the root and node is the minimum of the tree
    else return node->GetFatherNode();
}

template <class T>
Node<T>* Avl_tree<T>::FindNode(int key_to_find) const{
    if (root == nullptr)
    {
        return nullptr;
    }
    Node<T>* node_to_return = root;
    int current_key= root->GetKey();
    while (key_to_find!=current_key && node_to_return != nullptr){
        if(key_to_find < current_key){
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
Node<T>* Avl_tree<T>::FindNodeInGenre(int key, double grade, int views){
    if (root == nullptr)
    {
        return nullptr;
    }
    Node<T>* node_to_return = root;
    while (key != node_to_return->GetKey() && node_to_return != nullptr){
        if(grade > node_to_return->GetKeyGrade() || (grade == node_to_return->GetKeyGrade() && views > node_to_return->GetKeyView()) ||
           (grade == node_to_return->GetKeyGrade() && views == node_to_return->GetKeyView() && key < node_to_return->GetKey())){
            node_to_return = node_to_return->GetNodeRight();
        }
        else node_to_return = node_to_return->GetNodeLeft();
    }

    return node_to_return;
}

template <class T>
AVLResults Avl_tree<T>::InsertNode(Node<T>* node){
    if (root== nullptr){
        root = node;
        this->SetBiggestNode(node);
        return AVL_SUCCESS;
    }
    Node<T>* current_node=root;
    while (current_node!= nullptr){
        if(current_node->GetKey() < node->GetKey()){
            if (current_node->GetNodeRight()== nullptr){
                current_node->SetNodeRight(node);
                break;
            }
            current_node=current_node->GetNodeRight();
            continue;
        }
        else{
            if (current_node->GetNodeLeft()== nullptr){
                current_node->SetNodeLeft(node);
                break;
            }
            current_node=current_node->GetNodeLeft();
            continue;
        }
    }
    node->SetFatherNode(current_node);
    if(current_node == this->GetBiggestNode() && current_node->GetNodeRight() == node) this->SetBiggestNode(node);
    // time to check the BF
    this->Check_And_Fix_BF(node);
    return AVL_SUCCESS;
}

template <class T>
AVLResults Avl_tree<T>::InsertNodeInGenre(Node<T>* node){
    if (root== nullptr){
        root = node;
        this->SetBiggestNode(node);
        return AVL_SUCCESS;
    }
    Node<T>* current_node=root;
    while (current_node!= nullptr){
        if(node->GetKeyGrade() > current_node->GetKeyGrade() || (node->GetKeyGrade() == current_node->GetKeyGrade() && node->GetKeyView() > current_node->GetKeyView()) ||
           (node->GetKeyGrade() == current_node->GetKeyGrade() && node->GetKeyView() == current_node->GetKeyView() && node->GetKey() < current_node->GetKey())){
            if (current_node->GetNodeRight()== nullptr){
                current_node->SetNodeRight(node);
                break;
            }
            current_node=current_node->GetNodeRight();
            continue;
        }
        else{
            if (current_node->GetNodeLeft()== nullptr){
                current_node->SetNodeLeft(node);
                break;
            }
            current_node=current_node->GetNodeLeft();
            continue;
        }
    }
    node->SetFatherNode(current_node);
    if(current_node == this->GetBiggestNode() && current_node->GetNodeRight() == node) this->SetBiggestNode(node);
    // time to check the BF
    this->Check_And_Fix_BF(node);
    return AVL_SUCCESS;
}


template <class T>
void Avl_tree<T>::Swap(Node<T>* node_1, Node<T>* node_2){
    int temp_height = node_1->GetHeight();
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
            father_node_1->SetNodeRight(node_1);
        }
        else father_node_1->SetNodeLeft(node_1);
    }
    if(father_node_2 == nullptr){
        this->SetRoot(node_2);
    }
    else{
        if(father_node_2->GetNodeRight() == node_1){
            father_node_2->SetNodeRight(node_2);
        }
        else father_node_2->SetNodeLeft(node_2);
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
    B_node->SetNodeLeft(A_node_right);
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
    B_node->SetNodeRight(A_node_left);
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
            else this->RotateRR(check);
        }
        else{
            check->SetNewHeight();
        }
        check = check->GetFatherNode();
    }
}
template <class T>
AVLResults Avl_tree<T>::RemoveNode(Node<T>* node_to_remove) {

    if (node_to_remove== nullptr)
        return AVL_NODE_NO_EXIST;
    //if it s a leaf or the root alone
    if (node_to_remove->GetNodeRight()== nullptr && node_to_remove->GetNodeLeft()== nullptr){
        if(node_to_remove==root){
            root = nullptr;
            this->SetBiggestNode(nullptr);
        }
        else{
            if(node_to_remove->GetFatherNode()->GetNodeRight()== node_to_remove){
                node_to_remove->GetFatherNode()->SetNodeRight(nullptr);
            }
            else{
                node_to_remove->GetFatherNode()->SetNodeLeft(nullptr);
            }
            this->Check_And_Fix_BF(node_to_remove->GetFatherNode());
            if(node_to_remove== this->GetBiggestNode()) this->SetBiggestNode(node_to_remove->GetFatherNode());
        }
    }
    else if (node_to_remove->GetNodeRight()== nullptr || node_to_remove->GetNodeLeft()== nullptr){
        Node<T>* son_of_node_to_remove;
        if (node_to_remove->GetNodeRight()== nullptr){
            son_of_node_to_remove = node_to_remove->GetNodeLeft();
        }
        else son_of_node_to_remove = node_to_remove->GetNodeRight();
        son_of_node_to_remove->SetFatherNode(node_to_remove->GetFatherNode());
        if(node_to_remove==root){
            root = son_of_node_to_remove;
            if(node_to_remove== this->GetBiggestNode()) this->SetBiggestNode(son_of_node_to_remove);
        }
        else{
            if(node_to_remove->GetFatherNode()->GetNodeRight()== node_to_remove){
                node_to_remove->GetFatherNode()->SetNodeRight(son_of_node_to_remove);
            }
            else{
                node_to_remove->GetFatherNode()->SetNodeLeft(son_of_node_to_remove);
            }
            if(node_to_remove== this->GetBiggestNode()) this->SetBiggestNode(son_of_node_to_remove);
        }
        this->Check_And_Fix_BF(son_of_node_to_remove);
        delete node_to_remove;
        return AVL_SUCCESS;
    }
        //The node has 2 children, we look for the "following" node and we swap them
        //then we delete the node to remove
    else{
        Node<T>* node_to_swap = node_to_remove->GetNodeRight();
        while(node_to_swap->GetNodeLeft() != nullptr){
            node_to_swap = node_to_swap->GetNodeLeft();
        }
        this->Swap(node_to_remove,node_to_swap);
        return this->RemoveNode(node_to_remove);
    }
}
template<class T>
void Avl_tree<T>::ReverseInorder(int* array, int size){
    int i=0;
    Node<T>* node = this->GetBiggestNode();
    while(node != nullptr){
        array[i] = node -> GetKey();
        i+=1;
        node =this->FindPreviousNode(node);
    }
}

template<class T>
Node<T>* max(Node<T>* node1, Node<T>* node2){
    if(node1 == nullptr) return node2;
    if(node2 == nullptr) return node1;
    if(node1->GetKeyGrade() > node2->GetKeyGrade() || (node1->GetKeyGrade() == node2->GetKeyGrade() && node1->GetKeyView() > node2->GetKeyView()) ||
       (node1->GetKeyGrade() == node2->GetKeyGrade() && node1->GetKeyView() == node2->GetKeyView() && node1->GetKey() < node2->GetKey())){
        return node1;
    }
    else return node2;
}

template<class T>
Node<T>* max(Node<T>* node1, Node<T>* node2, Node<T>* node3, Node<T>* node4){
    return max(max(node1, node2), max(node3, node4));
}

template <class T>
void ReverseInOrderOfNone(int* array, int size, Avl_tree<T*> *tree1, Avl_tree<T*> *tree2, Avl_tree<T*> *tree3, Avl_tree<T*> *tree4){
    int i = 0;
    Node<T>*  max_node, node1= tree1->GetBiggestNode(), node2 = tree2->GetBiggestNode(), node3= tree3->GetBiggestNode(), node4 = tree4->GetBiggestNode();
    while( i < size){
        max_node= max(node1,node2,node3,node4);
        array[i] = max_node->GetKey();
        if(max_node==node1) node1 = tree1->FindPreviousNode(node1);
        else if(max_node==node2) node2 = tree2->FindPreviousNode(node2);
        else if(max_node==node3) node3 = tree3->FindPreviousNode(node3);
        else if(max_node==node4) node4 = tree4->FindPreviousNode(node4);
        i++;

    }
}

#endif //MIVNEWET1_AVLTREES_H