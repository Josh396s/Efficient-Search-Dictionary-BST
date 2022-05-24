//**********************************************************************************
// Joshua Angel, joangel
// PA7
// Dictionary.cpp
// Implementation of Dictionary ADT
//**********************************************************************************

#include<iostream>
#include<stdexcept>
#include<string>
#include"Dictionary.h"

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates new Dictionary in the empty state
Dictionary::Dictionary(){
    nil = new Node("\0\0", -999);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor
Dictionary::Dictionary(const Dictionary& D){
    //Empty Dictionary
    this->nil = new Node("\0\0", -999);
    this->root = this->nil;
    this->current = this->nil;
    this->num_pairs = 0;

    //Load elements of D into Dictionary
    this->preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete(nil);
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false otherwise
bool Dictionary::contains(keyType k) const{
    Node *pair = search(root, k);
    if(pair->val == -999){
        return false;
    } else {
        return true;
    }
}

// getValue()
// Returns a reference to the value corresponding to key k
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if(!contains(k)){
        throw std::out_of_range("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    Node *pair = search(root, k);
    return pair->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false otherwise
bool Dictionary::hasCurrent() const{
    if(current == nil){//Current is undefined
        return false;
    }
    return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const{
    if(!hasCurrent()){
        throw std::out_of_range("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(!hasCurrent()){
        throw std::out_of_range("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, otherwise inserts
// the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node *z = new Node(k, v);
    z->left = nil;
    z->right = nil;
    Node *y = nil;
    Node *x = root;
    while(x != nil){
        y = x;
        if(z->key == x->key){
            y->val = z->val;
            delete(z);
            return;
        }
        if(z->key < x->key){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == nil){
        root = z;
    }
    else if(z->key < y->key){
        y->left = z;
    }
    else{
        y->right = z;
    }
    num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if(!contains(k)){
        throw std::out_of_range("Dictionary: remove(): key \""  + k  + "\" does not exist");
    }
    Node *z = search(root, k);
    if(z->left == nil){
        transplant(z, z->right);
        delete(z);
    }
    else if(z->right == nil){
        transplant(z, z->left);
        delete(z);
    }
    else{
        Node *y = findMin(z->right);
        if(y->parent != z){
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        delete(z);
    }
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin(){
    if(root == nil){//If empty, do nothing
        return;
    }
    current = root;
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end(){
    if(root == nil){//If empty, do nothing
        return;
    }
    current = findMax(root);
    return;
}


// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(!hasCurrent()){
        throw std::out_of_range("Dictionary: next(): current not defined");
    }
    current = findNext(current);
    if(current == nil){//If current is at last pair
        current = nil;
    }
}


// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(!hasCurrent()){
        throw std::out_of_range("Dictionary: prev(): current not defined");
    }
    current = findPrev(current);
    if(current == nil){//If current is at last pair
        current = nil;
    }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <
std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return s;
}


// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive keys are separated by
// newline "\n" characters. The key order is given by a pre-order tree walk
std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value) pairs as Dictionary D
bool Dictionary::equals(const Dictionary& D) const{
    if(this->num_pairs != D.num_pairs){//If they are different sizes
        return false;
    }
    Dictionary A = *this;
    Dictionary B = D;
    Node *x = A.root;
    Node *y = B.root;
    x = A.findMin(x);
    y = B.findMin(y);
    while(x != nil){
        if(x->key != y->key || x->val != y->val){
            return false;
        }
        x = A.findNext(x);
        y = B.findNext(y);
    }
    return true;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R != nil){
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
    if(R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete(R);
        num_pairs--;
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R != N){
        //this->setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
    return;
}

// transplant()
// Helps replace nodes when deleting
void Dictionary::transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }
    if(v != nil){
        v->parent = u->parent;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if(R == nil or k == R->key){
        return R;
    }
    else if(k < R->key){
        return search(R->left, k);
    }
    else{
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if(R == nil){
        return nil;
    }
    while(R->left != nil){
        R = R->left;
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if(R == nil){
        return nil;
    }
    while(R->right != nil){
        R = R->right;
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findNext(Node* N){
    if(N->right != nil){
        return findMin(N->right);
    }
    Node *y = N->parent;
    while(y != nil && N == y->right){
        N = y;
        y = y->parent;
    }
    return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N->left != nil){
        return findMax(N->left);
    }
    Node *y = N->parent;
    while(y != nil && N == y->left){
        N = y;
        y = y->parent;
    }
    return y;
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by member function to_string()
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined by member function equals()
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a reference to this Dictionary
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if(this != &D){//Not self assignment
        Dictionary temp = D;
        this->preOrderCopy(D.root, D.nil);
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}