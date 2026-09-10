#include<iostream>
using namespace std;
int isp(char ch) {
    switch (ch) {
        case '#':return 0;
        case '(':return 1;
        case '+':return 3;
        case '-':return 3;
        case '*':return 5;
        case '/':return 5;
        case '^':return 7;
        case '~':return 8;
        case ')':return 10;
        default:return -1;
    }
}
int icp(char ch) {
    switch (ch) {
        case '#':return 0;
        case '(':return 10;
        case '+':return 2;
        case '-':return 2;
        case '*':return 4;
        case '/':return 4;
        case '^':return 6;
        case '~':return 9;
        case ')':return 1;
        default:return -1;
    }
}
bool isdigit(char ch) {
    if (ch >= '0' && ch <= '9')return true;
    else return false;
}
void postfix(char* ch,char* fixed) {
    int chpointer=0,fixedpointer=0,top=0;
    char stack[10000];
    stack[top]='#';
    while(ch[chpointer]!='#') {
        if(isdigit(ch[chpointer])) {
            fixed[fixedpointer++]=ch[chpointer++];
        }
        else {
            char stacktop=stack[top];
            if(isp(stacktop)<icp(ch[chpointer])) {
                stack[++top]=ch[chpointer++];
            }
            else if(isp(stacktop)>icp(ch[chpointer])) {
                fixed[fixedpointer++]=stack[top--];
            }
            else {
                if(stacktop == '(') {
                    chpointer++;
                }
                top--;
            }
        }
        if(ch[chpointer]=='#') {
            while(stack[top]!='#') {
                fixed[fixedpointer++]=stack[top--];
            }
        }
    }
}

int main() {
    char ch[10001];
    cin>>ch;
    int gettop=0;
    while(ch[gettop]!='\0') {
        gettop++;
    }
    ch[gettop]='#';
    char fixed[10001];
    postfix(ch,fixed);
//fixed 即为要求的后缀表达式。
    long long stack[10001];
    int top = -1;
    int fixedpointer=0;
    while(fixed[fixedpointer]!='\0') {
        if(isdigit(fixed[fixedpointer])) {
            long long num=0;
            switch(fixed[fixedpointer]) {
                case '0':num=0;break;
                case '1':num=1;break;
                case '2':num=2;break;
                case '3':num=3;break;
                case '4':num=4;break;
                case '5':num=5;break;
                case '6':num=6;break;
                case '7':num=7;break;
                case '8':num=8;break;
                case '9':num=9;break;
                default:break;
            }
            stack[++top]=num;
            fixedpointer++;
        }
        else if(fixed[fixedpointer]=='~') {
            fixedpointer++;
            stack[top]*=-1;
        }
        else {
            long long left,right,result;
            right = stack[top--];
            left = stack[top--];
            switch(fixed[fixedpointer]) {
                case '+':result = left + right;break;
                case '-':result = left - right;break;
                case '*':result = left * right;break;
                case '/':result = left / right;break;
                case '^':
                    result = 1;
                    while(right>0) {
                        result *= left ;
                        right --;
                    }
                    break;
                default:break;
            }
            stack[++top]=result;
            fixedpointer++;
        }
    }
    cout<<stack[top]<<endl;

    return 0;
}
