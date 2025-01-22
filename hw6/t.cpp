#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sstream>
using namespace std;
struct node{
  char key;
  int visit;
  int parent;
  int child[26];
  int children;
};
void big_to_small(string &s){
  int i;
  for(i=0; i<s.size(); i++){
    if(s[i] >= 'A' && s[i] <= 'Z'){
      s[i] += 32;
    }
  }
}
int main(){
  int i,j,k,n,l1,l2,n1,n2;
  string name,a,b;
  const char* str;
	str = "";
  scanf("%d",&n);
  if(n<=0){
    printf("%s\n", "另请高明吧");
    return 0;
  }
  string save[n];
  int count = -1;
  while(getline(cin,name)){
    if(name!=""){
      while(name.find(" ")!=-1){
        name = name.replace(name.find(" "), 1, str);
      }
      count++;
      big_to_small(name);
      // cout << name << endl;
      save[count]=name;
    }
  }
  node TS[26];
  for(i=0; i<26; i++){
    TS[i].key = i+97;
    TS[i].visit = 0;
    TS[i].parent = 0;
    TS[i].children = -1;
  }
  int longer;
  for(i=0; i<count; i++){
    longer = 0;
    int judge = -1;
    a = save[i];
    b = save[i+1];
    // cout << "___ "<<a <<" "<<b<<endl;
    l1 = a.size();
    l2 = b.size();
    if(l1>l2){
      longer = 1;
    }
    int length = min(l1,l2);
    for(j=0; j<length; j++){
      if(a[j] != b[j]){
        n1 = a[j]-97;
        n2 = b[j]-97;
        judge = j;
        break;
      }
    }
    if(judge == -1 && longer == 1){
      printf("%s\n", "另请高明吧");
      return 0;
    }
    // cout << n1<<" "<<n2<<endl;
    if(judge!=-1){
      TS[n1].children++;
      TS[n1].child[TS[n1].children] = n2;
      TS[n2].parent++;
    }
  }
  // for(i=0; i<26; i++){
  //   cout << TS[i].key<<" "<<TS[i].parent<<endl;
  // }
  int number = 0;
  char output[26];
  count = -1;
  for(i=0; i<26; i++){
    for(j=0; j<26; j++){
      if(TS[j].visit == 0){
        if(TS[j].parent == 0){
          for(k=0; k<TS[j].children+1;k++){
            TS[TS[j].child[k]].parent--;
          }
          TS[j].visit = 1;
          count++;
          number++;
          output[count] = TS[j].key;
          break;
        }
      }
    }
  }
  if(number!=26){
    printf("%s\n", "另请高明吧");
    return 0;
  }
  for(i=0; i<26; i++){
    cout << output[i];
  }
  return 0;
}
