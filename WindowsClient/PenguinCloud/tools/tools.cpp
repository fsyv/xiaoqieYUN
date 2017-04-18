#include "tools.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDateTime>
#include <QJsonObject>
Tools::Tools()
{

}

void *Tools::memstr(const void *src, memlen_t src_len, const void *des)
{
    return nullptr;
}
QVector<QStringList> Tools::getTableRow(QByteArray &byteArray)
{
    QVector<QStringList> vec;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byteArray, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject object = parse_doucment.object();
            QJsonValue value =  object.value(object.keys().at(0));
            QJsonArray array = value.toArray();


            for(int i = 0; i < array.size(); ++i)
            {
                QStringList list;

                QString time = QDateTime::fromTime_t(array.at(i).toObject()
                               .value("lastmodifytime").toInt()).toString("yyyy-MM-dd HH:mm:ss");
                list << array.at(i).toObject().value("name").toString()
                     << array.at(i).toObject().value("type").toString()
                     << QString::number(array.at(i).toObject().value("size").toInt())
                     << time;

                vec.push_back(list);
            }

        }
    }

    return vec;
}

FileType Tools::getFileType(const QString &filename)
{
     QStringList office;
     QStringList music;
     QStringList video;
     QStringList image;

     office << "doc" << "docx" << "xls" << "ppt" << "xlsx" << "pptx" << "pdf";
     music << "wav" << "mp3";
     video << "mp4" << "3gp" << "rm" << "rmvb";
     image << "png" << "jpg" << "ico";

     QString format = filename.split('.').last();
     if (office.contains(format.toLower()))
     {
        return Office;
     }
     else if (music.contains(format.toLower()))
     {
        return Music;
     }
     else if (video.contains(format.toLower()))
     {
        return Video;
     }
     else if (image.contains(format.toLower()))
     {
        return Image;
     }
}
