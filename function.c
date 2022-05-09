#include "Project.h"




//Q1 FUNCTIONS : //
char** GetInstrusFromFile(int* Psize)
{
    int logS = 2;
    int size = 0;

    FILE* fp = fopen("instruments.txt", "r");
    if (fp == NULL)
    {
        printf("File did not open");
        exit(1);
    }
    char** InstruArray = (char**)malloc(logS * sizeof(char*));
    InstruArray[size] = (char*)malloc(MAXSIZE * (sizeof(char)));
    while (fgets(InstruArray[size], MAXSIZE, fp))
    {
        MakeItString(InstruArray[size]);
        size = size + 1;
        if (size == logS)
        {
            logS = logS * 2;
            InstruArray = (char**)realloc(InstruArray, logS * sizeof(char*));
        }
        InstruArray[size] = (char*)malloc(MAXSIZE * sizeof(char));
    }
    InstruArray[size] = '\0';
    *Psize = size;
    return InstruArray;
}
void MakeItString(char* str)
{
    int i = 0;
    while (((str[i] >= 'a') && (str[i] <= 'z')) || ((str[i] >= 'A') && (str[i] <= 'Z')))
    {
        i++;
    }
    str[i] = '\0';
    return;
}
InstrumentTree buildTree(char** str, int size)
{
    InstrumentTree tr;
    int i = 0;
    int id = 0;
    tr.root = createNewTNodeInstru(str[0], id, NULL, NULL);
    id++;

    for (i = 0;i < size;i++, id++)
    {
        TreeNode* node;
        node = createNewTNodeInstru(str[i], id, NULL, NULL);
        buildTreeHelper(tr.root, node);
    }
    return tr;
}
void buildTreeHelper(TreeNode* root, TreeNode* node)
{
    if (strcmp(node->instrument, root->instrument) == 0)
        return;
    else
    {
        if (strcmp(node->instrument, root->instrument) > 0)
        {
            if (root->right == NULL)
            {
                root->right = node;
            }
            else
                buildTreeHelper(root->right, node);
        }
        else
        {
            if (root->left == NULL)
            {
                root->left = node;
            }
            else
                buildTreeHelper(root->left, node);
        }
    }
    return;
}
TreeNode* createNewTNodeInstru(char* name, int id, TreeNode* left, TreeNode* right)
{
    TreeNode* res;
    res = (TreeNode*)malloc(sizeof(TreeNode));
    res->instrument = name;
    res->insId = id;
    res->left = left;
    res->right = right;
    return res;
}
//END OF Q1 FUNCTIONS//



//Q2 FUNCTIONS//
int findInsId(InstrumentTree tree, char* instrument)
{
    return findInsIdHelper(tree.root, instrument);

}
int findInsIdHelper(TreeNode* root, char* name)
{
    if (root == NULL)
        return -1;
    if (strcmp(root->instrument, name) == 0)
        return root->insId;
    else
    {
        if (strcmp(name, root->instrument) > 0)
        {
            findInsIdHelper(root->right, name);
        }
        else
            findInsIdHelper(root->left, name);

    }
}
//END OF Q2 FUNCTIONS//



//Q3 FUNCTIONS//


char** getInfoFromFile(int* Psize, char* fileName)
{
    FILE* fp;
    int size = 0;
    fp = fopen(fileName, "r");
    chekOpen(fp);
    int logSize = 2;
    char** fileData = (char**)malloc(logSize * sizeof(char*));
    checkMemoryAllocation(fileData);
    fileData[size] = (char*)malloc(MAXSIZE * sizeof(char));

    while (fgets(fileData[size], MAXSIZE, fp))
    {
        size = size + 1;
        if (size == logSize)
        {
            logSize = logSize * 2;
            fileData = (char**)realloc(fileData, logSize * sizeof(char*));
        }
        fileData[size] = (char*)malloc(MAXSIZE * sizeof(char));
    }

    // לעשות realloc בסוף
    *Psize = size;
    return fileData;
}
void chekOpen(FILE* fp)
{
    if (fp == NULL)
    {
        printf("File did not open");
        exit(1);
    }
   
}
void checkMemoryAllocation(void* p)
{
    if (p == NULL)
    {
        printf("Memory Allocation Failed..");
        exit(1);
    }
}
void CreateMusiciansPArray(char* filename, Musician*** arr, int* size, InstrumentTree tr)
{
    int i;
    int musicianFileSize;
    char* start;
    Musician** musiArr;
    char** fileInfo = getInfoFromFile(&musicianFileSize, filename);
    musiArr = (Musician**)malloc(sizeof(Musician*) * musicianFileSize);
    checkMemoryAllocation(musiArr);
    for ( i = 0; i < musicianFileSize; i++)
    {
        musiArr[i] = (Musician*)malloc(sizeof(Musician));
        checkMemoryAllocation(musiArr[i]);
        musiArr[i]->name = getNameArr(fileInfo[i],tr,&start,&(musiArr[i]->nameSize));
        musiArr[i]->instruments = buildInstrumentList(fileInfo[i], tr);
    }
    *arr = musiArr;
    *size = musicianFileSize;
}

