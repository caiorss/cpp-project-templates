#include <iostream>
#include <iomanip>
#include <functional>
#include <cassert>
#include <sstream>

#include <QtWidgets>
#include <QApplication>
#include <QtUiTools/QtUiTools>
#include <QSysInfo>
#include <QtConcurrent/QtConcurrent>

#include "FormLoader.hpp"

class CustomerForm: public FormLoader
{
private:
    QWidget*     form;
    // Extract children widgets from from file
    QLineEdit*   entryUserName;
    QLineEdit*   entryUserEmail;
    QPushButton* btnClose;
    QPushButton* btnReset;
    QPushButton* btnSubmit;
    QTextEdit*   display;
    QLabel* DateTimeDisplay;
public:


    CustomerForm()
        : FormLoader(":/assets/user_interface.ui")
    {
        form = this->FormLoader::GetForm();
        // Load controls named in the form "user_interface.ui"
        entryUserName = form->findChild<QLineEdit*>("entryUserName");
        entryUserEmail = form->findChild<QLineEdit*>("entryUserEmail");

        btnClose     = form->findChild<QPushButton*>("btnClose");
        btnReset     = form->findChild<QPushButton*>("btnReset");
        btnSubmit    = form->findChild<QPushButton*>("btnSubmit");
        display      = form->findChild<QTextEdit*>("OutputDisplay");

        // ========== Set Event Handlers =================//

        // Signals and slots with lambda function
        QObject::connect(btnClose, &QPushButton::clicked, []
                         {
                             QApplication::exit(0);
                         });

        // Signals and slots with member function pointer
        QObject::connect(btnReset, &QPushButton::clicked, this, &CustomerForm::Reset);

        // Signals and slots with lambda function
        QObject::connect(btnSubmit, &QPushButton::clicked, [self = this]
                         {
                             self->Submit();
                         });

        // Save application state when the main Window is destroyed
        QObject::connect(this, &QMainWindow::destroyed, []{
            std::cout << " [INFO] Window closed Ok" << std::endl;
        });                

    } // --- End of CustomerForm ctor ------//

    void Reset()
    {
        this->entryUserName->clear();
        this->entryUserEmail->clear();
        this->display->clear();
    }

    void Submit()
    {
        std::cout << "Submit: User Name = " << entryUserName->text().toStdString()
                  << "  ; User Email = " << entryUserEmail->text().toStdString()
                  << std::endl;
        QString line = "User => name = " + entryUserName->text()
                       + " ; email "  + entryUserEmail->text();
        display->append(line + "\n");
        entryUserName->clear();
        entryUserEmail->clear();
    }

};


int main(int argc, char** argv)
{
    std::cout << " [INFO] Starting Application" << std::endl;

    QApplication app(argc, argv);
    app.setOrganizationName("UniqueOrganizatioName");
    app.setOrganizationDomain("myorganization.net.domain");
    app.setApplicationName("ApplicationName");

    std::cout << " [INFO] Starting Application" << std::endl;

    // Useful for debugging
    std::cout << " [INFO] QTVersion = " << ::qVersion() << std::endl;


    CustomerForm form;
    form.setWindowIcon(QIcon(":/images/appicon.png"));
    form.showNormal();


    return app.exec();
}

