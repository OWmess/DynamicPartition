//
// Created by owmess on 2022/11/28.
//

#ifndef DYNAMICPARITION_ERRORMESSAGE_H
#define DYNAMICPARITION_ERRORMESSAGE_H

#include <qerrormessage.h>

class ErrorMessage : QErrorMessage {
public:
    ErrorMessage() = delete;

    static void msg(QString str, QWidget *parent) {
        std::unique_ptr<QErrorMessage> qmsg(new QErrorMessage(parent));
        qmsg->showMessage(str);
        qmsg->exec();
    }


};

#endif //DYNAMICPARITION_ERRORMESSAGE_H
