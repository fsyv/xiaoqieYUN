#ifndef TOOLS_H
#define TOOLS_H

#include <QVector>

typedef unsigned long memlen_t;

//预览的文件类型
typedef enum _FileType{
    PDF = 0,    //pdf 包括office(经过服务器转成pdf后预览)
    PICTURE,    //图片
    MP3,        //音乐
    MP4,        //视频
    GIF         //动图
}FileType;

class Tools
{
public:
    Tools();
    static void *memstr(const void *src, memlen_t src_len, const void *des);
    static QVector<QStringList> getTableRow(QByteArray &byteArray);
    static FileType getFileType(const QString &filename);
    static QString sizeToString(const qint64 &fileSize);
};

#endif // TOOLS_H
