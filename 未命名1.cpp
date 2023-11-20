#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;
#define MAXSIZE 10000 
#define MAX_LINE 1024 
#define nullptr NULL

typedef struct Book{
	char no[20];					//书号 
	char name[100];					//书名 
	float price;					//价格 
}Book;

typedef struct LNode{
    Book data;                      //图书信息
    LNode *next;             //指向下一结点
    LNode *before;
    int number;
}LNode, *LinkList;

void InitList(LinkList &L){
  L = new LNode;
  L->next = NULL;
  L->number =0;
}

void FreeList(LinkList &L){
//释放内存
  delete L;
}

void show(LinkList &L) {
    LNode* current = L->next;
    while (current != NULL) {
        cout << current->data.no << " " << current->data.name << " " << current->data.price << endl;
        current = current->next;
    }
}

void ReadFile(LinkList &L, string filepath){
//从文件中读取图书信息，利用尾插法构建链表
    LNode* current = L;
    const char *path = filepath.c_str();
    FILE* fp = fopen(path, "r");

    if (fp == NULL) {
        fprintf(stderr, "Can't open file\n");
        exit(1);
    }

    char no[32], name[64];
    double price;
    char buffer[MAX_LINE];
    for (int i = 0; i < 2; i++) {
        if (fgets(buffer, MAX_LINE, fp) == NULL) {
            fprintf(stderr, "unseccessful");
            exit(1);
        }
    }

    while (fgets(buffer, MAX_LINE, fp)) {
        LNode* newnode = new LNode;
        if (sscanf(buffer, "%s %s %lf", no,  name,  &price) == 3) {
            strcpy(newnode->data.no,no);
            strcpy(newnode->data.name,name);
            newnode->data.price = price;
            newnode->next = current->next;
            current->next = newnode;
            //cout << newnode->data.no << " " << newnode->data.name << " " << newnode->data.price << endl;
            current = current->next;
            //cout<<"1"; 
            L->number++;
        }
        else {
            //fprintf(stderr, "%s\n", buffer);
        }
    }
    fclose(fp);
    //show(L);
}

int CountBook(LinkList &L){
//返回图书总数
return L->number;
}

void SaveFile(LinkList &L, string filepath) {
//保存图书信息到文件
    const char *path = filepath.c_str();
    ofstream fout(path);
    fout << "北京林业大学图书馆计算机类图书采购列表" << endl;
    fout << "ISBN	  书名	    定价" << endl;
    LNode* current = L;
    while (current) {
        fout << current->data.no << " " << current->data.name << " " << current->data.price << endl;
//        if(current->next == NULL)
//        break;
//        else
        current = current->next;
    }
//    cout << current->data.no << " " << current->data.name << " " << current->data.price << endl;
//    while(current->before != NULL)
//    {
//    	fout << current->data.no << " " << current->data.name << " " << current->data.price << endl;
//    	current = current->before;
//	  }
    fout.close();
}

bool InsertBook(LinkList &L, int pos, Book *book){
//插入图书信息，输入图书的书号、书名和价格，将该图书的基本信息插入到链表中的指定位置
//如果插入成功，返回true，否则，返回false
if(pos >= 1 && pos <= L->number+1){
    LNode* newnode = new LNode;
    LNode* current = L;
    int i = 1;
    double price;
    
    strcpy(newnode->data.no,book->no);
    strcpy(newnode->data.name,book->name);
    newnode->data.price = book->price;
    while (current->next != NULL && i != pos) {
        current = current->next;
        i++;
    }
    newnode->next = current->next;
    current->next = newnode;
    L->number++;
    return true;
}
else 
   return false;
}

bool DeleteBook(LinkList &L, int pos) { 				
//删除指定图书信息
//如果删除成功，返回true，否则，返回false
     LNode* auxpointer = L, *pointer = L->next;
    int i = 1;
    if (pointer == NULL)
        return false;
    else {
        while (pointer != NULL) {
            if (i == pos && auxpointer != L && i <= L->number) {
                auxpointer->next = pointer->next;
                pointer->next->before = auxpointer;
                delete pointer;
                L->number--;
                break;
            }
            else if (i == pos && auxpointer == L && i <= L->number) {
                auxpointer->next = pointer->next;
                pointer->next->before = auxpointer;
                L->number--;
                break;
            }
            else if (i > L->number) break;
            i++;
            pointer = pointer->next;
            auxpointer = auxpointer->next;
        }
        return true;
    }
}

