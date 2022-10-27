#include<iostream>
#include<string>
#include<fstream>
#include<stack>

using namespace std;


int contain(string s1, string s2)
{
    return s1.find(s2);
}

//读取文件代码
void readFile(string code[], int &row)
{
    ifstream fin("test.txt");
    if(!fin)
    {
        cout<<"代码文件打开失败！"<<endl;
        return;
    }
    while(getline(fin, code[row]))
    {
        //cout<<code[row]<<endl;
        row++;
    }
}

//level 1
int haveKeyWords(string s1)
{
    string keyWords[32] = {"auto", "break", "case", "char", "const", "continue", "default", "do",
                           "double", "else", "enum", "extern", "float", "for", "goto", "if",
                           "int", "long", "register", "return", "short", "signed", "sizeof", "static",
                           "struct", "switch", "typdef", "union", "unsigned", "void", "volatile", "while"
                          };
    int sum = 0;
    for(int i=0; i<32; i++)
    {
        int t = s1.find(keyWords[i]), len = keyWords[i].size();
        //cout<<t<<' '<<len<<' '<<endl;
        if(t!=-1 && !isdigit(s1[t+len]) && !isalnum(s1[t+len]) && (t==0 || !isdigit(s1[t-1]) && !isalnum(s1[t-1])))
        {
            sum++;
        }
    }
    return sum;
}
//用堆栈做的level 2，3 
void parseCode(string code[], int row)
{
    int total_num = 0;
    int switch_num = 0;
    int case_num[100] = {0}, p = 0;
    int if_else_num = 0;
    int if_elseif_else_num = 0;
    stack<int> st_switch;   //用堆栈来统计 if-else if-else
    stack<string> st_if;   //用堆栈来统计 if-else if-else
    for(int i=0; i<row; i++)
    {
        total_num += haveKeyWords(code[i]);
        if(code[i].find("switch") != -1)
        {
            st_switch.push(0);
            switch_num++;
        }
        else if(code[i].find("case") != -1)
        {
            st_switch.top()++;
        }
        else if(code[i].find("default") != -1)
        {
            case_num[p++] = st_switch.top();
            st_switch.pop();
        }
        if(code[i].find("if") != -1 && code[i].find("else if") == -1)
        {
            //cout<<"if push\n";
            st_if.push("if");
        }
        else if(code[i].find("else") != -1 && code[i].find("else if") == -1)
        {
            //cout<<"find else\n";
            if(st_if.top() == "if")     //为if-else结构
            {
                //cout<<"if else ++ \n";
                if_else_num++;
                st_if.pop();
            }
            else if(st_if.top() == "else if")   //为if-else if-else结构
            {
                if_elseif_else_num++;
                while(st_if.top() == "else if")
                {
                    st_if.pop();
                }
                st_if.pop();
            }
        }
        else if(code[i].find("else if") != -1)
        {
            //cout<<"else if push\n";
            st_if.push("else if");
        }
        //cout<<"if_else_num = "<<if_else_num<<endl<<"if_elseif_else_num = "<<if_elseif_else_num<<endl;
    }
    cout<<"total num: "<<total_num<<endl;
    cout<<"switch num: "<<switch_num<<endl;
    cout<<"case num: ";
    for(int i=0; i<switch_num; i++)
    {
        cout<<case_num[i]<<' ';
    }
    cout<<"\nif-else num: "<<if_else_num<<endl;
    cout<<"if-elseif-else num: "<<if_elseif_else_num<<endl;
}

int main()
{
    string code[500];
    int row = 0;
    readFile(code, row);
    parseCode(code, row);
    return 0;
}