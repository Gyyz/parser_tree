#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <queue>
#include <iomanip>
#include <cstdlib>
using namespace std;
 
typedef vector<string>::const_iterator iter;
 
const int word_length = 10;//Max word length, should be even
 
class SyntaxTree{
    struct Node{
        string tag;
        vector<Node*> children;
        int leaf_num;
 
        Node(string tag,vector<Node*> children,int leaf_num=0){
            this->tag = tag;
            this->children = children;
            this->leaf_num = leaf_num;
        }
    };
 
    Node * _root;
public:
    void parseTree(const vector<string>& vec){
        iter be = vec.begin();
        _root = parseTree(be);
    }
 
    void printTree(){
        queue<Node*> que;
        que.push(_root);
        int level_num = 1;
        bool end_flag = true;
        while(que.size() != 0 && end_flag){
            end_flag = false;
            int new_level_num = 0;
            while(level_num--){
                Node *temp = que.front();
                printAuxi(temp->leaf_num,temp->tag);
                que.pop();
                for(int i=0;i!=temp->children.size();i++){
                    end_flag = true;
                    que.push(temp->children[i]);
                    new_level_num++;
                }
                if(temp->children.size() == 0){
                    que.push(new Node(" ",vector<Node*>(),1));//Empty Node for aligning
                    new_level_num++;
                }
            }
            level_num = new_level_num;
            cout<<endl;
            cout<<endl;
        }
    }
private:
    void printAuxi(int num,string str){
        if(str.size() % 2 == 1)
            str += " ";
        int pad = (word_length * num - str.size()) / 2;
        cout<<setw(pad + str.size())<<str;
        cout<<setw(pad)<<" ";
    }
 
    Node * parseTree(iter& b){
        if(*b == ")" || *b == "]"){
            b++;
            return NULL;
        } else if( *b == "(" || *b == "["){
            Node *temp = new Node(*(b+1),vector<Node*>());
            b += 2;
            Node *child;
            while((child = parseTree(b)) != NULL){
                temp->children.push_back(child);
                temp->leaf_num += child->leaf_num;
            }
            return temp;
        } else{
            return new Node(*b++,vector<Node*>(),1);
        }
 
        return NULL;//nosense
    }
};
 
vector<string> convert(const string& sytree){
    vector<string> ret;
    for(string::const_iterator i = sytree.begin();i != sytree.end();i++){
        if(*i == ' ' | *i == '\t')
            continue;
        else if(*i == '(' || *i == ')' || *i == '[' || *i == ']')
            ret.push_back(string(i,i+1));
        else{
            string::const_iterator j = i+1;
            for (;j != sytree.end() && *j != ' ' && *j != '\t' && *j != '(' && *j != ')' && *j != '[' && *j != ']';j++)
                ;
            ret.push_back(string(i,j));
            i = --j;
        }
    }
    return ret;
}
 
int main(){
    string test = "(1 (2 (2 (2 Inco) (2 's)) (2 Net)) (1 (2 Soars) (1 (2 on) (1 (2 (2 (2 Higher) (2 (2 Metal) (2 Prices))) (2 ,)) (2 (2 Breakup) (2 Fee))))))";
    vector<string> syt = convert(test);
    SyntaxTree syn;
    syn.parseTree(syt);
    syn.printTree();
    return 0;
}