#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <bitset>
using namespace std;
#define MAX 1000000
struct node{
  int value;
  int weight;
  int minimum;
  int exist;
  node* lchild;
  node* rchild;
  node* parent;
};
void init_node(node &p){
  p.value = 0;
  p.weight = 0;
  p.minimum = 0;
  p.exist = -1;
  p.lchild = NULL;
  p.rchild = NULL;
  p.parent = NULL;
}
struct min_heap{
  int iback;
  node *array;
};
min_heap tree;
void init_min_heap(min_heap &q){
  q.iback = -1;
  q.array = (node*)malloc(MAX*sizeof(node));
}
node pop(min_heap &tree){
  node pop_item;
  int i;
  pop_item = tree.array[0];
  for(i=0; i<tree.iback; i++){
    tree.array[i] = tree.array[i+1];
  }
  tree.iback--;
  return pop_item;
}

void push(min_heap &tree, node merge_node){
  int i;
  tree.iback++;
  tree.array[tree.iback] = merge_node;
  for(i=tree.iback; i>0; i--){
    if(tree.array[i].weight < tree.array[i-1].weight){
      swap(tree.array[i], tree.array[i-1]);
    }else if(tree.array[i].weight == tree.array[i-1].weight){
      if(tree.array[i].minimum < tree.array[i-1].minimum){
        swap(tree.array[i], tree.array[i-1]);
      }else{
        break;
      }
    }else{
      break;
    }
  }
}
void add_node(unsigned char s, min_heap &tree){
  //add exist node
  int i;
  bool exi = false;
  int c = s;
  if(tree.iback == -1){
    tree.iback++;
    node new_node;
    init_node(new_node);
    new_node.value = c;
    tree.array[tree.iback] = new_node;
  }else{
    for(i=0; i<tree.iback+1; i++){
      if(tree.array[i].value == c){
        exi = true;
        break;
      }
    }
    if(!exi){
      tree.iback++;
      node new_node;
      init_node(new_node);
      new_node.value = c;
      tree.array[tree.iback] = new_node;
    }
  }
}
string Reverse(string s,int n){
    for(int i=0,j=n-1;i<j;i++,j--){
        char c=s[i];
        s[i]=s[j];
        s[j]=c;
    }
    return s;
}
int two_to_ten(string s){
  int result = 0;
  int i;
  for(i=s.length()-1; i>=0; i--){
    if(s[i] == '1'){
      int order = s.length()-i-1;
      result += pow(2, order);
    }
  }
  return result;
}
void CODE(string* h_code, char* input_char, int n){
  int i;
  string sub;
  string all = "";
  for(i=0; i<n; i++){
    int b = (unsigned char)input_char[i];
    all = all + h_code[b];
  }
  while (all.length() % 8 != 0)
    all += '0';
  for(i = (all.length()/8); i>0; i--){
    sub = all;
    sub = sub.substr(0, 8);
    all = all.substr(8,(i-1)*8);
    sub = Reverse(sub, 8);
    unsigned char a = two_to_ten(sub);
    cout << a;
  }
}
void find_huffman_code(node* position, string code, string* h_code){
  if(position == NULL){
    return;
  }
  if(position->lchild == NULL && position->rchild == NULL){
    h_code[position->value] = code;
  }else{
    find_huffman_code(position->lchild, code + "0", h_code);
    find_huffman_code(position->rchild, code + "1", h_code);
  }
}

//find huffman code
void huffman_tree(min_heap &tree){
  node* P1;node *P2;
  int i,j,size,compare1,compare2;
  size = tree.iback;
  //order the original
  for(i=0; i<tree.iback+1; i++){
    for(j=i-1; j>=0; j--){
      if(tree.array[j+1].weight<tree.array[j].weight){
        swap(tree.array[j+1], tree.array[j]);
      }else if(tree.array[j+1].weight == tree.array[j].weight){
        if(tree.array[j+1].minimum < tree.array[j].minimum){
          swap(tree.array[j+1], tree.array[j]);
        }
      }
    }
  }
  while(tree.iback != 0){
    node merge_node;
    init_node(merge_node);
    P1 = (node*)malloc(sizeof(node));
    P2 = (node*)malloc(sizeof(node));
    *P1 = pop(tree);
    *P2 = pop(tree);
    merge_node.weight = P1->weight + P2->weight;
    compare1 = P1->minimum;
    compare2 = P2->minimum;
    if(compare1 < compare2){
      merge_node.minimum = compare1;
    }else{
      merge_node.minimum = compare2;
    }
    merge_node.lchild = P2;
    merge_node.rchild = P1;
    //add to the last and change order
    push(tree, merge_node);
  }
}
string together;
// // void find_decode(node now, int* index, int* count){
//   cout << together<<endl;
//   if(now.lchild == NULL && now.rchild == NULL){
//     *count++;
//     cout << (unsigned char)(now.value);
//     return;
//   }
//   if(together[*index] == '0'){
//     now = *now.lchild;
//     *index++;
//     find_decode(now, index, count);
//   }else{
//     now = *now.rchild;
//     *index++;
//     find_decode(now, index, count);
//   }
// }
void find_decode(node *now, int *index, int *count){
    if (now->lchild == NULL && now->rchild == NULL){
        *count += 1;
        cout << (unsigned char)now->value;
        return;
    }
    if (together[*index] == '0'){
        *index += 1;
        find_decode(now->lchild, index, count);
    }
    else{
        *index += 1;
        find_decode(now->rchild, index, count);
    }
}

