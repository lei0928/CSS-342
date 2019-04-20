template <class Object>
Deque<Object>::Deque( ) {                          // the constructor
  front = back = NULL;
}

template <class Object>
Deque<Object>::Deque( const Deque &rhs ) {         // the copy constructor
  front = back = NULL;
  *this = rhs;
}

template <class Object>
Deque<Object>::~Deque( ) {                         // the destructor
  clear( );
}

template <class Object>
bool Deque<Object>::isEmpty( ) const {             // check if a deque is empty
  return front == NULL;
}

template <class Object>
int Deque<Object>::size( ) const {                 // retrieves # deque nodes
  int i = 0;
  for ( DequeNode *ptr = front; ptr != NULL; ptr = ptr->next ) // traverse que
    ++i;

  return i;
}

template <class Object>
const Object &Deque<Object>::getFront( ) const {   // retrieve the front node
  if ( isEmpty( ) )
    throw "empty queue";
  return front->item;
}

template <class Object>
const Object &Deque<Object>::getBack( ) const {    // retrieve the tail node
  if ( isEmpty( ) )
    throw "empty queue";
  return back->item;
}

template <class Object>
void Deque<Object>::clear( ) {          // clean up all entries.
  while ( !isEmpty( ) )                 // dequeue till the queue gets empty.
    removeFront( );
}

template <class Object>
void Deque<Object>::addFront( const Object &obj ) {// add a new node to  front
  DequeNode *newPtr = new DequeNode();
  newPtr->item = obj;
  // arranges links
  newPtr->next = front;
  newPtr->prev = NULL;
  // the new pointer becomes the back when the list is empty
  if(isEmpty()) {
     back = newPtr;
  } else {
     front->prev = newPtr;  // determines where the front is
  }
  front = newPtr;
}

template <class Object>
void Deque<Object>::addBack( const Object &obj ) { // add a new node to tail
  DequeNode *newPtr = new DequeNode();
  newPtr->item = obj;
  // arranges links
  newPtr->next = NULL;
  newPtr->prev = back;
  
  // the new pointer becomes the front when the list is empty
  if(isEmpty()){
     front = newPtr;
  } else {
	 back->next = newPtr;   // determines where the back is
  }
  back = newPtr;
}

template <class Object>
Object Deque<Object>::removeFront( ) {  // remove the front node
  Object frontItem = getFront();
  DequeNode *old = front;
  // if there is only one item in the list
  if(front == back) {
     front = NULL;
     back = NULL;
  } else {
	 //changes links
     front = front->next;
     front->prev = NULL;
  }
  delete old;
  return frontItem;
}

template <class Object>
Object Deque<Object>::removeBack( ) {   // remove the back node
  Object backItem = getBack();
  DequeNode *old = back;
  // if there is only one item in the list
  if(front == back) {
     front = NULL;
     back == NULL;
  } else {
     //changes links
     back = back->prev;
     back->next = NULL;
  }
  delete old;
  return backItem;
}

template <class Object>
const Deque<Object> &Deque<Object>::operator=( const Deque &rhs ) { // assign
  if ( this != &rhs ) { // avoid self assignment
    clear( );
    for ( DequeNode *rptr = rhs.front; rptr != NULL; rptr = rptr->next )
      addBack( rptr->item );
  }
  return *this;
}


