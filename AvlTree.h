//
// Created by Mostafa on 08/08/2020
//

#ifndef AVL1_AVLTREE_H
#define AVL1_AVLTREE_H

#include "library1.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <typeinfo>

#define RL 10
#define LR 1
#define RR 11
#define LL 0



template<class D, class K>
class AvlTreeNode {
public :
    int height;
    D *data;
    K *key;
    AvlTreeNode<D, K> *LeftSon;
    AvlTreeNode<D, K> *RightSon;

    AvlTreeNode() {
        data = NULL;
        LeftSon = NULL;
        RightSon = NULL;
        height=0;
    }

    ~AvlTreeNode()
    {
        char* name;
        name = const_cast<char *>(typeid(data).name());

        if(data && (strcmp(name,"Pi") != 0 && strcmp(name,"i") != 0 ))
            delete(data);
        if(data != NULL && (strcmp(name,"Pi") != 0 && strcmp(name,"i") != 0 ))
            data= nullptr;
        if(key && (strcmp(name,"Pi") != 0 && strcmp(name,"i") != 0 ))
            delete(key);
        if(key != NULL && (strcmp(name,"Pi") != 0 && strcmp(name,"i") != 0 ))
            key= nullptr;

        if(!(strcmp(name,"Pi") != 0 && strcmp(name,"i") != 0 )){
            if(key)
                delete(key);
            data=0;
        }
        this->LeftSon= nullptr;
        this->RightSon= nullptr;
    }

};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class D, class K>
class AvlTree {
public:

    AvlTreeNode<D, K> *root;
    AvlTree() {
        root = NULL;

    }

    ~AvlTree() {
        Destroy(root);
        root= nullptr;
    }

    /////////////////////////////////////////////////////// Here are the functions that we call them and use them from the outside! AKA WRAPPER FUNCTIONS

    AvlTreeNode<D, K> *FindNodeInTree(AvlTreeNode<D, K> *root, K key) {
        int TreeSize = size(root);
        return FindNodeInTreeWrapper(TreeSize,root,key);
    }

    /////////////////////////////////////////////////Mostafa, here I added InsertNodeWrapper helper
    AvlTreeNode<D, K> *AddNodeToTree(D *data, K key) {

        auto *Node = new AvlTreeNode<D, K>;
        Node->data = data;
        Node->key = new K(key);
        AvlTreeNode<D, K> *LastNode = InsertNodeWrapper(0, root, Node);
        if (!LastNode) {
            delete Node;
            return NULL;
        }
        return LastNode;
    }

    void DeleteNodeFromTree(AvlTreeNode<D, K> *root, K key) {
        if(root == NULL)
            return;

        AvlTreeNode<D, K> *Node = FindNodeInTree(this->root, key);
        if (Node == NULL)
            return;
        deleteNodeWrapper(0,this->root, Node);
    }
    void Destroy(AvlTreeNode<D, K> *node)
    {
        if (node==NULL) return;
        Destroy(node->LeftSon);
        Destroy(node->RightSon);
        delete node;
    }
    int Size()
    {
        return size(this->root);
    }
};

////////////Rotation Functions !
template<typename D, typename K>
AvlTreeNode<D, K> *RotateLL(int rotationIndex, AvlTreeNode<D, K> *TreeNode) {
    AvlTreeNode<D, K>* temp;
    temp = TreeNode->LeftSon;
    AvlTreeNode<D, K>* tempR;
    tempR = TreeNode->LeftSon->RightSon;
    TreeNode->LeftSon->RightSon=TreeNode;
    TreeNode->LeftSon=tempR;
    if(rotationIndex == LL) //here should be LL rotation , Mostafa please take care
    {
        updateHeight(temp);
        updateHeight(TreeNode);
    }
    return temp;
}



template<typename D, typename K>
AvlTreeNode<D, K> *RotateRR(int rotationIndex,AvlTreeNode<D, K> *TreeNode) {
    AvlTreeNode<D, K>* temp;
    temp = TreeNode->RightSon;
    TreeNode->RightSon = temp->LeftSon;
    temp->LeftSon = TreeNode;
    if(rotationIndex==RR) //here should be RR rotation , Mostafa please take care
    {
        updateHeight(temp);
        updateHeight(TreeNode);
    }
    return temp;
}


