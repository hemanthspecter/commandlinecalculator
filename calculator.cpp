#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Test{
public:
    void help(string s){
        validate(s);
    }


    
    
    
    
private:
//vector<string> helper(string temp);
//float calculate(vector<string> v);

    void validate(string S){
        
        if(S.length()==1 || S.length()==2){
            cout<<"Wrong Input"<<endl;
            return;
        }
        else{
          int numflag=0;
            for(int i=0;i<S.length();i++){
                int temp=S[i];
                if((temp==42 || temp==43 || temp==45 || temp==47) && numflag==0){
                    cout<<"wrong Input"<<endl;
                    return;
                }
                else if(temp>47 && temp<58){
                    numflag=1;
                }
                else if((temp==42 || temp==43 || temp==45 || temp==47) && numflag==1){
                    numflag=0;
                }
                else if(temp==46 && numflag==1){
                    numflag=0;
                }
                
                else{
                    cout<<"Wrong Input"<<endl;
                    return;
                }
                
            }
            if(numflag==0){
                cout<<"Error"<<endl;
                return;
            }
            cout << calculate(helper(S))<<endl;
            
            
        }
        
    }



    vector<string> helper(string temp){
    //void helper(string temp){
        vector<string> v;
        int val=0;
        int flag=0;
        int count=0;
        for(int i=0;i<temp.length();i++){
            
            int t = temp[i];
            //cout<<t <<" ascii ";
            
            
            //cout<<t<< "  t "<<endl;
            if(t==46){
                flag=1;
            }
            else if(val!=0 && (t<48 || t>57)){
                //cout << val << "val" <<endl;
                //char c=val;
                //cout << c <<" c "<<endl;
                float final=val;
                if(flag){
                    //cout<<"hi";
                    //cout<<count<<" count "<<endl;
                    final=(float(val))/float(pow(10,count));
                    count=0;
                    flag=0;
                }
                //cout<<val<<" val "<<endl;
                //cout<<final<<" final "<<endl;
                v.push_back(to_string(final));
                v.push_back(to_string(temp[i]));
                val=0;
            }
            
                
            else{
                int s = temp[i]-'0';
                if(flag==1){
                    count++;
                }
                val=(val*10)+s;
                //cout<<val<<" val "<<endl;
            }
            
        }
        if(val!=0){
            if(flag){
               float final=(float(val))/float(pow(10,count));
            
            v.push_back(to_string(final));
            }
            else{
                v.push_back(to_string(val));
            }
        }
        //test
        
        //for(int i=0;i<v.size();i++){
            //cout<<v[i]<<" i ";
        //}
        return v;
    }

    int precedence(char op){
        if(op == '+')
        return 1;
        if(op == '-')
            return 2;
        if(op == '*')
            return 3;
        if(op == '/')
            return 4;
        //return 2;
        return 0;
    }

    // Function to perform arithmetic operations.
    float applyOp(float a, float b, char op){
        switch(op){
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
        }
        return 0;
    }

    string refer(vector<char> v){
        for(int i=0;i<v.size();i++){
            if(v[i]!='/' && v[i]!='*' && v[i]!='-' && v[i]!='+'){
                cout<<int(v[i])<<endl;
            }
            else{
                cout<<v[i]<<endl;
            }
        }
        string temp="";
        return temp;
    }

    float stoint(string s){
        int temp=0;
        int flag=0;
        int count=0;
        for(int i=0;i<s.length();i++){
            
            if(s[i]=='.'){
                flag=1;
                //cout<<"hi";
                continue;
            }
            else if(flag){
                count++;
                //cout<<count<<" count "<<endl;
            }
            temp=(temp*10)+s[i]-'0';
            //cout<<temp<<" temp "<<endl;
        }
        float final;
        
        if(flag){
            final=float(temp)/float(pow(10,count));
            //cout<<final<<" final "<<endl;
            flag=0;
            count=0;
        }
        else{
            final=float(temp);
        }
        return final;
    }

    float calculate(vector<string> v){
        int i;
        stack <float> values;
        stack <char> ops;
        
        for(i=0; i<v.size();i++){
            
            if(v[i][0]=='('){
               // ops.push(v[i]);
            }
            else if(int(stoint(v[i]))!=42 && int(stoint(v[i]))!=43 && int(stoint(v[i]))!=45 && int(stoint(v[i])!=47) && i<v.size()){
                values.push(stoint(v[i]));
                //cout<<v[i]<<" v[i] "<<endl;
                //cout<<stoint(v[i])<<"stoi"<<endl;
                
            }
            else if(v[i][0]==')'){
                while(!ops.empty() && ops.top() != '('){
                    int val2 = values.top();
                    //cout<<val2<<" vales2 "<<endl;
                    values.pop();
                    int val1 =values.top();
                    //cout<<val1<<" vales1 "<<endl;
                    values.pop();
                    char op = ops.top();
                    //cout<<op<<" ops "<<endl;
                    ops.pop();
                    
                    values.push(applyOp(val1,val2,op));
                }
                if(!ops.empty())
                    ops.pop();
                    
        }
            else{
                int te=stoint(v[i]);
                char c=te;
                while(!ops.empty() && precedence(ops.top())>=precedence(c)){
                    float val2 = values.top();
                    //cout<<val2<<" vales2 "<<endl;
                    values.pop();
                    
                    float val1 = values.top();
                    //cout<<val1<<" vales1 "<<endl;
                    values.pop();
                    
                    char op = ops.top();
                    //cout<<op<<" ops "<<endl;
                    ops.pop();
                    
                    values.push(applyOp(val1,val2,op));
                }
                int temp=stoint(v[i]);
                ops.push(char(temp));
            }
        }
        
            while(!ops.empty()){
                float val2 = values.top();
                //cout<<val2<<" vales2 "<<endl;
                values.pop();
                        
                float val1 = values.top();
                //cout<<val1<<" vales1 "<<endl;
                values.pop();
                        
                char op = ops.top();
                //cout<<op<<" ops "<<endl;
                ops.pop();
                        
                values.push(applyOp(val1, val2, op));
            }
            
            // Top of 'values' contains result, return it.
            return values.top();
            
        //return "";
    }
    
    


};









int main(){
    while(1){
        cout<<" Enter the input expression "<<endl;
    string S;
    cin >> S;
        if(S=="quit"){
            break;
        }
        
    //cout << calculate(helper(S));
    Test o1;
    o1.help(S);
    
        
    }
    
    //test
    
    //test();
    
    
   // validate(S);
    //helper(S);
    return 0;
}
