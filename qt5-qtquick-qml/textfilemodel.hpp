#ifndef TEXTFILEMODEL_HPP
#define TEXTFILEMODEL_HPP

#include <QObject>
#include <QUrl>

class TextFileModel : public QObject
{
    QUrl    m_file;
    QString m_textBuffer;

    Q_OBJECT
    Q_PROPERTY(QUrl file READ file WRITE setFile NOTIFY fileChanged)
    Q_PROPERTY(QString text READ read WRITE write NOTIFY fileChanged)
public:
    explicit TextFileModel(QObject *parent = nullptr);

signals:
    void fileChanged();

public slots:   
    QUrl    file() const;
    void    setFile(QUrl const& file);

    QString read() const;
    void    write(QString const& text);
    void    flush();
};

#endif // TEXTFILEMODEL_HPP
