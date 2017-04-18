#ifndef FOLDER_H
#define FOLDER_H

#include "fileobject.h"

class Folder : public FileObject
{
    Q_OBJECT
public:
    Folder(QString remoteName, QDateTime dateTime);
};

#endif // FOLDER_H
