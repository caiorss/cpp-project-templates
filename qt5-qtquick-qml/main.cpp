// Modified from video:
// Introduction to Qt – Intro to Qt Quick Controls {tutorial}
//  - https://www.youtube.com/watch?v=uuhmSZxK1mk
//

#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QtQuick>
#include <QQmlContext>

#include "textfilemodel.hpp"

int main(int argc, char *argv[])
{
    std::cout << " [TRACE] Running QML app" << std::endl;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<TextFileModel>("com.qtdeveloper.textedit", 1, 0, "TextFileModel");
    std::cout << " [TRACE] Registered type TextFileModel" << std::endl;


    QQmlApplicationEngine engine;
    engine.load("qrc:/main.qml");
    if(engine.rootObjects().isEmpty())
        return EXIT_FAILURE;

    return app.exec();
}
