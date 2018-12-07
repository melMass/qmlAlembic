#pragma once

#include "AlembicEntity.hpp"
#include <QtQml>
#include <QQmlExtensionPlugin>

namespace abcentity
{

class AlembicEntityQmlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "alembicEntity.qmlPlugin")

public:
    void initializeEngine(QQmlEngine* engine, const char* uri) override {}
    void registerTypes(const char* uri) override
    {
        Q_ASSERT(uri == QLatin1String("AlembicEntity"));
        qmlRegisterType<AlembicEntity>(uri, 2, 0, "AlembicEntity");
        qmlRegisterUncreatableType<CameraLocatorEntity>(uri, 2, 0, "CameraLocatorEntity",
                                                        "Can't create CameraLocatorEntity intances from QML.");
        qmlRegisterUncreatableType<PointCloudEntity>(uri, 2, 0, "PointCloudEntity",
                                                        "Can't create PointCloudEntity intances from QML.");
    }
};

} // namespace
