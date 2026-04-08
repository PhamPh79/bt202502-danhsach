#include <iostream>
#include <string>

using namespace std;

struct File {
    string tenFile;
    int thoiGianTao; 
    float kichThuoc; 
};

struct Node {
    File info;
    Node* link;
};

struct List {
    Node* firstNode;
};

void List_Init(List* list) {
    list->firstNode = NULL;
}

Node* CreateNode(File f) {
    Node* newNode = new Node;
    newNode->info = f;
    newNode->link = NULL;
    return newNode;
}

void InsertSorted(List* list, File f) {
    Node* newNode = CreateNode(f);
    
    if (list->firstNode == NULL || list->firstNode->info.thoiGianTao >= f.thoiGianTao) {
        newNode->link = list->firstNode;
        list->firstNode = newNode;
        return;
    }
    
    Node* p = list->firstNode;
    while (p->link != NULL && p->link->info.thoiGianTao < f.thoiGianTao) {
        p = p->link;
    }
    
    newNode->link = p->link;
    p->link = newNode;
}

float CalculateTotalSize(List* list) {
    float totalSize = 0;
    Node* p = list->firstNode;
    while (p != NULL) {
        totalSize += p->info.kichThuoc;
        p = p->link;
    }
    return totalSize;
}

void RemoveSmallestFile(List* list) {
    if (list->firstNode == NULL) return;

    Node* p = list->firstNode;
    Node* prev = NULL;
    
    Node* minNode = p;
    Node* minPrev = NULL;

    while (p != NULL) {
        if (p->info.kichThuoc < minNode->info.kichThuoc) {
            minNode = p;
            minPrev = prev;
        }
        prev = p;
        p = p->link;
    }

    if (minPrev == NULL) { 
        list->firstNode = minNode->link;
    } else {
        minPrev->link = minNode->link;
    }
    
    delete minNode;
}

void BackupToUSB(List* list) {
    float usbCapacity = 32.0;
    
    while (CalculateTotalSize(list) > usbCapacity) {
        RemoveSmallestFile(list);
    }
}