////////////////////!!!! TAKE CARE LOOK HERE LOOK HERE , firas here we don;t need to make new rotate func its enough to call the old one first LL and next RR pleace check lecture 03 u will see it obvious then!!!!
template<typename D, typename K>
AvlTreeNode<D, K> * RotateRL(int rotationIndex, AvlTreeNode<D, K> *TreeNode) {
    AvlTreeNode<D, K> *temp;
    temp = TreeNode->RightSon;
    if(rotationIndex == RL) //Take care its RL rotation , firas please check here
        TreeNode->RightSon = RotateLL(LL,temp);
    return RotateRR(RR,TreeNode);
}


template<typename D, typename K>
AvlTreeNode<D, K> * RotateLR(int rotationIndex, AvlTreeNode<D, K> *TreeNode) {
    AvlTreeNode<D, K> *temp;
    temp = TreeNode->LeftSon;
    if(rotationIndex == LR) //Take care its LR rotation , firas please check here
        TreeNode->LeftSon = RotateRR(RR,temp);
    return RotateLL(LL,TreeNode);
}


////////////////////////////////////////////////////////////////////////Wrapper functions that we call them



////////////////////////////////////


//////////////////////////to firas i've noticed that u fix the balance here i think that would affect the recursive inserfunc
///////////////////////// so i made a new func called DoBalance and DoBalanceAux so we can use it in the insert and delete funcs
/////////////////////// instaed of making the code complicated please check them and run some tests , i explained why it is easier to use DoBalnce in whatsapp record msg, liten to the audio Pleas!!!!!
template<typename D, typename K>
AvlTreeNode<D, K> * InsertNodeWrapper(int size, AvlTreeNode<D, K> *&root, AvlTreeNode<D, K> *Node) // we call it using the wrapper function
{
    if (root == NULL && size>=0)
    {
        root = Node;
        return root;
    }
    else if (*Node->key - *root->key < 0)
    {
        root->LeftSon = InsertNodeWrapper(size, root->LeftSon, Node);
        root = doBalance(root);
        updateHeight(root);
        return root;
    }
    else if (*Node->key - *root->key > 0)
    {
        root->RightSon = InsertNodeWrapper(size, root->RightSon, Node);
        root = doBalance(root);
        updateHeight(root);
        return root;
    }
    size++;
    updateHeight(root);
    return root;
}

