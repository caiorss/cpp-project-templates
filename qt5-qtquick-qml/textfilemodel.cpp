#include "textfilemodel.hpp"
#include <iostream>
#include <QFile>
#include <QTextStream>

QUrl
TextFileModel::file() const
{
    return m_file;
}

void
TextFileModel::setFile(const QUrl &file)
{
    std::cout << " [INFO] File set to " << file.toString().toStdString() << std::endl;
    m_file = file;
    emit this->fileChanged();
}

QString
TextFileModel::read() const
{
    QFile file(m_file.toLocalFile());
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString txt = file.readAll();
        // std::cout << "Text = " << txt.toStdString() << std::endl;
        return txt;
    }
    return "";
}

void
TextFileModel::write(QString const& text)
{
    m_textBuffer = text;
}

void
TextFileModel::flush()
{
    QFile file(m_file.toLocalFile());
    if(!(file.open(QIODevice::WriteOnly | QIODevice::Text)))
    {
        file.close();
        return;
    }
    QTextStream ss(&file);
    ss << m_textBuffer;
    file.close();
}

TextFileModel::TextFileModel(QObject *parent) : QObject(parent)
{

}
