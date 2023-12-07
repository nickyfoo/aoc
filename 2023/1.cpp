#include <bits/stdc++.h>

using namespace std;

vector<string> words {"zero","one","two","three","four","five","six","seven","eight","nine"};

int getFirst(string&line){
    for(int i=0; i<line.size(); i++){
        if(isdigit(line[i])){
            return 10*(line[i]-'0');
        } else {
            for(int j=0; j<10; j++){
                if(i+words[j].size()<=line.size()){
                    if(line.substr(i,words[j].size())==words[j])
                        return 10*j;
                }
            }
        }
    }
}
int getLast(string&line){
    for(int i=line.size()-1; i>=0; i--){
        if(isdigit(line[i])){
            return (line[i]-'0');
        } else {
            for(int j=0; j<10; j++){
                if(i+words[j].size()<=line.size()){
                    if(line.substr(i,words[j].size())==words[j])
                        return j;
                }
            }
        }
    }
}

int process(string&line){
    int ans = getFirst(line) + getLast(line);
//    cout << line << ' ' << ans << '\n';
    return ans;
}

int main(){
    string line;
    int ans = 0;
    // part 1
//    while(getline(cin,line)){
//        ans += (line[line.find_first_of("0123456789")]-'0')*10 + line[line.find_last_of("0123456789")]-'0';
//    }

    // part 2
    while(getline(cin,line)){
        ans += process(line);
    }
    cout << ans;

}
