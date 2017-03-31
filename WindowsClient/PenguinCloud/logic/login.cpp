#include "login.h"
#include "macro.h"
Login::Login()
{
    conn = ConnectToServer::getInstance();
}



void Login::sendUserInfo(QString str)
{
    Msg *msg = (Msg*)new char[(1024* 64* + 1) * sizeof(char)];

    msg->m_uiCheckCrc = (unsigned int)0xAFAFAFAF;
    msg->m_eMsgType = Login_Msg;
    msg->m_iMsgLen = str.length();

    memcpy(msg->m_aMsgData, str.toStdString().c_str() , strlen(str.toStdString().c_str()));
    msg->m_aMsgData[strlen(str.toStdString().c_str())] = '\0';

    char *pmsg = (char*)msg;
    conn->write(pmsg, sizeof(Msg) + str.length() + 1);
}