char** getNameArr(char* line, InstrumentTree tr, int* size) 
{
    char ** res, * token;
    char* lineCopy;
    int i = 0, check,pSize = 2, logSize = 0;
    const char seps[21] = ", .;:?!-\t'()[]{}<>~_";
    lineCopy = strdup(line);
    token = strtok(lineCopy, seps);
    check = findInsId(tr, token);
    res = (char**)malloc(sizeof(char*) * pSize);
    checkMemoryAllocation(res);
    while (check == -1)
    {
        if (logSize == pSize)
        {
            pSize *= 2;
            res = (char**)realloc(res, sizeof(char*) * pSize);
        }
        res[i] = strdup(token);
        logSize = i + 1;
        token = strtok(NULL, seps);
        check = findInsId(tr, token);
        i++;
    }
    free(lineCopy);
    if (pSize > logSize)
        res = (char**)realloc(res, logSize * sizeof(char*));
    *size = logSize;
    return res;
    
}
MPIlist buildInstrumentList(char* line, InstrumentTree tr)
{
    MPIlist list; MPIlistNode* node;
    bool flag = true;
    const char seps[21] = " ,.;:?!-\t'()[]{}<>~_";
    char* token1, * token2;
    int Price, insId;


    makeEmptyMPIList(&list);

    token1 = strtok(line, seps);
    int checking = findInsId(tr, token1);

    while (checking == -1)
    {
        token1 = strtok(NULL, seps);
        checking = findInsId(tr, token1);
    }



    while (flag == true)
    {
        token2 = strtok(NULL, seps);
        sprintf(token2, "%d", &Price);

        insId = findInsId(tr, token1);

        node = createNewMPIListNode(insId, Price, NULL);
        insertNodeToEndList(&list, node);

        token1 = strtok(NULL, seps);
        if (token1 == NULL)
            flag = false;
    }


    return list;

}
MPIlistNode* createNewMPIListNode(int InsId, int price, MPIlistNode* next)
{
    MPIlistNode* res;
    res = (MPIlistNode*)malloc(sizeof(MPIlistNode));
    res->data.insId = InsId;
    res->data.price = price;
    res->next = next;
    return res;
}
void insertNodeToEndList(MPIlist* lst, MPIlistNode* tail)
{
    if (isEmptyMPIList(lst) == true)
        lst->head = lst->tail = tail;
    else
    {
        lst->tail->next = tail;
        lst->tail = tail;
    }
    tail->next = NULL;
}
bool isEmptyMPIList(MPIlist* lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}
void makeEmptyMPIList(MPIlist* lst)
{
    lst->head = lst->tail = NULL;
    return;
}

//Q4 functions//
void CreateMusiciansCollection(Musician** MusiciansGroup, int musiArrSize, InstrumentTree tr, Musician**** PMuiciansCollection)
{
    int size, insId;
    Musician*** MusicianCollection;
    size = treeSize(tr.root);
    if (size == 0)
        return;
    MusicianCollection = (Musician***)malloc(sizeof(Musician**) * size);
    for (insId = 0; insId < size; insId++)
    {
        MusicianCollection[insId] = createMusiciansQ4(MusiciansGroup, musiArrSize, insId);
    }
    *PMuiciansCollection = MusicianCollection;
}

Musician** createMusiciansQ4(Musician** MusiciansGroup,int musiArrSize,int insId)
{
    int i, counter = 0, holder;
    Musician** res;
    for ( i = 0; i < musiArrSize; i++)
    {
        counter += isPlaying(MusiciansGroup[i], insId);
    }
    res = (Musician**)malloc(sizeof(Musician*) * counter);
    counter = 0;
    for ( i = 0; i < musiArrSize; i++)
    {
        holder = isPlaying(MusiciansGroup[i], insId);
        if (holder == 1)
        {
            res[counter] = MusiciansGroup[i];
            counter += 1;
        }   
    }
    return res;

}
int isPlaying(Musician* player, int insId)
{
    MPIlistNode* curr;
    curr = player->instruments.head;
    while (curr != NULL)
    {
        if (curr->data.insId == insId)
            return 1;
        curr = curr->next;
    }
    return 0;
}

int treeSize(TreeNode* root)
{
    if (root == NULL)
        return 0;
    else
        return 1 + treeSize(root->left) + treeSize(root->right);
}
void checkIfWorks(int shit)
{
    printf("please");
}
