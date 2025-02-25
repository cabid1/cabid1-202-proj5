#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  // Required
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  // Required
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue<T>& operator= (Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
  void Push(const T&);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  // Required
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  // Required (used only for testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  // Required
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  // Required
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  // Required
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T&);
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Required
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  // Required
  void Clear();
  // Name: At
  // Precondition: Existing Lqueue
  // Postcondition: Returns object from Lqueue at a specific location
  // Desc: Iterates to node x and returns data from Lqueue
  // Required
  T At (int x);
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Lqueue Class Here***********
//**********All Functions Are Required Even If Not Used for Trivia**************
// Name: Lqueue() (Linked List Queue) - Default Constructor
// Desc: Used to build a new linked queue (as a linked list)
// Preconditions: None
// Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
// Required
template <class T>
Lqueue<T> :: Lqueue(){
    m_size =0;
    m_head = nullptr;
    m_tail = nullptr;
}
// Name: ~Lqueue() - Destructor
// Desc: Used to destruct a Lqueue
// Preconditions: There is an existing lqueue with at least one node
// Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
// Required
template <class T>
Lqueue<T> ::~Lqueue(){
    Node<T>* curr = m_head->GetNext();
    while(curr != nullptr){//goes through ll deletes m_head then
        delete m_head;
        m_head = curr;
        curr = curr->GetNext();
    }
    delete m_head;
    m_size = 0;
}
// Name: Lqueue (Copy Constructor)
// Preconditions: Creates a copy of existing LQueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
// Required
template <class T>
Lqueue<T> ::Lqueue(const Lqueue& copy){
    m_size = 0;
    if(copy.m_size == 0){
        m_size = 0;
        m_head = nullptr;
        m_tail = nullptr;
    }else {
        m_head = new Node<T>(copy.m_head->GetData());
        m_size = copy.m_size;
        Node<T> *curr = copy.m_head->GetNext();
        Node<T> *creating = m_head;
        while(curr != nullptr){
            Node<T> * temp = new Node<T>(curr->GetData());
            creating->SetNext(temp);
            m_tail = creating;
            creating= creating->GetNext();
            curr = curr->GetNext();
        }
    }
}
// Name: operator= (Overloaded Assignment Operator)
// Preconditions: Copies an Lqueue into an existing Lqueue
//                Requires a Lqueue
// Postconditions: Copy of existing Lqueue
// Required
template <class T>
Lqueue<T>& Lqueue<T> ::operator= (Lqueue& assign) {
    if (this != &assign) { //protection against self-assignment
        this->Clear();
        m_size = assign.m_size;
        m_head = new Node<T>(assign.m_head->GetData());
        Node<T> *curr = assign.m_head->GetNext();
        Node<T> *creating = m_head;
        while(curr != nullptr){
            Node<T> * temp = new Node<T>(curr->GetData());
            creating->SetNext(temp);
            m_tail = creating;
            creating= creating->GetNext();
            curr = curr->GetNext();
        }
    }
    return *this; //return this
}
// Name: Push
// Preconditions: Takes in data. Creates new node.
//                Requires a Lqueue
// Postconditions: Adds a new node to the end of the lqueue.
// Required
template <class T>
void Lqueue<T> ::Push(const T& data){
    Node<T> *next = new Node<T>(data);
    if(m_head == nullptr){// checks if empty
        m_head = next;//sets beginning and end of ll to data
        m_tail = next;
    }else{
        Node<T> *curr = m_head;
        Node<T> *previous;
        while(curr != nullptr){//goes through ll until cur is null
            previous = curr;
            curr = curr->GetNext();
        }
        previous->SetNext(next);//sets the last
        m_tail = next;
    }
    ++m_size; // update size

}
// Name: Pop
// Preconditions: Lqueue with at least one node.
// Postconditions: Removes first node in the lqueue, returns data from first node.
// Required 1->2->3 becomes 2->3 return 2
template <class T>
T Lqueue<T> :: Pop(){
    if(m_head == nullptr){//if ll is empty
        return NULL;
    }else {
        Node<T> *curr = m_head;
        Node<T> *next;
        if(curr->GetNext() != nullptr){//if the next item in ll is not empty
            next = curr->GetNext();
            delete curr;
            m_head = next;
            --m_size; //update size
            return next->GetData();
        }else{// if the second item in ll is empty only one item in ll
            delete m_head;
            m_head = nullptr;
            --m_size; //update size
            return NULL;
        }
    }

}
// Name: Display
// Preconditions: Outputs the lqueue.
// Postconditions: Displays the data in each node of lqueue
// Required (used only for testing)
template <class T>
void Lqueue<T> :: Display(){
    int count = 1;
    if(m_head == nullptr){// if ll is empty
        cout << "ll is empty" << endl;
    }
    else {
        Node<T> *curr = m_head;
        while (curr != nullptr){//goes through ll while not at end of ll
            cout << count << ". " <<curr->GetData() << endl;// displays ll data
            count++;
            curr = curr->GetNext();
        }
    }
}
// Name: Front
// Preconditions: Requires a populated lqueue
// Postconditions: Returns whatever data is in front
// Required
template <class T>
T Lqueue<T> :: Front(){
    if(m_head == nullptr){
        cout << "ll is empty" << endl; // check if this needs to return nullptr or this mess
    }else{
        return m_head->GetData();
    }
}
// Name: IsEmpty
// Preconditions: Requires a lqueue
// Postconditions: Returns if the lqueue is empty.
// Required
template <class T>
bool Lqueue<T> :: IsEmpty(){
    if(m_head == nullptr){
        return true;
    }else{
        return false;
    }
}
// Name: GetSize
// Preconditions: Requires a lqueue
// Postconditions: Returns m_size
// Required
template <class T>
int  Lqueue<T> ::GetSize() {
    return m_size;
}
// Name: Find()
// Preconditions: Requires a lqueue
// Postconditions: Iterates and if it finds the thing, returns index, else -1
// Required 0123
template <class T>
int Lqueue<T> :: Find(T& thing){
    int index = 0;
    if(m_head == nullptr){//if empty
        return -1;
    }else{
        Node<T> *curr = m_head;
        while(curr != nullptr){
            if(curr->GetData() == thing){
                return index;
            }
            index++;
            curr = curr->GetNext();
        }
}
   return -1;
}
// Name: Swap(int)
// Preconditions: Requires a lqueue
// Postconditions: Swaps the nodes at the index with the node prior to it.
// Required 1 2 3 given 1 returns  2 1 3
template <class T>
void Lqueue<T> :: Swap(int index){
    if(m_head == nullptr){
        cout << "ll is empty" << endl;
    }else {
        int count = 0;
        Node<T> *curr = m_head;
        Node<T> *pre;
        Node<T> *temp;
        while (curr != nullptr && count != index) {
            count++;
            temp = pre;
            pre = curr;
            curr = curr->GetNext();
        }
        pre->SetNext(curr->GetNext());
        curr->SetNext(pre);
        if (index > 1) {
            temp->SetNext(curr);
        }
    }
}
// Name: Clear
// Preconditions: Requires a lqueue
// Postconditions: Removes all nodes in a lqueue
// Required
template <class T>//
void Lqueue<T> ::Clear(){
    if(m_head != nullptr) {
        Node<T>* curr = m_head->GetNext();
        while(curr != nullptr){//goes through ll deletes m_head then
            delete m_head;
            m_head = curr;
            curr = curr->GetNext();
        }
        m_size = 0;
    }
}
// Name: At
// Precondition: Existing Lqueue
// Postcondition: Returns object from Lqueue at a specific location
// Desc: Iterates to node x and returns data from Lqueue
// Required
template <class T>
T Lqueue<T> ::At(int index){
    int count = 0;
    if(m_head == nullptr){//
        return NULL;
    }else{
        Node<T> *curr = m_head;
        Node<T> *pre;
        while(curr != nullptr){
            pre = curr;
            if(index ==count){
                return curr->GetData();
            }
            count++;
            curr = curr->GetNext();
        }
        if(index== count){
            return pre->GetData();
        }else{
            return NULL;
        }
    }
}
#endif
