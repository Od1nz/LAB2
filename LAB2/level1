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
        if(t!=-1 && !isdigit(s1[t+len]) && !isalnum(s1[t+len]) && (t==0 || !isdigit(s1[t-1]) && !isalnum(s1[t-1])))
        {
            sum++;
        }
    }
    return sum;
}
