#include <iostream>
#include <set>
#include <ctime>

using namespace std;

template <class T>
class LList;

template <class T>
class LListItr;

template <class T>
class LListNode
{
	LListNode<T>* prev;
	T data;
	LListNode<T>* next;
public:
	LListNode(const T& newdata=T(), LListNode<T>* newp =NULL, LListNode<T>* newn = NULL):
	  data(newdata), next(newn), prev(newp){}
	  friend class LList<T>;
	  friend class LListItr<T>;
};

template <class T>
class LListItr
{
	LListNode<T>* ptr;
public:
	LListItr(): ptr(NULL) {};
	LListItr(LListNode<T>* newPtr): ptr(newPtr){}
	T& operator*() {return ptr->data;}
	LListNode<T>* returnNode() { return ptr; }
	LListItr<T>& operator++();
	LListItr<T> operator++(int);
	LListItr<T>& operator--();
	LListItr<T> operator--(int);
	bool operator==(const LListItr<T>& rhs){return ptr == rhs.ptr;}
	bool operator!=(const LListItr<T>& rhs){return !(*this == rhs);}
	friend class LList<T>;
};

template <class T>
LListItr<T>& LListItr<T>::operator++()
{
	if(ptr && ptr->next)
		ptr = ptr->next;
	return *this;
}

template <class T>
LListItr<T> LListItr<T>::operator++(int)
{
	LListItr<T> temp = *this;
	if(ptr && ptr->next)
		ptr = ptr->next;
	return temp;
}

template <class T>
LListItr<T>& LListItr<T>::operator--()
{
	if(ptr && ptr->next)
		ptr = ptr->prev;
	return *this;
}

template <class T>
LListItr<T> LListItr<T>::operator--(int)
{
	LListItr<T> temp = *this;
	if(ptr && ptr->next)
		ptr = ptr->prev;
	return temp;
}

template <class T>
class LList
{
	LListNode<T>* head;
	LListNode<T>* tail;
	size_t s;
	LListItr<T> recursiveFind(const T& toFind, LListNode<T>* start=head); 
public:
	LListItr<T> begin(){return head->next;} //implicit constructor
	LListItr<T> end(){return tail;}
	void push_back(const T& newData) {insertAfter(tail->prev, newData);}
	size_t size() const {return s;}
	bool isEmpty() {return s == 0;}
	void clear(){while( !isEmpty()) pop_back();}

	LList();
	~LList();
	void push_front(const T& newData);
	void insertAfter(LListItr<T>, const T& newData);
	void remove(LListItr<T>);
	T pop_back();
	T pop_front();
	LList(const LList<T>& rhs);
	LList<T>& operator=(const LList<T>& rhs);
	LListItr<T> find(const T& tofind ){return recursiveFind(tofind,head->next);}
	void sort();
	void moveToHead(const T& element );
	LListNode<T>* returnNode(size_t );
	bool identicalLists(LList<T>* , LList<T>* );
	void backlink();
};
template <class T>
void LList<T>::sort()
{
	multiset<T> temp;
	for (LListItr<T> i = begin(); i!=end(); i++)
		temp.insert(*i);
	multiset<T>::iterator msi = temp.begin();
	for (LListNode<T>* i = head->next; i!=tail; i = i->next,msi++)
		i->data = *msi;
}
template <class T>
LListItr<T> LList<T>::recursiveFind(const T& toFind, LListNode<T>* start)
{
	if (start==NULL)
		return tail;
	else if(start->next==NULL)
		return tail;
	else if (start->data==toFind)
		return start;
	else
		return recursiveFind(toFind, start->next);
}

template <class T>
LList<T>& LList<T>::operator=(const LList<T>& rhs)
{
	if(this==&rhs)
		return *this;
	clear();
	for (LListNode<T>* temp = rhs.head->next; temp !=rhs.tail; temp=temp->next)
		push_back(temp->data);
	return *this;
}

template <class T>
LList<T>::LList(const LList<T>& rhs)
{
	head = new LListNode<T>;
	tail = new LListNode<T>;
	head->next = tail;
	tail->prev = head;    
	s=0;
	*this=rhs;
}



template <class T>
LList<T>::LList()
{
	/*
	head = new LListNode<T>(T(), NULL, new LListNode<T>);
	tail = head->next;
	tail->prev = head;
	*/
	head = new LListNode<T>;
	tail = new LListNode<T>;
	head->next = tail;
	tail->prev = head;  
	s=0;
}

template <class T>
LList<T>::~LList()
{
	clear();
	delete head;
	delete tail;
}

template <class T>
void LList<T>::push_front(const T& newData)
{
	insertAfter(head, newData);
}

template <class T>
void LList<T>::insertAfter(LListItr<T> loc, const T& newData)
{
	loc.ptr->next = new LListNode<T>(newData, loc.ptr, loc.ptr->next);
	loc.ptr->next->next->prev = loc.ptr->next;
	s++;
}

template <class T>
void LList<T>::remove(LListItr<T> loc) 
{
	if (loc.ptr == head || loc.ptr==tail)
		return;
	LListNode<T>* temp = loc.ptr;

	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	delete temp;
	s--;
}

template <class T>
T LList<T>::pop_back()
{
	if(isEmpty())
		return T();
	T retval = tail->prev->data;
	remove(tail->prev);
	return retval;
}

template <class T>
T LList<T>::pop_front()
{
	if(isEmpty())
		return T();
	T retval = head->next->data;
	remove(head->next);
	return retval;
}

int main()
{
	LList<int> l;
	srand(time(NULL));
	for(int i = 0; i < 10; i++ )
		l.push_back(i);

	l.moveToHead(4);

	cout<<"Did it crash?"<<endl;
}

//QUESTION 1///////////////////////////////////////////////////////////
template<class T>
void LList<T>::moveToHead(const T& element) {

	/*LListItr<T> node = recursiveFind(element, head);	
	LListNode<T>* temp = node.returnNode();
	if( temp != head ) {
		push_front(
		head->prev->next = head ->next;
		head->next->prev = head ->prev;
	}*/

	LListItr<T> node = recursiveFind(element, head);

	if( node.ptr != head ) {
		LListNode<T>* temp = node.ptr;
		
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		
		push_front(element);
		remove(node);
	}

}
////////////////////////////////////////////////////////////////////////

//QUESTION 2////////////////////////////////////////////////////////////
template<class T>
bool LList<T>::identicalLists(LList<T>* listOne, LList<T>* listTwo) {
	LListNode<T> *temp, *temp2;
	temp = listOne->head; temp2 = listTwo->head;
	while( true ) {
		if ( temp->data == temp2->data ) {
			listOne->head = temp->next;
			listTwo->head = temp2->next;
			identicalLists(listOne, listTwo);
			break;
		}
		else
			return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////

//QUESTION 3/////////////////////////////////////////////////////////////
template<class T>
void LList<T>::backlink() {
	LListNode<T> *curr, *prev;
	
	curr = this->head;
	while( curr != NULL ) {
		curr = curr->next;
		prev = curr->prev;
		prev = prev->next;
	}

}
/////////////////////////////////////////////////////////////////////////