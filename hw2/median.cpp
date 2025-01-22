#include <string>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define MAX 100000
using namespace std;
struct Heap{
  int size;
  int iback;
  int *array;
};
void init(Heap &q){
  q.iback = -1;
  q.size = 0;
  q.array = new int[MAX];
}
void push(Heap &q, int s){
  q.iback++;
  q.array[0] = s;
  q.size++;
}
int front(Heap &q){
  return q.array[0];
}
int pop_max(Heap &q){;
  int pop_item, children, position;
  pop_item = q.array[0];
  q.size--;
  q.array[0] = q.array[q.iback];
  q.iback--;
  position = 0;
  children = position*2 + 1;
  while(q.iback>=(children+1)){
    if(q.array[position]>=q.array[children] && q.array[position]>=q.array[children+1]){
      break;
    }
    if(q.array[children]>=q.array[children+1]){
      swap(q.array[children],q.array[position]);
      position = children;
      children = position*2 + 1;
    }else{
      swap(q.array[children+1],q.array[position]);
      position = children+1;
      children = position*2 + 1;
    }
  }
  if(q.iback==children && q.array[position]<q.array[children]){
    swap(q.array[children],q.array[position]);
  }
  return pop_item;
}

int pop_min(Heap &q){
  int pop_item, children, position;
  pop_item = q.array[0];
  q.size--;
  q.array[0] = q.array[q.iback];
  q.iback--;
  position = 0;
  children = 1;
  while(q.iback>=(children+1)){
    if(q.array[position]<=q.array[children] && q.array[position]<=q.array[children+1]){
      break;
    }
    if(q.array[children]<=q.array[children+1]){
      swap(q.array[children],q.array[position]);
      position = children;
      children = position*2 + 1;
    }else{
      swap(q.array[children+1],q.array[position]);
      position = children+1;
      children = position*2 + 1;
    }
  }
  if(q.iback==children && q.array[position]>q.array[children]){
    swap(q.array[children],q.array[position]);
  }
  return pop_item;
}
int pow_2(int i){
  int r=1;
  while(i--) r*=2;
  return r;
}

void max_heap_push(Heap &q, int s){
  int position, father;
  q.iback++;
  q.array[q.iback] = s;
  q.size++;
  position = q.iback;
  father = ceil((double)position/2)-1;
  while(father>=0 && (q.array[father] < q.array[position])){
    swap(q.array[father],q.array[position]);
    position = father;
    father = ceil((double)position/2)-1;;
  }
}
void min_heap_push(Heap &q, int s){
  int position, father;
  q.iback++;
  q.array[q.iback] = s;
  q.size++;
  position = q.iback;
  father = ceil((double)position/2)-1;
  while(father>=0 && q.array[father] > q.array[position]){
    swap(q.array[father],q.array[position]);
    position = father;
    father = ceil((double)position/2)-1;
  }
}
void print_heap(Heap &q){
  int i,j,count;
  count = 0;
  for(i=0; i<q.size; i++){
    if(q.iback < (i+pow_2(count)-1)){
      for(j=i; j<(q.iback+1); j++){
        if(j==i){
          printf("%d", q.array[j]);
        }else{
          printf("%s", " ");
          printf("%d", q.array[j]);
        }
      }
      for(j=q.iback+1; j<(i+pow_2(count)); j++){
        printf("%s", " S");
      }
      i=j-1;
      printf("%s\n", "");
      count++;
    }else{
      for(j=i; j < (i+pow_2(count)); j++){
        if(j==i){
          printf("%d", q.array[j]);
        }else{
          printf("%s", " ");
          printf("%d", q.array[j]);
        }
      }
      count++;
      i = j-1;
      printf("%s\n", "");
    }
  }
}
int find_median(int a, Heap &min_heap, Heap &max_heap){
  int pop_item;
  double median;
  //judeg the number of item
  //put smaller into the max_heap and bigger into min_heap
    //transfer string to int
  if(a < front(max_heap)){
    max_heap_push(max_heap,a);
  }else{
    min_heap_push(min_heap,a);
  }
  /*
  if (a == 60964633) {
    print_heap(max_heap);
    printf("%s\n", "\n\n\n\n\n\n\n\n");
  }*/
  if(min_heap.size - max_heap.size < -1){
    pop_item = pop_max(max_heap);
    min_heap_push(min_heap,pop_item);
  }else if(min_heap.size - max_heap.size >1){
    pop_item = pop_min(min_heap);
    max_heap_push(max_heap, pop_item);
  }
  if(min_heap.size == max_heap.size){
    median =(double)(front(min_heap) + front(max_heap))/2;
    if(median==(int)median){
      printf("%d\n", (int)median);
    }else{
      printf("%.1f\n", median);
    }
    // cout << median << endl;
  }else if(min_heap.size < max_heap.size){
    printf("%d\n", front(max_heap));
    // cout << front(max_heap) << endl;
  }else if(min_heap.size > max_heap.size){
    printf("%d\n", front(min_heap));
    // cout << front(min_heap) << endl;
  }
  print_heap(min_heap);
  print_heap(max_heap);
  return 0;
}
int main() {
  int s;
  int a,b;
  double median;
  Heap min_heap, max_heap;
  init(min_heap);
  init(max_heap);
  cin >> a >> b;
  if(a>b){
    push(max_heap, b);
    push(min_heap, a);
  }else{
    push(max_heap, a);
    push(min_heap, b);
  }
  median =(double)(front(min_heap) + front(max_heap))/2;
  if(median==(int)median){
    printf("%d\n", (int)median);
  }else{
    printf("%.1f\n", median);
  }
  print_heap(min_heap);
  print_heap(max_heap);
  while(cin >> s){
    find_median(s,min_heap,max_heap);
  };
  return 0;
}
