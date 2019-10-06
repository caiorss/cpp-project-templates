#ifndef FORMLOADER_HPP
#define FORMLOADER_HPP

#include <QtWidgets>
#include <QApplication>
#include <QtUiTools/QtUiTools>
#include <QSysInfo>
#include <QtConcurrent/QtConcurrent>

/**
  * Class FormLoader is a helper for loading QtWidgets dynamically
  * from a Form without compilation. */
class FormLoader: public QMainWindow
{
private:
    QString  formFile;
    QWidget* form;
public:
    FormLoader(QString path)
    {
        this->LoadForm(path);
        this->setCentralWidget(form);
        this->setWindowTitle(form->windowTitle());

        // Set Width and height
        this->resize(form->width(), form->height());

        // Center Window in the screen
        this->setGeometry(
            QStyle::alignedRect(
                Qt::LeftToRight,
                Qt::AlignCenter,
                this->size(),
                qApp->desktop()->availableGeometry()
                )
            );
    }

    virtual ~FormLoader() = default;

    // Forbid copy, aka Deep Copy
    FormLoader(FormLoader const&) = delete;
    FormLoader& operator=(FormLoader const&) = delete;

    void LoadForm(QString filePath)
    {
        QUiLoader loader;
        formFile = filePath;
        QFile file(filePath);
        // file.open(QFile::ReadOnly);
        form = loader.load(&file, nullptr);
        assert(form != nullptr);
        file.close();
    }

    QWidget* GetForm() { return form;  }
};


#endif // FORMLOADER_HPP
