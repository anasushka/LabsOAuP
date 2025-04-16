#include "folderfilescount.h"
#include <QFileInfoList>

void FolderFilesCount::count(const QString &path, int &countDir, int &countFiles){
    QDir dir(path);

    if(!dir.exists()) return;
    else{
        QFileInfoList list = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
        for(const QFileInfo &info : list) {
            if(info.isDir()) {
                countDir++;
                count(info.absoluteFilePath(), countDir, countFiles);
            } else if(info.isFile()) {
                countFiles++;
            }
        }
    }
}
