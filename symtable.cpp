/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){

}

void Delete(SymNode* root) {
    if (root==NULL) {
        return;
    }
    Delete(root->left);
    Delete(root->right);
    delete root;
}

void Insert(SymNode* root, string k) {
    SymNode* node = new SymNode(k);
    if (root==NULL) {
        root=node;
        root->height=0;
        return;
    }
    if ((root->key)>k) {
        Insert(root->left, k);
    }
    else {
        Insert(root->right, k);
    }
}

void SymbolTable::insert(string k){
    SymNode* node = new SymNode(k);
    if (root==NULL) {
        root=node;
        root->height=0;
        size++;
        return;
    }
    SymNode* a=root;
    SymNode* b=NULL;
    while (a!=NULL) {
        if ((a->key)>k) {
            b=a;
            a=a->left;
        }
        else {
            b=a;
            a=a->right;
        }
    }
    if (a==b->left) {
        b->left=node;
    }
    else {
        b->right=node;
    }

}

void SymbolTable::remove(string k){

}

SymNode* Search(SymNode* root, string k) {
    if (root==NULL) {
        return root;
    }
    else if (root->left==NULL && root->right==NULL) {
        if (root->key==k) {
            return root;
        }
        return NULL;
    }
    else {
        if (root->key==k) {
            return root;
        }
        else if ((root->key)>k) {
            root=root->left;
            return Search(root,k);
        }
        else {
            root=root->right;
            return Search(root,k);
        }
    }
}

int SymbolTable::search(string k){
    SymNode* ans=Search(root,k);
    if (!ans) {
        return ans->address;
    }
    return -2;
}

void SymbolTable::assign_address(string k,int idx){

}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    Delete(root);
}