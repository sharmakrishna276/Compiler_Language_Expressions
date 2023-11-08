/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
    memory_size=0;
    output_file="";
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit) {
    memory_size=mem_limit;
    output_file=out_file;
}

void EPPCompiler::compile(vector<vector<string>> code){
    for (int i=0;i<code.size();i++) {
        if (code[i][0]=="del") {
            int free_address=targ.symtable->search(code[i][2]);
            targ.parse(code[i]);
            mem_loc.push_back(free_address);
        }
        else if (code[i][0]=="ret") {
            targ.parse(code[i]);
            break;
        }
        else {
            int free_address=targ.symtable->search(code[i][0]);
            if (free_address==-1) {
                targ.parse(code[i]);
                targ.symtable->assign_address(code[i][0],mem_loc[mem_loc.size()-1]);
                mem_loc.pop_back();
            }
            else {
                targ.parse(code[i]);
            }
        }
    }
}

void PostOrder(ExprTreeNode* root, vector<string>& ans, Parser& targ) {
    if (root==NULL) {
        return;
    }

    else if (root->left==NULL && root->right==NULL) {
        if (root->type=="VAL") {
            string temp="PUSH "+to_string(root->num)+"\n";
            ans.push_back(temp);
        }
        else if (root->type=="ADD") {
            string temp="ADD\n";
            ans.push_back(temp);       
        }
        else if (root->type=="SUB") {
            string temp="SUB\n";
            ans.push_back(temp);       
        }
        else if (root->type=="MUL") {
            string temp="MUL\n";
            ans.push_back(temp);       
        }
        else if (root->type=="DIV") {
            string temp="DIV\n";
            ans.push_back(temp);       
        }
        else if (root->type=="VAR") {
            string temp="PUSH mem["+to_string(targ.symtable->search(root->id))+"]\n";
            ans.push_back(temp);
        }
        else if (root->type=="DEL") {
            string temp="DEL = mem["+to_string(targ.symtable->search())+"]\n";
            ans.push_back(temp);
        }
        else {
            string temp="RET = POP\n";
            ans.push_back(temp);
        }
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> ans;
    ExprTreeNode* root = targ.expr_trees.back();

}

void EPPCompiler::write_to_file(vector<string> commands){
    fstream my_output;
    my_output.open(output_file, std::ios::out);
    for (int i = 0; i < commands.size(); i++){
        my_output << commands[i] <<"\n";
    }
    my_output.close();
}

EPPCompiler::~EPPCompiler(){
  
}