
//
// Hash Table
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Each hash entry stores a key, object pair
struct HashTableVoidEntry {
  char * _key;
  void * _data;
  HashTableVoidEntry * _next;
};

// This is a Hash table that maps string keys to objects of type Data
class HashTableVoidS {
 public:
  // Number of buckets
  enum { TableSize = 2039};
  
  // Array of the hash buckets.
  HashTableVoidEntry **_buckets;
  
  // Obtain the hash code of a key
  int hash( char * key);
  
 public:
  HashTableVoidS();
  
  // Add a record to the hash table. Returns true if key already exists.
  // Substitute content if key already exists.
  bool insertItem(  char * key, void * data);

  // Find a key in the dictionary and place in "data" the corresponding record
  // Returns false if key is does not exist
  bool find(  char * key, void ** data);

  // Removes an element in the hash table. Return false if key does not exist.
  bool removeElement( char * key);
  bool exists(  char * key);
  bool check(  char * key, char * data);
};

class HashTableVoidIterator {
  int _currentBucket;
  HashTableVoidEntry *_currentEntry;
  HashTableVoidS * _hashTable;
 public:
  HashTableVoidIterator(HashTableVoidS * hashTable);
  bool next( char * & key, void * & data);
};

