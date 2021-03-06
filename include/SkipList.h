#ifndef _SkipList_H
#define _SkipList_H

#include <iostream>

/*
  SkipList.h

  See: Pugh, William,  "Skip Lists: A Probabilistic Alternative to Balanced Trees"

*/
#include <limits.h> // INT_MAX
#include <SkipListElement.h>

#define SKIPLIST_NOT_FOUND -1
// INT_MAX
// Was: -1

class SkipListElement;
// class ostream;

/**
 * Note: Keys are presumed positive in this formulation.
 */
class LINKAGE SkipList{
public:

	/* ITERATOR SUPPORT */
	/**
	 * Reset the iterator iter to the header's zeroth element.
	 */
	void reset() {
		iter = myHeader->getElement(0);
	}
	/// Set iter to the next element, returning True if it exists.
	int step() {
		iter = iter->getElement(0); return (iter != NIL);}
	/// TODO redo the getkey to something like bool getkey(Key &key)...
	Key getkey() {
		if (iter != NIL)
			return iter->getKey();
		else
			return (Key) -1; // TODO Rethink using a Key as a symbol -- only positive Keys? There are KEY_MAX and KEY_MIN and KEY_MIN < 0.
	}
	Value getvalue() {
		if (iter != NIL)
			return iter->getValue();
		else
			return (Value) -1;
	}
	Key getNthKey(const int n){
		int n_now = n-1;
		iter = myHeader->getElement(0);
		while(n_now > 0){
			if (iter == NIL)
				break;
			iter = iter->getElement(0);
			n_now--;
		}
		if (iter != NIL)
			return iter->getKey();
		return (Key) -1;
	}

	SkipList(float probability = 0.5);
	~SkipList();

	void insert(const Key searchKey, const Value value); // insert new element
	Value searchAlt(const Key searchKey); // search element with key
	Value search(const Key searchKey, const int iterator_flag); // search element with key
	Value search(const Key searchKey); // search element with key
	Key findMAX(const Key searchKey) const; // search element with key NGT searchKey
	Key findMIN(const Key searchKey) const; // search element with key NLT searchKey
	void list(ostream & os);	// List to stream


  void free(const Key searchKey); // free element with key
  void freeRange(const Key loKey, const Key hiKey);
  void freeAll();

  void stat(); // statistics;
  long getLength() {
    return myLength;
  }
  long getCount() ;

  friend ostream& operator<<(ostream& os, const SkipList& list);

  SkipListElement* myHeader; // the header (first) list element
  float myProbability;

private:
  SkipListElement* iter;
  long myLength;
};

#endif // _SkipList_H
