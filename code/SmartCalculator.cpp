//AOJ0109
#include<bits/stdc++.h>
using namespace std;

int64_t exp1(string &s, int64_t &pos); // [exp2{+,-}exp2]x
int64_t exp2(string &s, int64_t &pos); // [exp3{*,/}exp3]x
int64_t exp3(string &s, int64_t &pos); // [(exp1) or number]
int64_t number(string &s, int64_t &pos);

int64_t exp1(string &s, int64_t &pos){
    int64_t res = exp2(s, pos);
    while(true){
        if(s[pos] == '+'){
            res += exp2(s, ++pos);
        }else if(s[pos] == '-'){
            res -= exp2(s, ++pos);
        }else{
            return res;
        }
    }
}

int64_t exp2(string &s, int64_t &pos){
    int64_t res = exp3(s, pos);
    while(true){
        if(s[pos] == '*'){
            res *= exp3(s, ++pos);
        }else if(s[pos] == '/'){
            res /= exp3(s, ++pos);
        }else{
            return res;
        }
    }
}

int64_t exp3(string &s, int64_t &pos){
    if(s[pos] == '('){
        int64_t res = exp1(s, ++pos);
        pos++; //assert(s[pos] == ')');
        return res;
    }else{
        return number(s, pos);
    }
}

int64_t number(string &s, int64_t &pos){
    int64_t res = 0;
    while(isdigit(s[pos])){
        res = res * 10 + (s[pos] - '0');
        pos++;
    }
    return res;
}


int main(){
    int64_t T; cin >> T;
    cin.ignore();
    while(T--){
        string s;
        getline(cin, s);
        int64_t p = 0;
        cout << exp1(s, p) << '\n';
    }
}
