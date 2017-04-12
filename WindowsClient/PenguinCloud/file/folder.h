#ifndef FOLDER_H
#define FOLDER_H

#include "fileobject.h"

class Folder : public FileObject
{
public:
    Folder(QString name, QDateTime dateTime);
};

#endif // FOLDER_H
