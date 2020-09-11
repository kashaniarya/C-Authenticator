// HashMap.cpp
//
// ICS 45C Fall 2018
// Project #3: Maps and Legends


#include "HashMap.hpp"
#include <functional>
#include <string>

namespace {
    unsigned int hashFunc(const std::string& key) {
        unsigned int num = 0;
        for(int i=0; i < key.length(); i++) {
            num += int(key[i]);
        }
        return num;
    }
}


// This constructor initializes the HashMap to use whatever default
// hash function you'd like it to use.  A little research online will
// yield some good ideas about how to write a good hash function for
// strings; don't just return zero or, say, the length of the string.
HashMap::HashMap() {
    hasher = hashFunc;
    hashTable = new Node*[initialBucketCount];
    amountOfBuckets = initialBucketCount;
    sz = 0;
    for(int i=0; i < amountOfBuckets; i++) {
        hashTable[i] = nullptr;
    }
}
    
// This constructor instead initializes the HashMap to use a particular
// hash function instead of the default.  (We'll use this in our unit
// tests to control the scenarios more carefully.)
HashMap::HashMap(HashFunction hasher) {
    this->hasher = hasher; 
    hashTable = new Node*[initialBucketCount];
    amountOfBuckets = initialBucketCount;
    sz = 0;
    for(int i=0; i < amountOfBuckets; i++) {
        hashTable[i] = nullptr;
    }
}

// The "Big Three" need to be implemented appropriately, so that HashMaps
// can be created, destroyed, copied, and assigned without leaking
// resources, interfering with one another, or causing crashes or
// undefined behavior.
HashMap::HashMap(const HashMap& hm) {
    hasher = hm.hasher;
    hashTable = new Node*[hm.amountOfBuckets];
    amountOfBuckets = hm.amountOfBuckets;
    sz = hm.sz;
    for(int i=0; i < hm.amountOfBuckets; i++) {
        hashTable[i] = hm.hashTable[i];
    }
}

HashMap::~HashMap() {
    for(int i=0; i < amountOfBuckets; i++) {
        while(hashTable[i] != nullptr) {
            Node* currentHeadNode = hashTable[i];
            hashTable[i] = currentHeadNode->next;
            delete currentHeadNode;
        }
    }
    delete[] hashTable;
}


 void HashMap::add_to_end(Node* n1, std::string k, std::string v) {

    Node* temp = n1;
    if(temp == nullptr) {
        n1 = new Node();
        n1->key = k;
        n1->value = v;
        n1->next = nullptr;
    }
    else {
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new Node();
        temp->next->key = k;
        temp->next->value = v;
        temp->next->next = nullptr;
    }
}


void HashMap::copy_ll(Node* n1, Node* n2) {
    Node* temp = n1;
    while(temp != nullptr) {
        add_to_end(n2, temp->key, temp->value);
        temp = temp->next;
    }
}



HashMap& HashMap::operator=(const HashMap& hm) {
    if (this != &hm) {
        Node** hT = new Node*[hm.amountOfBuckets];


        for(int i = 0; i < hm.amountOfBuckets; i++) {
            //hT[i] = hm.hashTable[i];
            copy_ll(hm.hashTable[i], hT[i]);
        }


        hasher = hm.hasher;
        sz = hm.sz;


        for(int i=0; i < amountOfBuckets; i++) {
            while(hashTable[i] != nullptr) {
                Node* currentHeadNode = hashTable[i];
                hashTable[i] = currentHeadNode->next;
                delete currentHeadNode;
            }
        }
        delete[] hashTable;

        hashTable = hT;
        amountOfBuckets = hm.amountOfBuckets;
    }
    return *this;
}


// contains() returns true if the given key is in this HashMap, false
// if not.
bool HashMap::contains(const std::string& key) const {
    Node* currentHeadNode = hashTable[hasher(key) % amountOfBuckets];
    while(currentHeadNode != nullptr) {
        if(currentHeadNode->key == key) {
            return true;
        }
        currentHeadNode = currentHeadNode->next;
    }
    return false;    
}


// loadFactor() returns the proportion of the number of key/value pairs
// to the number of buckets, a measurement of how "full" the HashMap is.
// For example, if there are 20 key/value pairs and 50 buckets, we would
// say that the load factor is 20/50 = 0.4.
double HashMap::loadFactor() const {
    double returnValue = 1.0 * sz / amountOfBuckets;
    return returnValue;
}


