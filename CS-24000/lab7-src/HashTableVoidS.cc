    #include <stdlib.h>
    #include <string.h>
    #include "HashTableVoidS.h"

    // Obtain the hash code of a key
    int HashTableVoidS::hash( char * key)
    {
        int sum = 0;
        char * k = strdup(key);
        while (*k) {
            sum += *k;
            k++;
        }
        return sum % TableSize;
    }

    // Constructor for hash table. Initializes hash table
    HashTableVoidS::HashTableVoidS()
    {
        _buckets = (HashTableVoidEntry **) malloc(TableSize*sizeof(HashTableVoidEntry*));
        for ( int i = 0; i < TableSize; i++) {
        _buckets[i] = NULL; 

        }
    }

    // Add a record to the hash table. Returns true if key already exists.
    // Substitute content if key already exists.
    bool HashTableVoidS::insertItem(  char * key, void * data)
    {
    // Get hash bucket
        int h = hash(key);
        HashTableVoidEntry * e = _buckets[h];
        while (e!=NULL) {
        if (!strcmp(e->_key, key)) {
    // Entry found 
            e->_data = data;
                return true;
            }
            e = e->_next;
            }
            // Entry not found. Add it.
            e = new HashTableVoidEntry; e->_key = strdup(key); e->_data = data; e->_next = _buckets[h];
        _buckets[h] = e;
        return false;
    }

    // Find a key in the dictionary and place in "data" the corresponding record
    // Returns false if key is does not exist
    bool HashTableVoidS::find(  char * key, void ** data)
    {
    // Get hash bucket
    int h = hash(key);
    HashTableVoidEntry * e = _buckets[h];
    while (e!=NULL) {
    if (!strcmp(e->_key, key)) {
    // Entry found
    *data = e->_data;
    return true;
    }
    e = e->_next;
    }
    return false;
    }
    bool HashTableVoidS::exists(  char * key)
    {
    // Get hash bucket
    int h = hash(key);
    HashTableVoidEntry * e = _buckets[h];
    while (e!=NULL) {
    if (!strcmp(e->_key, key)) {
    // Entry found
    // *data = e->_data;
    return true;
    }
    e = e->_next;
    }
    return false;
    }
    bool HashTableVoidS::check(  char * key, char * data)
    {
    // Get hash bucket
    int h = hash(key);
    HashTableVoidEntry * e = _buckets[h];
    while (e!=NULL) {
    if (!strcmp(e->_key, key)) {
    // Entry found
    // *data = e->_data;
    if(!strcmp((char*)e->_data, (char*)data)){
        return true;
    }
    else{
        return false;
    }
    //return true;
    }
    e = e->_next;
    }
    return false;
    }

    // Removes an element in the hash table. Return false if key does not exist.
    bool HashTableVoidS::removeElement( char * key)
    {
// Get hash bucket
    int h = hash(key);
    HashTableVoidEntry * e = _buckets[h];
    HashTableVoidEntry * prev = NULL;
    while (e!=NULL) {
    if (!strcmp(e->_key, key)) {
    // Entry found
    if (prev != NULL) {
    prev->_next = e->_next;
    }
    else {
    _buckets[h] = e->_next;
    }
    //free(e->_key);
    delete e;
    return true;
    }
    prev = e;
    e = e->_next;
    }
    return false;
    }

    // Creates an iterator object for this hash table
    HashTableVoidIterator::HashTableVoidIterator(HashTableVoidS * hashTable)
    {
        _hashTable = hashTable;
        _currentBucket = 0;
        _currentEntry = NULL;
    }

    // Returns true if there is a next element. Stores data value in data.
    bool HashTableVoidIterator::next( char * & key, void * & data)
    {
		if(key != NULL){
			_currentBucket = _hashTable->hash(key);
		}
        _currentEntry = _hashTable->_buckets[_currentBucket];
        if (_currentEntry != NULL && _currentEntry->_next != NULL)
        {
            key = _currentEntry->_next->_key;
            data = _currentEntry->_next->_data;
            
            _currentEntry = _currentEntry->_next;
            
            return true;
        }
        
        
        _currentBucket ++;
        
        while (_hashTable->_buckets[_currentBucket] == NULL
			&& _currentBucket < _hashTable->TableSize 
               )
        {
            _currentBucket++;
        }
        
        if ( _hashTable->_buckets[_currentBucket] != NULL &&
			_currentBucket < _hashTable->TableSize 
              )
        {
            key = _hashTable->_buckets[_currentBucket]->_key;
            data = _hashTable->_buckets[_currentBucket]->_data;
            _currentEntry = _hashTable->_buckets[_currentBucket];
        
            return true;
        }
        
        return false;
    }