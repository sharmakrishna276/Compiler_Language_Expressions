/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable=new SymbolTable();
    last_deleted=-1;
}

void Delete(ExprTreeNode* root) {
    if (root==NULL) {
        return;
    }
    Delete(root->left);
    Delete(root->right);
    delete root;
}

void Parser::parse(vector<string> expression) {

    ExprTreeNode* root=new ExprTreeNode();
    expr_trees.push_back(root);

    if (expression[0]=="del") {
        ExprTreeNode* leftchild = new ExprTreeNode("DEL",0);
        ExprTreeNode* rightchild = new ExprTreeNode("VAR",symtable->search(expression[2]));
        rightchild->id=expression[2];
        root->left=leftchild;
        root->right=rightchild;
        last_deleted=symtable->search(root->right->id);
        symtable->remove(root->right->id);
    }

    else if (expression[0]=="ret") {
        root->left=new ExprTreeNode("RET",0);
        ExprTreeNode* curr=new ExprTreeNode();
        root->right=curr;
        vector<ExprTreeNode*> v;
        v.push_back(curr);
        for (int i=2;i<expression.size();i++) {
            if (expression[i]=="(") {
                curr->left=new ExprTreeNode();
                v.push_back(curr->left);
                curr=curr->left;
            }
            else if (expression[i]=="+") {
                curr->type="ADD";
                curr->right=new ExprTreeNode();
                v.push_back(curr->right);
                curr=curr->right;
            }
            else if (expression[i]=="-") {
                curr->type="SUB";
                curr->right=new ExprTreeNode();
                v.push_back(curr->right);
                curr=curr->right;
            }
            else if (expression[i]=="*") {
                curr->type="MUL";
                curr->right=new ExprTreeNode();
                v.push_back(curr->right);
                curr=curr->right;
            }
            else if (expression[i]=="/") {
                curr->type="DIV";
                curr->right=new ExprTreeNode();
                v.push_back(curr->right);
                curr=curr->right;
            }
            else if (expression[i]==")") {
                v.pop_back();
                if (v.size()>=1) {
                    curr=v[v.size()-1];
                }
            }
            else if (expression[i][0]=='0' || expression[i][0]=='1' || expression[i][0]=='2' || expression[i][0]=='3' || expression[i][0]=='4' || expression[i][0]=='5' || expression[i][0]=='6' || expression[i][0]=='7' || expression[i][0]=='8' || expression[i][0]=='9') {
                curr->type="VAL";
                curr->num=stoi(expression[i]);
                v.pop_back();
                if (v.size()>=1) {
                    curr=v[v.size()-1];
                }         
            }
            else {
                curr->type="VAR";
                curr->id=expression[i];
                v.pop_back();
                if (v.size()>=1) {
                    curr=v[v.size()-1];
                }
            }
        }
    }

    else {
        bool flag=false;
        int idx=0;
        for (int i=0;i<expr_trees.size();i++) {
            if (expr_trees[i]->left->id==expression[0]) {
                flag=true;
                idx=i;
                break;
            }
        }
        ExprTreeNode* root=new ExprTreeNode();
        if (flag) {
            Delete(expr_trees[idx]);
            expr_trees[idx]=root;                                           // Is it correct?
        }
        else {
            expr_trees.push_back(root);
        }
        root->left=new ExprTreeNode("VAR",0);
        root->left->id=expression[0];
        ExprTreeNode* curr=new ExprTreeNode();
        root->right=curr;
        vector<ExprTreeNode*> v;
        v.push_back(curr);
        for (int i=2;i<expression.size();i++) {
            if (expression[i]=="(") {
                curr->left=new ExprTreeNode();
                v.push_back(curr->left);
                curr=curr->left;
            }
            else if (expression[i]=="+") {
                curr->type="ADD";
                curr->right=new ExprTreeNode();
                v.push_back(curr->right);
                curr=curr->right;
            }
            else if (expression[i]=="-") {
                curr->type="SUB";
                curr->right=new ExprTreeNode();
                v.push_back(curr->right);
                curr=curr->right;
            }
            else if (expression[i]=="*") {
                curr->type="MUL";
                curr->right=new ExprTreeNode();
                v.push_back(curr->right);
                curr=curr->right;
            }
            else if (expression[i]=="/") {
                curr->type="DIV";
                curr->right=new ExprTreeNode();
                v.push_back(curr->right);
                curr=curr->right;
            }
            else if (expression[i]==")") {
                v.pop_back();
                if (v.size()>=1) {
                    curr=v[v.size()-1];
                }
            }
            else if (expression[i][0]=='0' || expression[i][0]=='1' || expression[i][0]=='2' || expression[i][0]=='3' || expression[i][0]=='4' || expression[i][0]=='5' || expression[i][0]=='6' || expression[i][0]=='7' || expression[i][0]=='8' || expression[i][0]=='9') {
                curr->type="VAL";
                curr->num=stoi(expression[i]);
                v.pop_back();
                if (v.size()>=1) {
                    curr=v[v.size()-1];
                }         
            }
            else {
                curr->type="VAR";
                curr->id=expression[i];
                v.pop_back();
                if (v.size()>=1) {
                    curr=v[v.size()-1];
                }
            }
        }
        symtable->insert(root->left->id);
    }
}

Parser::~Parser(){
    delete symtable;
    for (int i=0;i<expr_trees.size();i++) {
        Delete(expr_trees[i]);
    }
}