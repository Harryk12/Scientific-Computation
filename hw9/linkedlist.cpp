//Harry Singh Kang   hsk697   hkangt
#include <cmath>

#include <iostream>
using std::cin, std::cout;

#include <memory>
using std::make_shared, std::shared_ptr;

#include <cassert>

class Node; // forward definition

//List class attributes and method declarations
class List {
private:
  shared_ptr<Node> head{nullptr};
public:
  List() {};
  auto headnode() { return head; };
  void insert(int value);
  int length();
  int length_iterative();
  bool contains_value(int v);
  void print();
  //void 
};

//Node class attributes and method declarations
class Node:public std::enable_shared_from_this<Node>{
private:
  int datavalue{0},datacount{0};
  shared_ptr<Node> next{nullptr};
public:
  Node() {};
  Node(int value,shared_ptr<Node> next=nullptr)
    : datavalue(value),datacount(1),next(next) {};
  int value() {
    return datavalue; };
  auto nextnode() {
    return next; };
  int length();
  int count() {
    return datacount; };
  bool has_next() {
    return next!=nullptr; };
  bool contains_value(int v);
  void insert(int value,shared_ptr<Node> head);  //added head to help me parse the list
  void print();
};

int main() {
  //cases
  List mylist;
  cout << "Empty list has length: "
       << mylist.length() << '\n';
  cout << '\n';

  mylist.insert(3);
  cout << "After inserting 3 the length is: "
       << mylist.length() << '\n';

  if (mylist.contains_value(3))
    cout << "Indeed: contains 3" << '\n';
  else
    cout << "Hm. Should contain 3" << '\n';
  if (mylist.contains_value(4))
    cout << "Hm. Should not contain 4" << '\n';
  else
    cout << "Indeed: does not contain 4" << '\n';
  cout << '\n';

  mylist.insert(3);
  cout << "Inserting the same item gives length: "
       << mylist.length() << '\n';

  if (mylist.contains_value(3)) {
    cout << "Indeed: contains 3" << '\n';
    auto headnode = mylist.headnode();
    cout << "head node has value " << headnode->value()
         << " and count " << headnode->count() << '\n';
  } else
    cout << "Hm. Should contain 3" << '\n';
  cout << '\n';
 
  mylist.insert(2);
  cout << "Inserting 2 goes at the head;\nnow the length is: "
       << mylist.length() << '\n';
  if (mylist.contains_value(2))
    cout << "Indeed: contains 2" << '\n';
  else
    cout << "Hm. Should contain 2" << '\n';
  if (mylist.contains_value(3))
    cout << "Indeed: contains 3" << '\n';
  else
    cout << "Hm. Should contain 3" << '\n';
  cout << '\n';

  mylist.insert(6);
  cout << "Inserting 6 goes at the tail;\nnow the length is: "
       << mylist.length()
       << '\n';
  if (mylist.contains_value(6))
    cout << "Indeed: contains 6" << '\n';
  else
    cout << "Hm. Should contain 6" << '\n';
  if (mylist.contains_value(3))
    cout << "Indeed: contains 3" << '\n';
  else
    cout << "Hm. Should contain 3" << '\n';
  cout << '\n';

  mylist.insert(4);
  cout << "Inserting 4 goes in the middle;\nnow the length is: "
       << mylist.length()
       << '\n';
  if (mylist.contains_value(4))
    cout << "Indeed: contains 4" << '\n';
  else
    cout << "Hm. Should contain 4" << '\n';
  if (mylist.contains_value(3))
    cout << "Indeed: contains 3" << '\n';
  else
    cout << "Hm. Should contain 3" << '\n';
  cout << '\n';

  cout << "List has length: " << mylist.length() << '\n';
  cout << '\n';
  mylist.print();

  //other cases
  {
    cout << "Another check.\n";
    List mylist;
    for ( auto i : { 15,23,11,75,11,65,3} ) {
      cout << "insert: " << i << '\n';
      mylist.insert(i);
    }
    mylist.print();
  }

  return 0;
}

/*
 * Compute the length of a list recursively
 * See below for an iterative solution
 */
int List::length() {
  if (head==nullptr)
    return 0;
  else
    return head->length();
};

int Node::length() {
  if (!has_next())
    return 1;
  else
    return 1+next->length();    //these functions are recursive
};

/*
 * Iterative alternative
 * to recursive computation
 */
int List::length_iterative() {
  int count = 0;
  if (head!=nullptr) {
    auto current_node = head;
    while (current_node->has_next()) {
      current_node = current_node->nextnode(); count += 1;
    }
  }
  return count;
};

/*
 * Auxiliary functions
 */
//print functions
void Node::print() {
  cout << datavalue << ":" << datacount;
  if (has_next()) {
    cout << ", "; next->print();
  }
};

void List::print() {
  cout << "List:";
  if (head!=nullptr)
    cout << " => "; head->print();
  cout << '\n';
};

//insert functions
void List::insert(int value){
  if (head==nullptr)
    head=make_shared<Node>(value);
  else head->insert(value,head);
};

void Node::insert(int value,shared_ptr<Node> head){
  if(value==datavalue)     //add counts to redundant numbers
    datacount++;
  else{      //adding new numbers
    auto iter=head;    //parsing list
    auto datavalueholder=value;
    while (iter->next!=nullptr){
      if (iter->next->datavalue > datavalueholder){   //ascending order logic
	auto newiter=make_shared<Node>(datavalueholder);
	newiter->next=iter->next;   //attaching new pointers
	iter->next=newiter;
	return;
      }
      iter=iter->next;
    }
    iter->next=make_shared<Node>(value);   //putting largest last
  };
};

//contains value functions
bool List::contains_value(int v){
  if (head==nullptr)
    return false;
  else
    return head->contains_value(v);
};

bool Node::contains_value(int v){
  if (datavalue==v)
    return true;
  else if (next==nullptr)
    return false;
  else
    return next->contains_value(v);
};