// add() takes a key and a value.  If the key is not already stored in
// this HashMap, the key/value pair is added; if the key is already
// stored, the function has no effect.
//
// If adding the new key/value pair will cause the load factor of this
// HashMap to exceed 0.8, the following must happen:
//
// (1) The number of buckets should be increased by doubling it and
//     adding 1 (i.e., if there were 10 buckets, increase it to
//     2 * 10 + 1 = 21).
// (2) All key/value pairs should be rehashed into their new buckets,
//     important because changing the number of buckets will likely
//     change which bucket a particular key hashes to (especialy if
//     you're using % to determine the index of that bucket).
void HashMap::add(const std::string& key, const std::string& value) {
    if(HashMap::contains(key) == false) {
        unsigned int numberLocation = hasher(key) % amountOfBuckets;
        Node* headNode = hashTable[numberLocation];
        Node* newNode = new Node();
        newNode->key = key;
        newNode->value = value;
        newNode->next = nullptr;
        if(headNode == nullptr) {
            hashTable[numberLocation] = newNode;
        } 
        else {
            while(headNode->next != nullptr) {
                headNode = headNode->next;
            }
            headNode->next = newNode;
        }
        sz += 1;
        if(HashMap::loadFactor() > 0.8) {
            unsigned int old_amountOfBuckets = amountOfBuckets;
            amountOfBuckets = amountOfBuckets * 2 + 1;
            Node** hT = new Node*[amountOfBuckets];
            for(int i=0; i < amountOfBuckets; i++) {
                hT[i] = nullptr;
            }
            
            for(int i=0; i < old_amountOfBuckets; i++) {
                Node* currentHeadNode = hashTable[i];
                while(currentHeadNode != nullptr) {
                    unsigned int new_numberLocation = hasher(currentHeadNode->key) % amountOfBuckets;
                    Node* new_headNode = hT[new_numberLocation];
                    Node* new_newNode = new Node();
                    new_newNode->key = currentHeadNode->key;
                    new_newNode->value = currentHeadNode->value;
                    new_newNode->next = nullptr;
                    if(new_headNode == nullptr) {
                        hT[new_numberLocation] = new_newNode;
                    } 
                    else {
                        while(new_headNode->next != nullptr) {
                            new_headNode = new_headNode->next;
                        }
                        new_headNode->next = new_newNode;
                    }
                    currentHeadNode = currentHeadNode->next;
                }
            }
            
            for(int i=0; i < old_amountOfBuckets; i++) {
                while(hashTable[i] != nullptr) {
                    Node* currentHeadNode = hashTable[i];
                    hashTable[i] = currentHeadNode->next;
                    delete currentHeadNode;
                }
            }
            
            delete[] hashTable;
            hashTable = hT;
        }
    }
}


// remove() takes a key and removes it (and its associated value) from
// this HashMap if it is already present; if not, the function has no
// effect.
void HashMap::remove(const std::string& key) {
    if(HashMap::contains(key) == true) {
        int numberLocation = hasher(key) % amountOfBuckets;
        Node* currentHeadNode = hashTable[numberLocation];
        if(currentHeadNode->key == key) {
            Node* tempNode = currentHeadNode;
            if(currentHeadNode->next == nullptr) {
                hashTable[numberLocation] = nullptr;
            }
            else {
                hashTable[numberLocation] = currentHeadNode->next;
            }
            delete tempNode;
        }
        else {
            Node* old_node;
            while(currentHeadNode->key != key) {
                old_node = currentHeadNode;
                currentHeadNode = currentHeadNode->next;
            }
            if(currentHeadNode->next == nullptr) {
                old_node->next = nullptr;
                delete currentHeadNode;
            }
            else{
                old_node->next = currentHeadNode->next;
                delete currentHeadNode;
            }
        }
        sz -= 1;
    }
}



// value() returns the value associated with the given key in this HashMap
// if the key is stored in this HashMap; if not, the empty string is
// returned.  (Going forward, we'll discover that throwing an exception
// is a better way to handle the scenario where the key is not present,
// but we'll conquer that at a later date.)
std::string HashMap::value(const std::string& key) const {
    Node* currentHeadNode = hashTable[hasher(key) % amountOfBuckets];
    while(currentHeadNode != nullptr) {
        if(currentHeadNode->key == key) {
            return currentHeadNode->value;
        }
        currentHeadNode = currentHeadNode->next;
    }
    return "";
}


// size() returns the number of key/value pairs stored in this HashMap.
unsigned int HashMap::size() const {
    return sz;
}

// bucketCount() returns the number of buckets currently allocated in
// this HashMap.
unsigned int HashMap::bucketCount() const {
    return amountOfBuckets;
}



// maxBucketSize() returns the number of key/value pairs stored in this
// HashMap's largest bucket.
unsigned int HashMap::maxBucketSize() const {
    int maxBucketSize = 0;
    for(int i=0; i < amountOfBuckets; i++) {
        int temp = 0;
        Node* currentHeadNode = hashTable[i];
        while(currentHeadNode != nullptr) {
            temp += 1;
            currentHeadNode = currentHeadNode->next; 
        }
        if(temp > maxBucketSize) {
            maxBucketSize = temp;
        }
    }
    return maxBucketSize;
}

void HashMap::clear_and_remove_all() {
    for(int i=0; i < amountOfBuckets; i++) {
        while(hashTable[i] != nullptr) {
            Node* n = hashTable[i];
            HashMap::remove(n->key);
        }
    }
}



