#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QObject>
#include "PathDataModel.h"
#include "PathDataList.h"
#include "FileSystemWatcher.h"
#include "EventClassModel.h"
#include "EventList.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    PathDataList pathList;
    EventList eventList;
    EventClassModel eventClass;

    FileSystemWatcher fsw;



    QObject::connect(&pathList,&PathDataList::itemAppended,&fsw,&FileSystemWatcher::addUserPath);
    QObject::connect(&pathList,&PathDataList::itemRemoved,&fsw,&FileSystemWatcher::removeUserPath);

    QObject::connect(&fsw,&FileSystemWatcher::putEventItem,&eventList,&EventList::appendItem);

    qmlRegisterType<EventClassModel> ("EventClass",1, 0 ,"EventClassModel");
    qmlRegisterType<PathDataModel> ("PathData",1,0,"PathDataModel");

    qmlRegisterUncreatableType<EventList> ("EventList",1,0,"EventList",QString("EventList should not be created in QML"));
    qmlRegisterUncreatableType<PathDataList>("PathList",1,0,"PathDataList",QString("PathDataList should not be created in QML"));


    engine.rootContext()->setContextProperty("pathDataList",&pathList);
    engine.rootContext()->setContextProperty("eventDataList",&eventList);
    engine.rootContext()->setContextProperty("fileSystemWatcher",&fsw);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    return app.exec();
}
