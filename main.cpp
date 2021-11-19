#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QObject>
#include "pathdatamodel.h"
#include "pathdatalist.h"
#include "filesystemwatcher.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    PathDataList pathList;

    FileSystemWatcher fsw;

    fsw.addPath("/Users/kacperhandzel/Documents/Emiter");

    QObject::connect(&pathList,&PathDataList::itemAppended,&fsw,&FileSystemWatcher::addUserPath);
    QObject::connect(&pathList,&PathDataList::itemRemoved,&fsw,&FileSystemWatcher::removeUserPath);


    qmlRegisterType<PathDataModel> ("PathData",1,0,"PathDataModel");
    qmlRegisterUncreatableType<PathDataList>("PathList",1,0,"PathDataList",QString("PathDataList should not be created in QML"));

    engine.rootContext()->setContextProperty("pathDataList",&pathList);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    return app.exec();
}
