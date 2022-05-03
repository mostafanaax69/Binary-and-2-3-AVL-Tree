#ifndef TwoThreeTree_H
#define TwoThreeTree_H
#include <iostream>

template <class D,class K>
struct TwoThreeNode {

    K* key;
    K* value1;
    K* value2;
    D* data;
    D* d1;
    D* d2;
    int n{};
    int numOfSons{};
    TwoThreeNode<D,K>* left;
    TwoThreeNode<D,K>* middle;
    TwoThreeNode<D,K>* right;
    TwoThreeNode<D,K>* parent;
    K* middleVal;
    D* mid;
    TwoThreeNode<D,K>* child;

    TwoThreeNode<D,K>()
    {
        key = nullptr;
        data = nullptr;
        value1 = NULL;
        value2 = NULL;
        numOfSons = 0 ;
        n = 0 ;
        left = nullptr;
        right = nullptr;
        middle = nullptr;
        child = nullptr;
        middleVal = nullptr;
        mid = nullptr;
    }

    ////////////////////////////// to firas i deleted the old constructers of the TwoThreeNode because i suspected something wrong
    //////////////////////////// i will add new constructer and send u the file

};


template <class D, class K>
class TwoThreeTree
{
public:
    TwoThreeNode<D,K>* root;
    int size ;

    TwoThreeTree()
    {
        root = nullptr;
        size = 0 ;
    }

    void correctTheTree(TwoThreeNode<D,K>* midnode , TwoThreeNode<D,K>* parent) {
        if (parent->value2 == NULL) {   //This node is a 2-node
            int diff = parent->value1-midnode->value1;

            if (diff > 0) {
                parent->value2 = parent->value1;
                parent->value1 = midnode->value1;
                parent->left = midnode->left;
                parent->left->parent = parent;
                parent->middle = midnode->right;
                parent->middle->parent = parent;
            } else { // mid node key 1 bigger or equal to parent node key 1
                parent->value2 = midnode->value1;
                parent->middle = midnode->left;
                parent->middle->parent = parent;
                parent->right = midnode->right;
                parent->right->parent = parent;
            }
        }

        else {             // here is 3 node we should split it !!!
            splitThreeNode(parent,parent->parent);

            if (parent->parent != NULL) {
                correctTheTree(parent,parent->parent);
            }
        }
    }


    void splitLeaf(TwoThreeNode<D,K>* added , TwoThreeNode<D,K>* curr) {
        int diff = (*curr->value1 - *added->key);

        if (diff > 0) {        //New added item is smaller than nodeKey1

            auto* RightNode = new TwoThreeNode<D, K>;
            RightNode->data = curr->d2;
            RightNode->d1 = curr->d2;
            RightNode->key = curr->value2;
            RightNode->value1 = curr->value2;
            RightNode->parent = curr;
            curr->right = RightNode;
            curr->left = added;
            added->parent = curr;
            curr->value2 = NULL;
        } else {       //New added item is larger than nodeKey1
            diff = (curr->value2 - added->key);
            if (diff > 0) {    //New added item is smaller than nodeKey2
                auto* LeftNode = new TwoThreeNode<D, K>;
                LeftNode->data = curr->d1;
                LeftNode->d1 = curr->d1;
                LeftNode->key = curr->value1;
                LeftNode->value1 = curr->value1;
                LeftNode->parent = curr;
                added->parent = curr;
                curr->left = LeftNode;
                curr->right = added;
                curr->value1 = added->key;
                curr->value2 = NULL;
            }  else {              //New added item is larger than nodeKey2 and largest
                auto* LeftNode = new TwoThreeNode<D, K>;
                LeftNode->data = curr->d1;
                LeftNode->d1 = curr->d1;
                LeftNode->key = curr->value1;
                LeftNode->value1 = curr->value1;
                LeftNode->parent = curr;
                curr->left = LeftNode;
                curr->right = added;
                added->parent = curr;
                curr->value1 = curr->value2;
                curr->d1 = curr->d2;
                curr->value2 = nullptr;
                curr->d2 = nullptr;
            }
        }
    }


