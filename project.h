#ifndef PROJECT
#define PROJECT 1
#define _CRT_NONSTDC_NO_DEPRECATE //strdup not working without it
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 150



// Q1 STRUCTS //
typedef struct treeNode {
    char* instrument;
    unsigned short insId;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;
typedef struct tree {
    TreeNode* root;
} InstrumentTree;
typedef struct Intrument {
    char* instrument;
    unsigned short insId;
}Ins;
//END OF STRUCTS//



// Q3 STURCTS // 
typedef struct {
    unsigned short insId;
    float price;
}MusicianPriceInstrument;
typedef struct mpilistnode {
    MusicianPriceInstrument data;
    struct mpilistnode* next;
}MPIlistNode;
typedef struct {
    MPIlistNode* head;
    MPIlistNode* tail;
}MPIlist;
typedef struct {
    char** name;
    int nameSize;
    MPIlist instruments;
}Musician;


//Q1 FUNCTIONS//
char** GetInstrusFromFile(int* size);
void MakeItString(char* str);
void buildTreeHelper(TreeNode* root, TreeNode* node);
InstrumentTree buildTree(char** str, int size);
TreeNode* createNewTNodeInstru(char* name, int id, TreeNode* left, TreeNode* right);
//END OF Q1 FUNCTIONS//


//Q2 FUNCTIONS//
int findInsId(InstrumentTree tree, char* instrument);
int findInsIdHelper(TreeNode* root, char* name);
//END OF Q2 FUNCTIONS//


//Q3 FUNCTIONS//
char** getInfoFromFile(int* Psize, char* fileName);
void chekOpen(FILE* fp);
void checkMemoryAllocation(void* p);
void CreateMusiciansPArray(char* filename, Musician*** arr, int* size, InstrumentTree tr);
char** getNameArr(char* line, InstrumentTree tr, int* size);
MPIlist buildInstrumentList(char* line, InstrumentTree tr);
MPIlistNode* createNewMPIListNode(int InsId, int price, MPIlistNode* next);
void insertNodeToEndList(MPIlist* lst, MPIlistNode* tail);
bool isEmptyMPIList(MPIlist* lst);
void makeEmptyMPIList(MPIlist* lst);


//Q4 FUNCTIONS//
int treeSize(TreeNode* root);
int isPlaying(Musician* player, int insId);
Musician** createMusiciansQ4(Musician** MusiciansGroup, int musiArrSize, int insId);
void CreateMusiciansCollection(Musician** MusiciansGroup, int musiArrSize, InstrumentTree tr, Musician**** PMuiciansCollection);


//Q5 functions//

ConcertInstrumentNode* createNewListNode(ConcertInstrumentNode* next, InstrumentTree tr);
void insertCINodeToEndList(CIList* lst, ConcertInstrumentNode* tail);
bool isEmptyCIlist(CIList lst);
void makeEmptyCIlist(CIList* lst);
int getConcertFromUser(Concert* concertp, InstrumentTree tr);
CIList getInstrumentList(InstrumentTree tr);
int getName(char* name);
void GetConcertAndFindMusicians(InstrumentTree tr, Musician*** MuiciansCollection, int* IMSize);
int sortCheapestToExpensive(void* priceA, void* priceB, int id);
int sortExpensiveToChepest(void* priceA, void* priceB, int id);
int getPriceForInstrument(int insId, MPIlist musicianList);


//Q5 structs//
typedef struct
{
    int day, month, year;
    float hour;
} Date;
typedef struct
{
    int num;
    int inst;
    char importance;
}ConcertInstrument;

typedef struct ConcertInstrumentNode
{
    ConcertInstrument data;
    ConcertInstrumentNode* next;

}ConcertInstrumentNode;
typedef struct
{
    ConcertInstrumentNode* head;
    ConcertInstrumentNode* tail;
}CIList;

typedef struct
{
    Date date_of_concert;
    char* name;
    CIList instruments;
}Concert;


#endif 
