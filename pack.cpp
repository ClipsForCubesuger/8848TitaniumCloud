#include "pack.h"



void strmncpy(char *s, int m, int n, char *t)
{

    char *p=s,*q=t;
    p+=m;
    while(*p!='\0'&&n){
        *q=*p;
        p++;
        q++;
        n--;
    }
    *q='\0';
}


void path (char FN[],char * root,char* tem_src,char* tmpDirName) {
    char fn [MAX_PATH];
    strcpy(fn,root);

    char *tmp1 = fn + strlen(fn);
    while( '/' != *tmp1)
    {
        tmp1--;
    }
    memset(tmpDirName,0x0,sizeof(tmpDirName));
    strcpy(tmpDirName,tmp1);
    char fileName[MAX_PATH];
    char *tmp3 = FN + strlen(FN);
    while( '/' != *tmp3)
    {
        tmp3--;
    }
    memset(fileName,0x0,sizeof(fileName));
    strcpy(fileName,tmp3);
    char* tmp2=FN + strlen(fn);
    strcat(tmpDirName,tmp2);
    char *s = tmpDirName;

    strmncpy(s,0,strlen(tmpDirName)-strlen(fileName),tem_src);


}

int  list_dir_name(char* dirname,string names[MAX_FILE_COUNT], int tabs=0)
{
    DIR* dp;
    struct dirent* dirp;
    struct stat st;
    char tab[tabs + 1];
    if((dp = opendir(dirname)) == NULL)
    {
        perror("opendir");
        return -1;
    }

    memset(tab, '\t', tabs);
    tab[tabs] = 0;
    while((dirp = readdir(dp)) != NULL)
    {
        char fullname[MAX_PATH];
        memset(fullname, 0, sizeof(fullname));
        if(dirp->d_name[0] == '.')
            continue;

        strncpy(fullname, dirname, sizeof(fullname));
        strncat(fullname, "/", sizeof(fullname));
        strncat(fullname, dirp->d_name, sizeof(fullname));
        if(stat(fullname, &st) == -1)
        {
            perror("stat");
            fputs(fullname, stderr);
            return -1;
        }
        if(S_ISREG(st.st_mode)){  //copy full_name
            for(int i=0;i<MAX_FILE_COUNT;i++)
            {
                if(names[0]==""){
                    names[0]=fullname;
                    break;
                }
                if(names[i]!=""&&names[i+1]==""){
                    names[i+1]=fullname;
                    break;
                }

                if(names[i]==""&&names[i+1]==""){
                    break;
                }
            }

        }
        if(S_ISDIR(st.st_mode) && list_dir_name(fullname, names,tabs + 1) == -1)
            return -1;
    }
    return 0;
}


MyCab::MyCab()
{
    memset(&fh,0x0,sizeof(fh));
    memset(ObjectFilePathName,0x0,sizeof(ObjectFilePathName));
}


//?????????????????????
void  MyCab:: AddFile(char * FilePathName)
{
    if ( fh.FileCount >= MAX_FILE_COUNT - 1 )
    {
        cout<<"????????????"<<MAX_FILE_COUNT<<"?????????"<<endl;
        return;
    }
    strcpy(fh.FileName[fh.FileCount],FilePathName);
    fh.FileCount++;
}

//????????????????????????
void  MyCab::SetOutPutFile(char * OutFile)
{
    memset(ObjectFilePathName,0x0,sizeof(ObjectFilePathName));
    strcpy(ObjectFilePathName,OutFile);
}

//??????????????????(?????????????????????????????????????????????)
long MyCab:: GetFileSize(char* filename)
{
    struct stat statbuf;
    stat(filename,&statbuf);
    return statbuf.st_size;
}

//??????????????????
void MyCab:: DoMakeCAB()
{
    if ( fh.FileCount < 1 )
    {
        cout<<"???????????????????????????"<<endl;
        return;
    }
    if ( strlen(ObjectFilePathName) < 1 )
    {
        cout<<"????????????????????????????????????"<<endl;
        return;
    }

    FILE *pOutFile = NULL;
    FILE *pWorkFile = NULL;

    //????????????????????????
    for ( int i = 0 ; i < fh.FileCount ; i++ )
    {
        pWorkFile = fopen(fh.FileName[i],"rb");
        if ( NULL == pWorkFile )
        {
            cout<<"??????:"<<fh.FileName[i]<<"????????????["<<strerror(errno)<<"]"<<endl;
            return;
        }
        fh.FileLen[i] = GetFileSize(fh.FileName[i]);
        fclose(pWorkFile);
    }

    //?????????????????????
    pOutFile = fopen(ObjectFilePathName,"wb");
    if ( NULL == pOutFile )
    {
        cout<<"????????????????????????["<<strerror(errno)<<"]"<<endl;
        return;
    }

    //???????????????
    fwrite(&fh,sizeof(fh),1,pOutFile);
    //???????????????
    for ( int i = 0 ; i < fh.FileCount ; i++ )
    {
        unsigned char *pTmpData = NULL;
        pWorkFile = fopen(fh.FileName[i],"rb");
        if ( NULL == pWorkFile )
        {
            cout<<"??????:"<<fh.FileName[i]<<"????????????["<<strerror(errno)<<"]"<<endl;
            fclose(pWorkFile);
            fclose(pOutFile);
            return;
        }
        pTmpData = new unsigned char[fh.FileLen[i]];
        fread(pTmpData,fh.FileLen[i],1,pWorkFile);
        if ( ferror(pWorkFile) )
        {
            cout<<"??????:"<<fh.FileName[i]<<"????????????["<<strerror(errno)<<"]"<<endl;
            fclose(pWorkFile);
            fclose(pOutFile);
            return;
        }
        fwrite(pTmpData,fh.FileLen[i],1,pOutFile);
        if ( ferror(pOutFile) )
        {
            cout<<"??????:"<<ObjectFilePathName<<"????????????["<<strerror(errno)<<"]"<<endl;
            fclose(pWorkFile);
            fclose(pOutFile);
            return;
        }
        delete [] pTmpData;
        fclose(pWorkFile);
    }

    fclose(pOutFile);
    cout<<"????????????"<<endl;
}

