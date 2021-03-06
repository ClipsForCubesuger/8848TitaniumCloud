#include "dialog_restore.h"
#include "ui_dialog_restore.h"
#include "QFileDialog"
#include<dirent.h>

#include "huffman.h"
#include "pack.h"
#include "lock_safe.h"


Dialog_restore::Dialog_restore(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Dialog_restore)
{
    ui->setupUi(this);
}

Dialog_restore::~Dialog_restore()
{
    delete ui;
}
void Dialog_restore::getpwforDecrypt(QString pwfd)
{
    pwfordecrypt = pwfd;
}


void Dialog_restore::on_pushButton_4_clicked()//返回按钮
{
    Dialog_restore::close();
}

void Dialog_restore::on_pushButton_clicked()
{
    filePathReTo = QFileDialog::getExistingDirectory();
    ui->backReTo->setText(filePathReTo);
}

void Dialog_restore::on_pushButton_2_clicked()
{
    isremote = false;
    filePathReFrom = QFileDialog::getExistingDirectory();
    ui->backReFrom->setText(filePathReFrom);

}

void Dialog_restore::on_pushButton_5_clicked()
{
    std::string  pathfrom= filePathReFrom.toStdString();
    const char* constcpathfrom = pathfrom.c_str();
    std::string pathto = filePathReTo.toStdString();
    const char* constcpathto = pathto.c_str();

    if(pathto == "" || pathfrom == "")
    {
        ui->label_2->setStyleSheet("color:red");
        return;
    }
    else{
        ui->label_2->setStyleSheet("color:#f0f0f0");
    }

    char* named = new char[50];
    for(int i = 0;i<=99;i++)
    {
        strcpy(named,constcpathto);
        strcat(named,"/Restore_");
        strcat(named,std::to_string(i).c_str());
        if(opendir(named))
        {
            memset(named,0,50);
            continue;
        }
        else {
            break;
        }
    }

    char* order = new char[100];

    strcpy(order,"mkdir -p ");
    strcat(order,named);
    system(order);

    memset(order,0,100);
    strcpy(order,"cp -a ");
    strcat(order,constcpathfrom);
    strcat(order," ");
    strcat(order,named);
    system(order);

    fileSystem fileManager(named);
    string suffixStr = fileManager.fileList[0].substr(fileManager.fileList[0].find_last_of('.'));

    if(fileManager.fileList.size() == 1 && !suffixStr.compare(".8848pass")) {
        cout << "unpass........." << endl;
        cout << "file has a password" << endl;
        dialog_pwfordecrypt = new Dialog_PwForDecrypt(this);
        dialog_pwfordecrypt->setModal(true);
        QObject::connect(dialog_pwfordecrypt,SIGNAL(sendpwForDecrypt(QString)),this,SLOT(getpwforDecrypt(QString)));
        dialog_pwfordecrypt->exec();

        // pass
        char* unpasspath = new char[200];
        strcpy(unpasspath, named);
        char* packname = new char[50];
        int length = fileManager.fileList[0].substr(fileManager.fileList[0].find_last_of('/')).length() - strlen(".8848pass");
        strncpy(packname, fileManager.fileList[0].substr(fileManager.fileList[0].find_last_of('/')).c_str(), length);
        packname[length] = '\0';
        strcat(unpasspath, packname);

        delete[] unpasspath, packname;

        cout << "unpass " << fileManager.fileList[0] << " to " << pwfordecrypt.toStdString() << endl;
        bool res = decode((char *)fileManager.fileList[0].c_str(), (char*)unpasspath, (char*)pwfordecrypt.toStdString().c_str());
//        std::cout << res;
        if(res) {
            strcpy(order, "rm -rf ");
            strcat(order, fileManager.fileList[0].c_str());
            system(order);

        }
    }

    fileManager.getFileList(named);
    suffixStr = fileManager.fileList[0].substr(fileManager.fileList[0].find_last_of('.'));

    if(fileManager.fileList.size() == 1 && !suffixStr.compare(".8848pack")) {
        cout << "unpack........." << endl;
        int index = pathfrom.find_last_of("/");
        string dirName = pathfrom.substr(index, pathfrom.back());
        char* unpackpath = new char[200];
        strcpy(unpackpath, named);
        strcat(unpackpath, "/");
        strcat(unpackpath, dirName.c_str());

        cout << "unpack " << fileManager.fileList[0] << " to " << unpackpath << endl;
        unpack((char*)fileManager.fileList[0].c_str(), unpackpath);
        delete[] unpackpath;

        string order = "rm -rf " + fileManager.fileList[0];
        system(order.c_str());
    }


    fileManager.getFileList(named);
    suffixStr = fileManager.fileList[0].substr(fileManager.fileList[0].find_last_of('.'));
    cout << "suffix is : " << suffixStr << endl;
    if(!suffixStr.compare(".8848com")) {
        cout << "suffix is: " << suffixStr << " uncompress........." << endl;

        com_uncompress compressManager;
        cout << "uncompress " << named << endl;
        compressManager.uncompressFile(named);
    }


//    if(isRemote) {
//        // remote restore

//    }
}

void Dialog_restore::on_pushButton_3_clicked()
{
    isremote = true;
    filePathReFrom = QFileDialog::getExistingDirectory();
    ui->backReFrom->setText(filePathReFrom);

}