    void splitThreeNode(TwoThreeNode<D,K>* midnode , TwoThreeNode<D,K>* parent) {
        int diff = parent->value1-midnode->value1;
        TwoThreeNode<D,K>* temp = new TwoThreeNode<D,K>;

        if (diff > 0) {     //new added item is smaller than nodekey 1
            parent->left = midnode;
            parent->left->parent = parent;
            temp->data = parent->d2;
            temp->d1 = parent->d2;
            temp->key = parent->value2;
            temp->value1 = parent->value2;
            temp->parent = parent;
            parent->value2 = NULL;
            temp->left = parent->middle;
            temp->left->parent = temp;
            temp->right = parent->right;
            temp->right->parent = temp;
            parent->right = temp;
            parent->middle = NULL;

        } else {
            diff = parent->value2 - midnode->value1;

            if (diff > 0) {    // new item that i am going to add is between nodekey1 and nodekey2
                temp->parent = parent;
                temp->value1 = parent->value1;
                temp->left = parent->left;
                temp->left->parent = temp;
                temp->right = midnode->left;
                temp->right->parent = temp;
                parent->left = temp;

                temp->parent = parent;
                temp->value1 = parent->value2;
                temp->left = midnode->right;
                temp->left->parent = temp;
                temp->right = parent->right;
                temp->right->parent = temp;
                parent->right = temp;
                parent->value1 = midnode->value1;
                parent->value2 = NULL;
                parent->middle = NULL;
            } else {
                parent->right = midnode;
                parent->right->parent = parent;
                temp->parent = parent;
                temp->value1 = parent->value1;

                temp->left = parent->left;
                temp->left->parent = temp;
                temp->right = parent->middle;
                temp->right->parent = temp;
                parent->left = temp;
                parent->value1 = parent->value2;
                parent->value2 = NULL;
                parent->middle = NULL;
            }
        }
    }



    TwoThreeNode<D,K>* AddNodeToTree(D* data ,K key)
    {
        TwoThreeNode<D, K>* NodeInTree = FindNodeInTree(root,key);
        if(NodeInTree !=NULL) return NodeInTree;

        NodeInTree = new TwoThreeNode<D, K>;
        NodeInTree->data = data;
        NodeInTree->d1 = data;
        NodeInTree->key = new K(key);
        NodeInTree->value1 = new K(key);
        if (root == nullptr)
        {
            NodeInTree->n = 1;
            NodeInTree->numOfSons = 0 ;
            root = NodeInTree;
            size++;
            return NodeInTree;

        }
        TwoThreeNode<D,K>* InsertedNode = insert(root, NodeInTree);
        size++; //
        return InsertedNode;
    }


    TwoThreeNode<D, K>* FindNodeInTree(TwoThreeNode<D, K> *TreeNode, K key) {

        if (!TreeNode)
            return NULL;

        if (key == *TreeNode->value1 || ((TreeNode->value2 != NULL ) && (key == *TreeNode->value2)))
            return TreeNode;

        if (key < *TreeNode->value1)
            return FindNodeInTree(TreeNode->left, key);

        if (TreeNode->value2 && key > *TreeNode->value2)
            return FindNodeInTree(TreeNode->right, key);

        return FindNodeInTree(TreeNode->middle, key);
    }

    /// to firas take care :  during the debug i noticed that you use a paramter called size, what do we need it for ?
    ///////to Mostafa take care : here i used size to check if the tree is empty or not because sometimes i was getting seg fault for the root
    /// so i checked if the tree is empty i return null !!! we also used size in the MusicManager take a a look at row 100
    //// to firas : I updated it we don't need size anymore you can delete it !!

    TwoThreeNode<D,K>* DeleteNodeFromTree(TwoThreeNode<D,K>* TreeNode, K* d)
    {
        TwoThreeNode<D, K> *Node = FindNodeInTree(this->root, *d);
        if (!Node)
            return NULL;
        TwoThreeNode<D,K>* p = TreeNode;
        DeleteFuncWrapper(root, d, p,d, size);
        size--;
    }



    /////// to firas : I think the insert and AddToNode is working just fine , but sometimes i get segFault or Idk
    /////// sometype of weird errors or sometimes it inserts to weird spots , it happens sometimes and not always
    ////// i really can not figure this out i am gonna wait till roi answer my email maybe he can view it and help us !!!!

    //// to mostafa : I think i found the problem maybe if we meet at sunday i can explain and fix it !!!

    TwoThreeNode<D,K>* insert(TwoThreeNode<D,K>*& root,TwoThreeNode<D,K>*& TreeNode) // wrapper function that we call it from addNotetotree
    {

        if (root->left == nullptr && root->middle == nullptr && root->right == nullptr)
        {
            if (root->value2 == nullptr)
            {
                if (TreeNode->key < root->value1)
                {
                    root->value2 = root->value1;
                    root->value1 = TreeNode->key;
                    root->d2 = root->d1;
                    root->d1 = TreeNode->d1;
                }
                else
                {
                    root->value2 = TreeNode->key;
                    root->d2 = TreeNode->data;
                }
                root->n = 2;
                root->numOfSons++;
                return TreeNode;
            }
            else
            {
                splitLeaf(TreeNode,root);
                if(root->parent != NULL)
                {
                    correctTheTree(root,root->parent);
                }
            }

            return TreeNode ;
        }

        if (TreeNode->key < root->value1)
        {
            insert(root->left, TreeNode);
        }

        else if (TreeNode->value2 == NULL)
        {
            insert(root->right,TreeNode);
        }


        else { // 3 nodes
            int diff = root->value2 - TreeNode->key;

            if(diff > 0) { // new item is smaller than the Nodekey2
                insert(root->middle,TreeNode);
            }

            else { // new item is larger than the
                // Nodekey2
                insert(root->right,TreeNode);
            }
        }

        return TreeNode;
    }