int main() {
  //("haha.in", "r", stdin);
  //freopen("hehe2.out", "w", stdout);
  string magic_cookie;
  unsigned char s;
  int i, j, decode;
  int number = 0;
  int have_char_number = 0;
  char input_char[MAX];
  init_min_heap(tree);
  int fre[256];
  string* h_code = new string[256];
  cin.get((char&)s);
  //encode*********************************
  if(s == 'E'){
    magic_cookie = "HUFFMAN";
    for(i=0; i< magic_cookie.size(); i++){
      cout << magic_cookie[i];
    }
    cout << '\0';
    cin.get((char&)s);cin.get((char&)s);cin.get((char&)s);cin.get((char&)s);cin.get((char&)s);
    while(cin.get((char&)s)){
      have_char_number++;
      input_char[number] = s;
      number++;
      int asc = (unsigned char)s;
      /*if(asc < 0){
        asc += 256;
      }*/
      fre[asc] = fre[asc]+1;
      add_node(s, tree);
    }
    if(number == 0){
      int fre[256] = {0};
    }
    // print_frequency(fre)
    for(i=0; i<256; i++){
      cout.put(fre[i]&0xFF);
      cout.put((fre[i]&0xFF00) >> 8);
      cout.put((fre[i]&0xFF0000) >> 16);
      cout.put((fre[i]&0xFF000000) >> 24);
    }
    if(number != 0){
      // add_weight(tree, fre);
      for(i=0; i<tree.iback+1; i++){
        tree.array[i].weight = fre[tree.array[i].value];
        tree.array[i].minimum = tree.array[i].value;
      }
      //no need
      huffman_tree(tree);
      tree.array[0].exist = 0;
      string code ="";
      find_huffman_code(&tree.array[0], code, h_code);
      CODE(h_code, input_char, have_char_number);
    }
  }else{
  //decode*********************************
    cin.get((char&)s);cin.get((char&)s);cin.get((char&)s);cin.get((char&)s);cin.get((char&)s);
    for(i=0; i<7; i++){
      cin.get((char&)s);
    }
    cin.get((char&)s);
    for(i=0; i<256; ++i){
      string frequency = "";
      int first = cin.get();
      int second = cin.get();
      second = second << 8;
      int third = cin.get();
      third = third << 16;
      int fourth = cin.get();
      fourth = fourth << 24;
      int a = first + second + third + fourth;
      fre[i] = a;
    }
    int judge = 0;
    for(i=0; i<256; i++){
      if(fre[i]!=0){
        char f = i;
        judge = judge + fre[i];
        add_node(f,tree);
      }
    }
    for(i=0; i<tree.iback+1; i++){
      tree.array[i].weight = fre[tree.array[i].value];
      tree.array[i].minimum = tree.array[i].value;
    }
    if(judge != 0){
      huffman_tree(tree);
      while(cin.get((char&)s)){
        // s = (unsigned char)s;
        int c = (unsigned char)s;
        std::bitset<8> bit(c);
        string one_byte = bit.to_string();
        one_byte = Reverse(one_byte, one_byte.length());
        together += one_byte;
        // for (int i = 0; i < 8; ++i){
        //   together += '0' + (s & 1);
        //   s >>= 1;
        // }
      }
      // int count = 0;
      // int index = 0;
      // while( judge != count && index < together.length()){
      //   find_decode(tree.array[0], &index, &count);
      // }
      int index = 0, count = 0;
        while (index < together.length() && count != judge){
          find_decode(&tree.array[0], &index, &count);
        }
    }
  }
  return 0;
}
