#include "Project.h"

//MAIN//
void main(int argc, char* argv[])
{
    //Q1//
    InstrumentTree tr;
    Musician** MusiciansGroup;
    Musician*** MuiciansCollection;
    int musiArrSize;
    int size;
    char* MusicianFileName;
    char** Instu = GetInstrusFromFile(&size);
    tr = buildTree(Instu, size);
    //END OF Q1

    //Q2//
    findInsId(tr, "A");
    //END OF Q2//


    //Q3//
    
    MusicianFileName = "musicians.txt";
    CreateMusiciansPArray(MusicianFileName,&MusiciansGroup, &musiArrSize,tr);
    //END OF Q3//

    //Q4//
    CreateMusiciansCollection(MusiciansGroup, musiArrSize, tr, &MuiciansCollection);





}
//MAIN//