template<typename D, typename K>
AvlTreeNode<D, K>* deleteNodeWrapper(int size, AvlTreeNode<D, K> *& root, AvlTreeNode<D, K> *& Node) // we call it using the wrapper function
{
    if (size>=0 && (Node == NULL || root == NULL))
        return NULL;
    else if (*Node->key < *root->key)
    {
        root->LeftSon = deleteNodeWrapper(size, root->LeftSon, Node);
    }

    else if (*Node->key > *root->key)
    {
        root->RightSon = deleteNodeWrapper(size, root->RightSon, Node);
    }

        ///Cases I follow the cases that in the lecture the first if its a leaf , the second if it has 1 son ( left or right )
        ///the forth case if it has 2 sons !!
        ///Case1 the Node has no sons
    else if (!root->LeftSon && !root->RightSon) {
        delete root;
        root= nullptr;
        return NULL;
    }


        ///Case2 The Node has 1 son and its the Right one so the father of the curr node becomes the father of the right son of the curr node
        /// and after that we delete the curr node , to do that we can simply point by the curr node pointer to the rightson
        /// and then remove the curr node from the tree
    else if (!root->LeftSon && root->RightSon) {
        AvlTreeNode<D, K> *tempNode;
        tempNode = root;
        root = root->RightSon;
        delete tempNode;
    }

        ///Case3 The Node has 1 son and its the Left one so the father of the curr node becomes the father of the Left son of the curr node
        /// and after that we delete the curr node , to do that we can simply point by the curr node pointer to the leftSon
        /// and then remove the curr node from the tree


    else if (!root->RightSon && root->LeftSon) {
        AvlTreeNode<D, K> *tempNode;
        tempNode = root;
        root = root->LeftSon;
        delete tempNode;
    }

        ///case 4 The node has 2 sons , HERE due to the lecture we need to find the succ after that we change between them and delete the curr
        /// after the deletetion of the curr we need to go back on the above checks because the node after swapping has 1 OR 0 SONS and we need to remove CURR from the tree

        /////// NOTE HERE I CAN CHANGE THIS ALSO IF NEEDED  ,  FERAS !!!!!!!!!!!!!!
    else if (root->RightSon && root->LeftSon) {
        AvlTreeNode<D, K> *tempNode = Succ(0,root);
        D *tempData = Node->data;
        K *tempKey = Node->key;
        setKey(tempNode->key, root);
        setData(tempNode->data, root);
        setKey(tempKey, tempNode);
        setData(tempData, tempNode);
        Node->RightSon = deleteNodeWrapper(size, Node->RightSon, tempNode);
    }
    updateHeight(root);
    root =  doBalance(root);
    return root;
}
template<typename D, typename K>
AvlTreeNode<D, K> *FindNodeInTreeWrapper(int size,AvlTreeNode<D, K> *root, K key) // we call it using the wrapper function
{
    if (size == 0 || (root == NULL || root->key == NULL ))
        return NULL;
    if (*(root->key) == key && size>=0) return root;
    if (key < *(root->key) && size>=0)
        return FindNodeInTreeWrapper(size,root->LeftSon, key);
    return FindNodeInTreeWrapper(size,root->RightSon, key);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// HELPER FUNCTIONS

template<class D, class K>
void setData(D *& data , AvlTreeNode<D,K>* TreeNode){
    if(!TreeNode)
        return;
    TreeNode->data=data;
}

template<class D, class K>
void setKey(K* key, AvlTreeNode<D,K>* TreeNode){
    if(!TreeNode)
        return;
    TreeNode->key=key;
}

template<class D, class K>
int NodeHeight(AvlTreeNode<D, K> *TreeNode) {
    if(!TreeNode) return -1;
    return TreeNode->height;
}

template<class D, class K>
void updateHeight(AvlTreeNode<D, K> *TreeNode)
{
    if(TreeNode == nullptr)
        return;
    TreeNode->height =  getMax(TreeNode->LeftSon,TreeNode->RightSon);
}

template<class D, class K>
AvlTreeNode<D, K>* Succ(int index, AvlTreeNode<D, K>* NodeInTree)
{
    AvlTreeNode<D, K>* temp=NodeInTree->RightSon;
    while(temp->LeftSon && index >=0) {
        temp = temp->LeftSon;
    }
    return temp;

}

template<class D, class K>
int getMax(AvlTreeNode<D, K> *Left , AvlTreeNode<D, K> *Right)
{

    if(Left== nullptr && Right== nullptr)
        return 0;
    else if(Left != nullptr && Right== nullptr)
        return 1+Left->height;
    else if(Left == nullptr)
        return 1+Right->height;
    else if(Left->height > Right->height) return 1+Left->height;
    return 1+Right->height;
}


template<class D, class K>
int size(AvlTreeNode<D, K>* root)
{
    if(!root) return 0;
    return size(root->RightSon)+size(root->LeftSon)+1;
}

template<class D, class K>
AvlTreeNode<D,K>* doBalance(AvlTreeNode<D, K>* root)
{
    if(root == nullptr)
        return NULL;
    int checkBalance = NodeHeight(root->LeftSon)-NodeHeight(root->RightSon); // asm3 hon mnqdr nm7a kl fonktsyat NodeHeight wnkbha bl zbale wnst3ml bs al height
    if(checkBalance == -2)
        root = doBalanceAux(1,root);
    if(checkBalance == 2)
        root = doBalanceAux(2, root);
    updateHeight(root);
    return root;

}
template<class D, class K>
AvlTreeNode<D,K>* doBalanceAux(int index, AvlTreeNode<D, K>* root) {

    if(index == 1){
        int calcRes = NodeHeight(root->RightSon->LeftSon) - NodeHeight(root->RightSon->RightSon);
        if(calcRes == 1)
            root = RotateRL(RL,root);
        else if (calcRes <= 0 )
        {
            root = RotateRR(RR,root);
        }
    }
    if(index == 2) {
        int calcRes = NodeHeight(root->LeftSon->LeftSon) - NodeHeight(root->LeftSon->RightSon);
        if (calcRes == -1) {
            root = RotateLR(LR, root);

        } else if (calcRes >= 0) {
            root = RotateLL(LL, root);
        }
    }
    return root;
}

#endif //AVL1_AVLTREE_H
