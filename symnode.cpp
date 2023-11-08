/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key="";
    height=0;
}

SymNode::SymNode(string k){
    key=k;
    height=0;
}

SymNode* SymNode::LeftLeftRotation(){               // Anticlockwise
    SymNode* par_temp=this->par;
    SymNode* new_temp=this->right;
    int x=0;
    if (new_temp->left) {
        new_temp->left->par=this;
        this->right=new_temp->left;
        new_temp->left=NULL;
        new_temp->par=NULL;
    }
    if (this->par==NULL) {
        x=0;
    }
    else if (this->par->left==this) {
        new_temp->par=this->par;
        this->par->left=new_temp;
        this->par=NULL;
    }
    else {
        new_temp->par=this->par;
        this->par->right=new_temp;
        this->par=NULL;
    }
    this->par=new_temp;
    new_temp->left=this;
    this->height-=2;
    return new_temp;
}

SymNode* SymNode::RightRightRotation(){         // Clockwise
    SymNode* par_temp=this->par;
    SymNode* new_temp=this->right;
    int x=0;
    if (new_temp->right) {
        new_temp->right->par=this;
        this->left=new_temp->right;
        new_temp->right=NULL;
        new_temp->par=NULL;
    }
    if (this->par==NULL) {
        x=0;
    }
    else if (this->par->left==this) {
        new_temp->par=this->par;
        this->par->left=new_temp;
        this->par=NULL;
    }
    else {
        new_temp->par=this->par;
        this->par->right=new_temp;
        this->par=NULL;
    }
    this->par=new_temp;
    new_temp->right=this;
    this->height-=2;
    return new_temp;
}

SymNode* SymNode::LeftRightRotation(){
    this->left->LeftLeftRotation();
    this->RightRightRotation();
}

SymNode* SymNode::RightLeftRotation(){
    this->right->RightRightRotation();
    this->LeftLeftRotation();
}

SymNode::~SymNode(){

}