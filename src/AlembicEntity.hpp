#pragma once

#include <QEntity>
#include <QUrl>
#include <Alembic/AbcGeom/All.h>
#include <Alembic/AbcCoreFactory/All.h>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QMaterial>
#include <QQmlListProperty>

namespace abcentity
{
class CameraLocatorEntity;

class AlembicEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(
        float particleSize READ particleSize WRITE setParticleSize NOTIFY particleSizeChanged)
    Q_PROPERTY(
        float locatorScale READ locatorScale WRITE setLocatorScale NOTIFY locatorScaleChanged)
    Q_PROPERTY(QQmlListProperty<abcentity::CameraLocatorEntity> cameras READ cameras NOTIFY camerasChanged)

public:
    AlembicEntity(Qt3DCore::QNode* = nullptr);
    ~AlembicEntity() = default;

public:
    Q_SLOT const QUrl& url() const { return _url; }
    Q_SLOT const float& particleSize() const { return _particleSize; }
    Q_SLOT const float& locatorScale() const { return _locatorScale; }
    Q_SLOT void setUrl(const QUrl&);
    Q_SLOT void setParticleSize(const float&);
    Q_SLOT void setLocatorScale(const float&);

private:
    /// Delete all child entities/components
    void clear();
    void createMaterials();
    void loadAbcArchive();
    void visitAbcObject(const Alembic::Abc::IObject&, QEntity* parent);

    QQmlListProperty<CameraLocatorEntity> cameras() {
        return QQmlListProperty<CameraLocatorEntity>(this, _cameras);
    }

public:
    Q_SIGNAL void urlChanged();
    Q_SIGNAL void camerasChanged();
    Q_SIGNAL void particleSizeChanged();
    Q_SIGNAL void locatorScaleChanged();
    Q_SIGNAL void objectPicked(Qt3DCore::QTransform* transform);

protected:
    /// Scale child locators
    void scaleLocators() const;

private:
    QUrl _url;
    float _particleSize = 0.5;
    float _locatorScale = 1.0;
    Qt3DRender::QParameter* _particleSizeParameter;
    Qt3DRender::QMaterial* _cloudMaterial;
    Qt3DRender::QMaterial* _cameraMaterial;
    QList<CameraLocatorEntity*> _cameras;
};

} // namespace
