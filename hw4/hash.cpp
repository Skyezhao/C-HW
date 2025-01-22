#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <time.h>
#define IOS ios::sync_with_stdio(false)
using namespace std;
#define MAX 100000
struct node{
  string key;
  int fre;
  node* next;
};
struct linked_list{
  node* head;
};
struct hash_table{
  linked_list* list;
  long long height;
};
bool judge_number(string str){
  for (int i = 0; i < str.size(); i++){
    long long tmp = (int)str[i];
    if (tmp >= 48 && tmp <= 57){
      continue;
    }else{
      return false;
    }
  }
  return true;
}
long long calculate(hash_table &table, string s){
  long long hash_code;
  int i,j;
  long long length = table.height;
  if(judge_number(s) == true){
    stringstream ss; //string to long long
    ss << s;
    ss >> hash_code;
    hash_code = hash_code % length;
  }else{
    long long sum = 0;
    for(i=s.size()-1; i>=0; i--){
      long long c = s[i];
      if(c<0){
        c = c+256;
      }
      if(i == s.size()-1){
        sum += c%length;
      }else{
        long long shift = 1;
        for(j=0; j<(s.size()-i-1); j++){
          shift = (shift * (256%length))%length;
        }
        long long temp = (((shift%length)%length)*(c%length))%length;
        sum += temp;
      }
    }
    hash_code = sum % length;
  }
  return hash_code;
}

long long search(hash_table &table, string s, long long hash_code){
  long long find = -1;
  node* position;
  position = table.list[hash_code].head;
  while(position != NULL){
    if(position->key == s){
      find = 1;
      position->fre++;
      break;
    }
    position = position->next;
  }
  return find;
}
int size = 0;
void add_to_table(hash_table &table, string s){
  long long hash_code = calculate(table,s);
  long long find = search(table, s, hash_code);
  if(find == -1){ //not find
    node* P = new node;
    size++;
    if (s.size()!=0) P->key = s;
    P->fre = 1;
    if(table.list[hash_code].head == NULL){
      table.list[hash_code].head = P;
      P->next = NULL;
    }else{
      P->next = table.list[hash_code].head;
      table.list[hash_code].head = P;
    }
  }
}

int main() {
  // clock_t start = clock();
  int i,j;
  int load_factor,length;
  node* position;
  int count = -1;
  string* exist[MAX];
  scanf("%d", &load_factor);
  scanf("%d", &length);
  hash_table table;
  table.height = length;
  table.list = new linked_list[length];
  for(i=0; i<table.height; i++){
    table.list[i].head = NULL;
  }
  //insert
  string s;
  while(true){
    char a[2000];
    scanf("%s",a);
    s = a;
    // cout << "s: "<<s<<endl;
    if(s == "************************"){
      break;
    }
    add_to_table(table, s);
    if(size*100 > table.height * load_factor){
      hash_table new_table;
      new_table.height = table.height *2 + 1;
      new_table.list = new linked_list[new_table.height];
      for(i=0; i<new_table.height; i++){
        new_table.list[i].head = NULL;
      }
      //move to new new_table
      for(i=0; i<table.height; i++){
        position = table.list[i].head;
        while(position !=NULL){
          long long hash_code = calculate(new_table, position->key);
          node* P = new node;
          P->key = position->key;
          P->fre = position->fre;
          if(new_table.list[hash_code].head == NULL){
            new_table.list[hash_code].head = P;
            P->next = NULL;
          }else{
            P->next = new_table.list[hash_code].head;
            new_table.list[hash_code].head = P;
          }
          position = position->next;
        }
      }
      table = new_table;
    }
  }
  // cout << dd << endl;
  //erase node
  while(true){
    char a[2000];
    scanf("%s",a);
    s = a;
    if(s == "************************"){
      break;
    }
    int hash_code = calculate(table, s);
    node* now = table.list[hash_code].head;
    if(now == NULL){
      continue;
    }
    if(now->key == s){
      table.list[hash_code].head = now->next;
      delete now;
    }else{
      while(now->next != NULL){
        if(now->next->key == s){
          delete now->next;
          now->next = now->next->next;
          break;
        }
        now = now->next;
      }
    }
  }
  //output the result
  printf("[\n");
  for(i=0; i<table.height; i++){
    int debug = 0;
    printf("{");
    position = table.list[i].head;
    while(position!=NULL){
      if(debug != 0){
        printf(",");
      }
      printf("\"");
      printf("%s", position->key.c_str());
      printf("\":");
      printf("%d", position->fre);
      debug++;
      position = position -> next;
    }
    if(i == table.height -1){
      printf("%s\n", "}");
    }else{
      printf("%s\n", "},");
    }
  }
  printf("%s", "]");
  for(i=0; i<table.height; i++){
    node* tmp = table.list[i].head;
    node* current;
    while (tmp != NULL){
        current = tmp;//the node to be cleaned
        tmp = tmp->next;
        delete current;
    }
  }
  delete table.list;
  // clock_t ends = clock();
  // cout << endl<<"Running Time: "<<(double)(ends-start)/CLOCKS_PER_SEC << endl;
  return 0;
}
