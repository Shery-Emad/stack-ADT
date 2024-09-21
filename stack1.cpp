#include<iostream>
#include<algorithm>
#include <string>
#include<cstring>
#include <stack>
using namespace std;
template <class t>
class Stack
{
private:
    t *arr;
    int size;
    int top;
public:
    Stack(int size):size(size),top(-1)
    {
        arr =new t [size];
    }
    bool isEmpty()
    {
        return top==-1;
    }
    bool isFull()
    {
        return top==size-1;
    }
    void pushd(t value)
    {
        if (isFull())
        {
            cout<<"overflow"<<endl;
            return;
        }
        top ++;
        arr [top]=value;
    }
    t pops()
    {
        if (isEmpty())
        {
            cout<<"underflow"<<endl;
            return t();
        }
        t value=arr[top];
        top--;
        return value;
    }
    void print()
    {
        if (isEmpty())
        {
            cout<<"underflow"<<endl;
            return ;
        }
        for(int i=0; i<=top; i++)
        {
            cout<<arr[i]<<endl;
        }
    }
    void reversed()   //*
    {
        if (isEmpty())
        {
            return;
        }
        t *s =new t[size];
        int index=0;
        while(!isEmpty())
        {
            s[index++]=pops();
        }
        for(int i=0; i<index; i++)
        {
            pushd (s[i]);
        }
        delete []s;
    }
    bool areParenthesesBalanced(const char *x)
    {
        for(int i=0; x[i]!='\0'; i++)
        {
            if (x[i]=='(')
                pushd('(');
            else if (x[i]==')')
            {
                if(isEmpty())
                    return false;
                else
                    pops();
            }
        }
        return isEmpty();
    }
    bool isOperand(char s)
    {
        if(s=='*'||s=='/'||s=='+'||s=='-')
            return false;
        return true;
    }
    t precedence(char s)
    {
        if(s=='*'||s=='/')
            return 2;
        else if(s=='+'||s=='-')
            return 1;
        return 0;
    }
    string toPostfix(const string &infix)
    {
        string postfix;
        int i=0,j=0;
        while (infix [i]!='\0')
        {
            if (isOperand(infix[i]))
                postfix[j++]=infix[i++];
            else if (precedence(infix[i])>precedence (arr[top]))
                pushd(infix[i++]);
            else
            {
                postfix[j++]=arr[top];
                pops();
            }

        }
        while (!isEmpty())

        {
            postfix[j++]=arr[top];
            pops();
        }
        postfix[j]='\0';
        for(int i=0; i<=j; i++)
        {
            cout<<postfix[i];
        }
        cout<<endl;
        return postfix;
    }

    string toPrefix(const string &infix)
    {
        string postfix;
        int i=0,j=0;
        while (infix [i]!='\0')
        {
            if (isOperand(infix[i]))
                postfix[j++]=infix[i++];
            else if (precedence(infix[i])>precedence (arr[top]))
                pushd(infix[i++]);
            else
            {
                postfix[j++]=arr[top];
                pops();
            }

        }
        while (!isEmpty())

        {
            postfix[j++]=arr[top];
            pops();
        }
        postfix[j]='\0';
        for(int i=j; i>=0; i--)
        {
            cout<<postfix[i];
        }

        cout<<endl;
        return postfix;
    }
    Stack &operator=(const Stack&other)
    {
        if(this==&other)
            return *this;
        else
        {
            top=other.top;
            return *this;
        }
    }
    int evalpost(char *x)
    {
        int x1=0,x2=0;
        for (int i = 0; i <strlen(x); i++) {
            char m=x[i];

            if(isOperand(m))
                pushd(m-'0');
            else
            {
                x1=pops();
                x2=pops();
                switch(m)
                {
                case '+' :
                    pushd(x2+x1);
                    break;
                case '-' :
                    pushd(x2-x1);
                    break;
                case '*' :
                    pushd(x2*x1);
                    break;
                case '/' :
                    pushd(x2/x1);
                    break;
                }
            }
        }
        return pops();
    }
    int evalpre(char *x)
    {
        int x1=0,x2=0;
        for (int i = 0; i <strlen(x); i++) {
            char m=x[i];

            if(isOperand(m))
                pushd(m-'0');
            else
            {
                x1=pops();
                x2=pops();
                switch(m)
                {
                case '+' :
                    pushd(x1+x2);
                    break;
                case '-' :
                    pushd(x1-x2);
                    break;
                case '*' :
                    pushd(x1*x2);
                    break;
                case '/' :
                    pushd(x1/x2);
                    break;
                }
            }
        }
        return pops();
    }

};
bool isStackEmpty(const stack<int>& s)
{
    return s.empty();
}
void printStack( stack<int> s)
{
   while (!s.empty())
    {
   cout<<s.top()<<endl;
       s.pop();
    }
}
stack<int> mergeStacks(const stack<int>& s1, const stack<int>& s2)
{
stack<int>m=s1;
stack<int>t=s2;
while (!t.empty())
 {
m.push(t.top());
t.pop();
}
return m;
}
stack<int> cloneStack(const stack<int>& s) //*
 {
    stack<int>t;
    stack<int>o=s;
    while (!o.empty())
     {
        t.push(o.top());
        o.pop();
     }
     return t;
    }

stack<int> ReverseStack (const stack<int>& s)
{
stack<int>a;
stack<int>t=s;
       while (!t.empty())
    {
        a.push(t.top());
      t.pop();
    }

    return a;
}

int main()
{
    Stack <char>obj(100);
    cout<<"Are parentheses balanced in (a+b)(c-d) "<<endl<<(obj.areParenthesesBalanced("(a+b)(c-d)")?"yes":"no")<<endl;
    string infix = "5+2*3-9/3";
    cout << "Postfix of " << infix << ": " ;
    string postfix = obj.toPostfix(infix);
    int result = obj.evalpost(&postfix[0]);
    cout << "Evaluation of postfix: " << result << endl;
    cout << "Prefix  of " << infix << ": "  ;
    reverse(infix.begin(),infix.end());
    obj.toPrefix(infix);
    string prefix = obj.toPrefix(infix);
    int result2 = obj.evalpre(&prefix[0]);
    cout << "Evaluation of prefix: " << result2 << endl;
    Stack <int>obj2(100);
    obj2.pushd(10);
    obj2.pushd(20);
    obj2.pushd(30);
    obj2.pops();
    cout<<"obj2:"<<endl;
    obj2.print();
    cout<<"reverse of obj2:"<<endl;
    obj2.reversed();
    obj2.print();

   stack<int> sh;
   sh.push (1);
   sh.push(2);
   sh.push(3);
  stack<int> y;
   y.push (4);
   y.push(5);
   y.push(6);
  cout << (isStackEmpty(sh) ? "stack is empty" : "stack isn't empty") << endl;
  printStack(sh);
 stack<int>m=mergeStacks(sh,y);
 cout<<"merged stack"<<endl;
  printStack(m);
 stack<int>c=cloneStack(sh);
 cout<<"coloned stack"<<endl;
  printStack(sh);
 stack<int>l= ReverseStack(sh);
cout<<"Reversed Stack"<<endl;
  printStack(l);

    return 0;
}
