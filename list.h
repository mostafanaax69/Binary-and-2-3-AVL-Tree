
#ifndef MyPart_LIST_H
#define MyPart_LIST_H

template <class T>
class Node {
public:
    Node* next;
    Node* last;
    T* data;
    int key;

    Node()= default;
    ~Node(){
        key=-1;
        delete (data);
        data= nullptr;
    }



};

template <class T>
class List{
public:
    Node<T>* head;
    int size;
    Node<T>* first;

    List(){
        head= nullptr;
        first = nullptr;
        size=0;

    }
    ~List(){
        Node<T>* tmp=head; // hon ante knt 7att mtsbe3 lmtsb3 node<t>** tmp wmktsh tsht3'l
        while (tmp)
        {
            Node<T>* nextNode = tmp->next ;  // get next node
            delete tmp;                         // delete current
            tmp = nextNode;                     // set current to "old" next
        }

        if(head)
        {
            head = nullptr;
        }

        if(first)
        {
            first = nullptr;
        }

        size = 0 ;

    }

    Node<T>* AddNodebyData(T* data,int key)
    {
        Node<T>* new_node=new Node<T>();
        new_node->data= data;
        new_node->key=key;
        if(head== nullptr)
        {
            first = new_node;
            new_node->next= nullptr;
        }
        else{
            new_node->next=head;
            head->last=new_node;

        }
        size++;
        new_node->last= nullptr;
        head=new_node;

        return new_node;

    }
    Node<T>* AddNodeFirst(Node<T>* pNode,T* data ,int key){
        Node<T>* new_node=new Node<T>();
        new_node->key= 0;
        new_node->data= data;

        if(pNode != nullptr) {
            new_node->last=pNode;
             pNode->next=new_node;
            new_node->next= nullptr;
            first=new_node;
        }
        size++;
        return new_node;
    }
    Node<T>* AddNodeInMid(Node<T>* pNode, T* data ,int key)
    {
        Node<T>* new_node=new Node<T>();
        new_node->key= pNode->key+1;
        new_node->data= data;

        if(pNode->last != nullptr) {
            pNode->last->next = new_node;
            new_node->last = pNode->last;
            pNode->last = new_node;
            new_node->next = pNode;
        }
        else{
            new_node->last = nullptr;
            pNode->last = new_node;
            new_node->next = pNode;
        }


        size++;
        return new_node;

    }


    Node<T>* AddNode(Node<T>* add)
    {
        Node<T>* new_node=add;
        if(head== nullptr)
        {
            new_node->next= nullptr;
            first = new_node;
        } else{
            new_node->next=head;
            head->last=new_node;

        }
        new_node->last= nullptr;
        size++;
        head=new_node;

        return new_node;// return new_node bnf3sh

    }

    bool ListContains(int key)
    {
        Node<T>* temp=head;
        while (temp!= nullptr)
        {
            if(temp->key == key)
            {
                return true;
            }
            temp=temp->next;
        }

        return false;
    }

    Node<T>* find(int key)
    {
        Node<T>* temp=head;
        while (temp)
        {
            if(temp->key == key)
                return temp;
            temp = temp->next;

        }
        return nullptr;
    }

    bool DeleteNode(int key)
    {
        Node<T>* temp=head;
        while (temp)
        {
            if(temp->key == key)
            {
              if(temp==head) // delete head
              {
                  if(head==first)
                      first= nullptr;
                  head=head->next;
                  if(head)
                  {
                      head->last= nullptr;
                  }
                  delete(temp);
                  size--;
                  temp= nullptr;
                  return true;
              } else{
                  if(temp->next != nullptr) { // delete node from the middle
                      temp->next->last = temp->last;
                      temp->last->next = temp->next;
                      delete temp;
                      size--;
                      temp= nullptr;
                      return true;
                  } else{ // delete last node
                      first = first->last;
                      temp->last->next= nullptr;
                      delete temp;
                      size--;
                      temp= nullptr;
                      return true;
                  }

              }
            }
            temp=temp->next;
        }
        return false;

    }

    void removeNode(Node<T>* node)
    {
        if(node== nullptr)
            return;
        Node<T>* temp=head;
        while (temp)
        {
            if(temp->key == node->key)
            {
                if(temp==head) // delete head
                {
                    if(head == first){
                        delete(temp);
                        temp= nullptr;
                        first= nullptr;
                        size--;
                        return;
                    }
                    head=head->next;
                    if(head)
                    {
                        head->last= nullptr;
                    }
                    delete(temp);
                    size--;
                    return;
                } else{
                    if(temp->next != nullptr) { // delete node from the middle
                        temp->next->last = temp->last;
                        temp->last->next = temp->next;
                        delete(temp);
                        size--;
                        return;
                    } else{ // delete last node
                        temp->last->next= nullptr;
                        first=first->last;
                        delete(temp);
                        temp= nullptr;
                        size--;
                        return;
                    }

                }
            }
            temp=temp->next;

        }


    }




};



#endif //UNTITLED37_LIST_H