LinkList SearchBook(LinkList &L, int type) {
//图书信息查找，返回包含查找图书信息的链表，如果查找失败，返回nullptr
    LNode* newnode = new LNode, *head;
    head = newnode;
	if(type == 1){
		int pos;
		cin >> pos;
		if(pos <= L->number && pos >= 1)
		{
			int i = 0;
		    LNode* current = L, *auxhead = new LNode;
		    while (current != NULL)
		    {
		        if (i == pos)
	            {
	            	strcpy(auxhead->data.no,current->data.no);
					strcpy(auxhead->data.name,current->data.name);
					auxhead->data.price = current->data.price;
					auxhead->next = newnode->next;
					newnode->next = auxhead;
				    return head;
	            }
		        i++;
		        current = current->next;
		    }
		}
		else 
		    return NULL;
	}
	if(type == 2){
		char name[50];
		cin >> name;
        LNode* current = L;
	    while (current != NULL)
	    {
	        if (strcmp(name,current->data.name)==0)
	        {
	        	LNode *auxhead = new LNode;
	        	strcpy(auxhead->data.no,current->data.no);
				strcpy(auxhead->data.name,current->data.name);
				auxhead->data.price = current->data.price;
	            auxhead->next = newnode->next;
                newnode->next = auxhead;
				newnode = newnode->next;
				newnode->next = NULL;
			}
	        current = current->next;
	    }
	    return head;
	}
}

void UpdateBook(LinkList &L) {
//图书信息更新
    LNode* current = L;
    while (current != NULL)
    {
        if (current->data.price >= 45)
            current->data.price *= 1.1;
        else
            current->data.price *= 1.2;
        current = current->next;
    }
}

void ReverseBook(LinkList &L){
//把图书信息逆序存储 
L->before = NULL; 
int i =1;
LNode *current = L->next, *auxcurrent = L->next->next;
   if(current == NULL)
   return;
   else if(auxcurrent == NULL)
   return;
   else{
   	  current->before = L->before;
   	  current->before = L;
      while(auxcurrent != NULL)
      {
      	//cout<< auxcurrent->data.no << " " << auxcurrent->data.name << " " << auxcurrent->data.price << endl;
      	auxcurrent->before = current->before;
      	auxcurrent->before = current;
      	current = current->next;
      	auxcurrent = auxcurrent->next; 
	  }
//	   while(current->before != NULL)
//    {
//    	//cout <<i<<" "<< current->data.no << " " << current->data.name << " " << current->data.price << endl;
//    	i++;
//    	current = current->before;
//	}
   }
	
}

void PriceSort(LinkList &L){
//按图书价格升序排序，采用冒泡排序
	Book* b = new Book[MAXSIZE];
	int book_number = 0;
	LNode* current = L->next;
	while(current != NULL)
	{
		strcpy(b[book_number].no,current->data.no);
		strcpy(b[book_number].name,current->data.name);
		b[book_number].price = current->data.price;
		//cout<<b[book_number].no<<" "<<b[book_number].name<<" "<<b[book_number].price<<endl; 
		book_number++;
		current = current->next;
	}
	
	for(int i = 0; i<book_number-1 ; i++)
	{
	   for(int j = 0; j <book_number-i-1; j++)
	   {
	   	   if(b[j].price>b[j+1].price)
	   	   swap(b[j],b[j+1]);
	   }
	}
	
	int i = 0;
	current = L->next;
	while(current!=NULL)
	{
		strcpy(current->data.no,b[i].no);
		strcpy(current->data.name,b[i].name);
		current->data.price =b[i].price;
		//cout<<b[i].no<<" "<<b[i].name<<" "<<b[i].price<<endl; 
		//cout<< current->data.no << " " << current->data.name << " " << current->data.price << endl;
		i++;
		current = current->next;
	}
	
}

int main()
{	
	LinkList L;
    LinkList L1;
	InitList(L);				
	ReadFile(L,"book.txt");
	PriceSort(L);				
	SaveFile(L,"book-newsort.txt");	
	InitList(L1);
    ReadFile(L1, "book-newsort.txt");
    LinkList p;					          //验证排序后的数组
	p = L1;
	int count = 0;
	while(count != 9){
		p = p->next;
		count++;
	}
	cout << "输出链表中第9个位置的图书信息" << endl;
	cout << "书号：" << p->data.no << endl; 
	cout << "书名：" << p->data.name << endl;
	cout << "价格：" << p->data.price<<endl;
	FreeList(L);
    FreeList(L1);
	return 0;
}
