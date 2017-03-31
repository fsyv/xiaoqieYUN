#ifndef LOGIN_H
#define LOGIN_H
#include "connecttoserver.h"

class Login
{
public:
    Login();
    void sendUserInfo(QString str);
private:
    ConnectToServer *conn;
};

#endif // LOGIN_H