//??????
void  MyCab::DoUnCAB(char *CabFilePathName,char *dest)
{
    FILE *pCAB = NULL;
    FILE *pWork = NULL;
    pCAB = fopen(CabFilePathName,"rb");
    //????????????

    memset(&fh,0x0,sizeof(fh));
    fread(&fh,sizeof(fh),1,pCAB);


    printCAB();
    //???????????????


    bool fl=false;
    for(int i=0;i<MAX_PATH;i++){
        if(fh.src[i]!=0){
            fl=true;
        }
    }



    if(!fl){

        unsigned char *pTmpData = NULL;
        pTmpData = new unsigned char[fh.FileLen[0]];
        fread(pTmpData,fh.FileLen[0],1,pCAB);
        //???????????????,??????????????????????????????
        char tmpFileName[MAX_PATH];
        char *ptmpC = fh.FileName[0] + strlen(fh.FileName[0]);
        while( '/' != *ptmpC)
        {
            ptmpC--;
        }
        *ptmpC = '\0';

        memset(tmpFileName,0x0,sizeof(tmpFileName));
        strcpy(tmpFileName,dest);//??????????????????
        strcat(tmpFileName,ptmpC);
        pWork = fopen(tmpFileName,"wb");
        fwrite(pTmpData,fh.FileLen[0],1,pWork);
        fclose(pWork);
        delete [] pTmpData;
        fclose(pCAB);
    }

    else{
        for ( int i = 0 ; i < fh.FileCount ; i++ )
        {


            char tmpDirName[MAX_PATH];
            char tem_src[MAX_PATH];
            path (fh.FileName[i], fh.src,tem_src,tmpDirName);//??????????????????




            unsigned char *pTmpData = NULL;
            pTmpData = new unsigned char[fh.FileLen[i]];
            fread(pTmpData,fh.FileLen[i],1,pCAB);
            //???????????????,??????????????????????????????
            char tmpFileName[MAX_PATH];
            char *ptmpC = fh.FileName[i] + strlen(fh.FileName[i]);
            while( '/' != *ptmpC)
            {
                ptmpC--;
            }
            memset(tmpFileName,0x0,sizeof(tmpFileName));
            strcpy(tmpFileName,ptmpC+1);




            //???CAB????????????
            char tmpPathName[MAX_PATH];
            memset(tmpPathName,0x0,sizeof(tmpPathName));

            strcpy(tmpPathName,CabFilePathName);
            ptmpC = tmpPathName + strlen(tmpPathName);
            while('/' != *ptmpC)
            {
                ptmpC--;
            }

            *ptmpC = '\0';

            char filPath[MAX_PATH];
            memset(filPath,0x0,sizeof(filPath));
            strcat(filPath,dest);
            strcat(filPath,tmpDirName);


            char filDir[MAX_PATH];
            memset(filDir,0x0,sizeof(filDir));



            strcat(filDir,dest);

            strcat(filDir,tem_src);


            Create_Folders(filDir);

            strcat(tmpPathName,tmpFileName);
            pWork = fopen(filPath,"wb");




            fwrite(pTmpData,fh.FileLen[i],1,pWork);

            fclose(pWork);
            delete [] pTmpData;
        }

        fclose(pCAB);


    }
}


//???????????????????????????
void  MyCab:: printCAB()
{
    cout<<"?????????????????????:"<<endl;
    cout<<"????????????:"<<fh.FileCount<<endl;
    for ( int i = 0 ; i < fh.FileCount ; i++ )
    {
        cout<<fh.FileName[i]<<"\t\t\t\t"<<fh.FileLen[i]<<"??????"<<endl;
    }
}

void MyCab:: Create_Folders(const char* dir){
    char order[100] = "mkdir -p ";
    strcat(order, dir);
    system(order);
}

void pack(char* src,char* dest){
    //????????????
    MyCab mc;
    //??????????????????
    mc.SetOutPutFile(dest);

    struct stat state_of_entry;
    lstat(src, &state_of_entry);



    if (S_ISDIR(state_of_entry.st_mode)) //??????????????????????????????
    {
//            mc.fh.src=src;
        strcpy(mc.fh.src,src);

        fileSystem fileManager(src);
        for(auto file : fileManager.fileList) {
            mc.AddFile((char*)file.c_str());
        }

        mc.DoMakeCAB();

    }

    else{
        for(int i=0;i<MAX_PATH;i++){
            mc.fh.src[i]=0;
        }

        //????????????????????????
        mc.AddFile(src);
        mc.DoMakeCAB();

    }
}

void unpack(char* src,char* dest){

    MyCab umc;
    //????????????

    umc.DoUnCAB(src,dest);


}



