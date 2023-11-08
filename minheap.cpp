/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){

}

void Delete(HeapNode* root) {
    if (root==NULL) {
        return;
    }
    Delete(root->left);
    Delete(root->right);
    delete root;
}

void heapifyup(HeapNode* node) {

}

void heapifydown(HeapNode* root) {

}

void MinHeap::push_heap(int num){

}

int MinHeap::get_min(){
    return root->val;
}

void MinHeap::pop(){

}

MinHeap::~MinHeap(){
    Delete(root);
}