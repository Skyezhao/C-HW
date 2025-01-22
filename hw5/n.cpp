#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sstream>
#define MAX 20000
using namespace std;
int n,m,k,time_to_stop;
struct node{
  int city1;
  int city2;
  int min_road;
  node* next;
};
struct Heap{
  int iback;
  node* array;
};
struct linked_list{
  node* head;
  int height;
  int minimum;
};
struct UnionFindSet{
  linked_list* list;
};
bool compare(node a, node b){
  if(a.min_road < b.min_road){
    return true;
  }else if(a.min_road == b.min_road){
    if(min(a.city1,a.city2) < min(b.city1,b.city2)){;
      return true;
    }else if(min(a.city1,a.city2) == min(b.city1,b.city2)){
      if(max(a.city1,a.city2) < max(b.city1,b.city2)){
        return true;
      }else{
        return false;
      }
    }else{
      return false;
    }
  }else{
    return false;
  }
}

void min_heap_push(Heap &q, node s){
  int position, father;
  q.iback++;
  q.array[q.iback] = s;
  position = q.iback;
  father = ceil((double)position/2)-1;
  while(father>=0 && !compare(q.array[father], q.array[position])){
    swap(q.array[father],q.array[position]);
    position = father;
    father = ceil((double)position/2)-1;
  }
}
node pop_min(Heap &q){
  node pop_item;
  int i,j;
  pop_item = q.array[0];
  q.array[0] = q.array[q.iback];
  int add_number = q.iback;
  q.iback--;
  i = 0;
  j = 1;
  while(q.iback>=(j+1)){
    if(compare(q.array[i],q.array[j]) && compare(q.array[i],q.array[j+1])){
      break;
    }
    if(compare(q.array[j],q.array[j+1])){
      swap(q.array[i],q.array[j]);
      i = j;
      j = 2*i+1;
    }else{
      swap(q.array[i],q.array[j+1]);
      i = j+1;
      j = 2*i+1;
    }
  }
  if(q.iback==j && compare(q.array[j],q.array[i])){
    swap(q.array[i],q.array[j]);
  }
  q.array[add_number]=pop_item;
  return pop_item;
}

int find_max_region(UnionFindSet region,int* a, int p){
  int i,j;
  int find = -2;
  int result = 0;
  int mini;
  for(i=0; i<p+1; i++){
    j = a[i];
    if(region.list[j].height > find){
      find = region.list[j].height;
      mini = region.list[j].minimum;

      result = j;
    }else if(region.list[j].height == find){
      if(region.list[j].minimum >= mini){
        find = region.list[j].height;
        mini = region.list[j].minimum;
        result = j;
      }
    }
  }
  return result;
}

int findy(int n,int* H){
  if(H[n] == n){
    return n;
  }else{
    H[n] = findy(H[n],H);
    return H[n];
  }
}
int set_union(int i, int j, int* H){
  int re = -1;
  i = findy(i,H);
  j = findy(j,H);
  if(i!=j){
    H[j]=i;
    re = 0;
  }
  return re;
}

int main() {
  int i,j,P,city1,city2,road,find,total,first,second,count,save;
  UnionFindSet region;
  Heap min_heap;
  scanf("%d",&n); //number of cities
  scanf("%d",&m); //number of old roads
  scanf("%d",&k); //threshold region number
  if(n<0 || m<0){
    return 0;
  }
  if(k>=n){
    cout <<"["<<endl;
    for(i=0; i<n-1; i++){
      cout <<"["<<endl;
      cout <<"],"<<endl;
    }
    cout <<"["<<endl;
    cout <<"]"<<endl;
    cout <<"]"<<endl;
    return 0;
  }
  min_heap.iback = -1;
  min_heap.array = new node[m];
  count = 0;
  save = m;
  while(scanf("%d",&city1) && scanf("%d",&city2) && scanf("%d",&road)){
    if(city1 == city2){
      m--;
      continue;
    }
    count++;
    if(count > save) break;
    node new_node;
    if(city1 > city2) swap(city1,city2); //invalid input
    new_node.city1 = city1;
    new_node.city2 = city2;
    new_node.min_road = road;
    min_heap_push(min_heap,new_node);
  }
  int H[MAX];
  for(i=0; i<n; i++){
    H[i]=i;
  }
  count = -1;
  node need[m];
  total = min_heap.iback; //because when pop iback will change
  time_to_stop = n;
  for(i=0; i<total+1; i++){
    if(time_to_stop == k) break;
    node edge = pop_min(min_heap);
    int re = set_union(edge.city1,edge.city2,H);
    if(re == 0){
      time_to_stop--;
      count++;
      need[count]=edge;
    }
  }
  for(i=0; i<n; i++){
    H[i]=findy(i,H);
  }
  region.list = new linked_list[n];
  for(i=0; i<n; i++){
    region.list[i].head = NULL; //at most m road;
    region.list[i].height = -1;
    region.list[i].minimum = i;
  }
  //distinguish roads to different region
  for(i=0; i<count+1; i++){
    node* T = &need[i];
    int top = H[T->city1];
    region.list[top].minimum = min(T->city1,region.list[top].minimum);
    region.list[top].height++;
    P = region.list[top].height;
    T->next = region.list[top].head;
    region.list[top].head = T;
  }
  //find out need to print region
  int a[n];
  int p = -1; //save exist region
  for(i=0; i<n;i++){
    if(i == H[i]){
      p++;
      a[p]=i;
    }
  }
  cout << "["<<endl;
  for(i=0; i<time_to_stop;i++){
    int output = find_max_region(region,a,p);
    // cout << output<<endl;
    Heap max_heap;
    max_heap.iback = -1;
    if (region.list[output].height == -1){
      cout <<"["<<endl;
    }else{
      max_heap.array = new node[region.list[output].height+1];
      node* Y = region.list[output].head;
      while(Y!=NULL){
        min_heap_push(max_heap,*Y);
        Y = Y->next;
      }
      region.list[output].height = -2;//set to 0
      int A = max_heap.iback;
      for(j=0; j<A+1; j++){
        pop_min(max_heap);
      }
      node print;
      cout << "["<<endl;
      for(j=0;j<A;j++){
        print = max_heap.array[j];
        cout << "["<<print.city1<<","<<print.city2<<","<<print.min_road<<"],"<<endl;
      }
      print = max_heap.array[A];
      cout << "["<<print.city1<<","<<print.city2<<","<<print.min_road<<"]"<<endl;
    }
    if(i == time_to_stop-1){
      cout << "]"<<endl;
    }else{
      cout << "],"<<endl;
    }
  }
  cout << "]"<<endl;
  return 0;
}