    //////////////////// to firas : tbh i am a bit sciptical about the delete i don't think it working correctly
    ///////////////// also i've noticed that you did not use merge function that we have talked about it in the zoom , please try to do it and use it in the code
    /// as soon as possible so we can start testing the removeArtist function !!!!!!
    ////////////// to mostafa : sure i am trying to think about the merge i studied the lectures again and the tutorials
    ///////////// still can not figure it out i don't think that i have understood the algorithm correctly , can you try to code it ? and help me to understand it ?
    //////////// to firas : i also did not understand how can we merge the nodes and update i am gonna ask roi
    ////////// to fiars : i know that we talked about the delete func at the zoom meeting i tried to program it before but i also asked you to do it so i can test the insert
    ////////// please add some comments to the code i can't seem to understand it 100% , add cases if it has 1 son 2 or 3 sons so i can totally understand what is going on
    /////////// to mos : i think that the delete func is not completed i think i have missed some cases send you a whatsapp message about it

    TwoThreeNode<D,K> DeleteFuncWrapper(TwoThreeNode<D,K>* firstNode, K* Data1, TwoThreeNode<D,K>* secondNode,K* Data2, int size)
    {
        int tempdone = 1;
        TwoThreeNode<D,K>* deletedNode = firstNode;
        TwoThreeNode<D,K>* newNode ;


        if (firstNode != NULL && Data1 != NULL && Data2 != NULL)
        {
            if (firstNode->left != NULL && size >=0)
            {
                TwoThreeNode<D,K> deletedNode(NULL);

                if (firstNode->n == 1 && Data1 && size >=0)
                {
                    TwoThreeNode<D,K> newNode(NULL);
                    if (Data1 != firstNode->value1)
                        if (Data1 < firstNode->value1 && size>=0)
                        {
                            TwoThreeNode<D,K> returnedNode(NULL);
                            returnedNode = DeleteFuncWrapper(firstNode->left, Data1, firstNode, Data2, size);
                            newNode = returnedNode;
                        }
                        else{
                            TwoThreeNode<D,K> returnedNode(NULL);
                            returnedNode = DeleteFuncWrapper(firstNode->middle, Data1, firstNode, Data2, size);
                            newNode = returnedNode;
                        }
                    if (newNode.child == NULL)
                        return newNode;
                }
                deletedNode=newNode;
            }


            if (root->n == 0 && size>=0)
            {

                root->left = NULL;
                root->middle = NULL;
                root->right = NULL;
                delete root;
                root = deletedNode.child;
                firstNode = root;
                return (NULL);
            }

            TwoThreeNode<D,K>* current;
            K* temp;

            if ((firstNode->n == 2) && (firstNode->value2 == Data1) && size >=0)
            {
                temp = firstNode->value2;
                secondNode = firstNode;
                K* temp2 = temp;
                current = firstNode->middle;

                while (current->left != NULL && size >=0)
                {
                    secondNode = current;
                    if (current->n == 1)
                        current = current->middle;
                    else
                    {
                        tempdone=1;
                        current = current->right;
                    }
                }
                if (current->n == 1 && size >=0)
                {
                    tempdone=1;
                    firstNode->value2 = current->value1;
                    current->value1 = temp;
                    size--;
                }
                else
                {
                    tempdone=1;
                    firstNode->value2 = current->value2;
                    current->value2 = temp;
                    size--;
                }
            }
            else
            {
                temp = firstNode->value1;
                current = firstNode->left;
                secondNode = firstNode;
                size--;
                while (current->left != NULL && size >=0)
                {
                    secondNode = current;
                    if (current->n == 1)
                        current = current->middle;
                    else
                    {
                        current = current->right;
                    }
                }
                size++;
                if (current->n == 1 && size >=0){
                    firstNode->value1 = current->value1;
                    current->value1 = temp;
                    size--;
                }
                else if (current->n == 2)
                {
                    firstNode->value1 = current->value2;
                    current->value2 = temp;
                    size--;
                }
            }
            current->n--;
            firstNode = current;
        }
        /////////////////////// mostafa there is some missing cases here please work on it !!
        return (NULL);
    }

};


#endif //WET1_MUSICMANAGER_H