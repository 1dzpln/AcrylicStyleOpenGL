#include <QApplication>
#include <QFile>
#include <QMutex>
#include <QFile>
#include "core.h"
#include "mainwindow.h"

/*!
    \mainpage   Программа, реализующая стиль Acrylic с использованием API OpenGL
    \authors    Зенин Вячеслав
    \version    1.0.0.0.
    \date       Сентябрь 2020.
    \copyright  Свободного пользования. Открытая.

    <STRONG> Назначение программы </STRONG> \n\n
    Реализация стиля Acrylic с использованием API OpenGL 3.3 \n
    Используются следующие проходы для шейдера:
        - размытие фона методом Гаусса
        - смешивание с накладкой и шумом
 */

void LogOutput(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    static QFile        *fileOut = nullptr;
    static QTextStream	strm;
    static QMutex		mut;

    mut.lock();

    if (!fileOut) {
        fileOut = new QFile("log.txt");
        fileOut->open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly);
        static const unsigned char bomMarker[] = { 0xef, 0xbb, 0xbf };
        fileOut->write(reinterpret_cast<const char*>(bomMarker), 3);
        strm.setDevice(fileOut);
        strm.setCodec("UTF-8");
    }

    switch (type) {
        case QtDebugMsg:
            strm << "Debug: " << msg << endl << flush;
            break;
        case QtInfoMsg:
            strm << "Info: " << msg << endl << flush;
            break;
        case QtWarningMsg:
            strm << "Warning: " << msg << endl << flush;
            break;
        case QtCriticalMsg:
            strm << "Critical: " << msg << endl << flush;
            break;
        case QtFatalMsg:
            strm << "Fatal: " << msg << endl << flush;
            abort();
    }

    mut.unlock();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(LogOutput);
    QApplication a(argc, argv);
    QFile styleFile(":/Content/Style/blueStyle/style.qss");
    if(styleFile.open(QFile::ReadOnly))
    {
        QString styleSheetStr = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleSheetStr);
    }

    MainWindow mWindow;    
    Core core;
    core.initCore();
    mWindow.setScene(core.getScene());
    mWindow.showMaximized();
    return a.exec();
}
