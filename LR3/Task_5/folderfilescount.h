#ifndef FOLDERFILESCOUNT_H
#define FOLDERFILESCOUNT_H

#include <QDir>
#include <QString>

class FolderFilesCount
{
public:
    static void count(const QString &path, int &countdDr, int &countFiles);

};

#endif // FOLDERFILESCOUNT_H
