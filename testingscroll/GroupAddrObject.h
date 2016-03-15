#ifndef GROUPADDROBJECT_H
#define GROUPADDROBJECT_H

/*
*  GroupAddrObject is a delegate list object that is used from devHandler to
*  dynamically fill a list of objects in the screen.
*  The object is initialized in constructor has 4 properties that are common
*  with the DeviceButton.qml object.
*  When one of the properties is changed then a signal is emmited and the
*  corresponding slot in QML file is triggered. The QML slot always has the
*  name "on<Property-name>Changed" by default.
*/

#include <QObject>
#include <QDebug>

class GroupAddrObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString groupAddr READ groupAddr WRITE setGroupAddr NOTIFY groupAddrChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString tags READ tags WRITE setTags NOTIFY tagsChanged)

public:
    GroupAddrObject( int type, QString description, QString groupAddr, QString value, QString tags )
        : m_type(type), m_description(description), m_groupAddr(groupAddr), m_value(value), m_tags(tags) {

        setValue(value);
        setTags(tags);
        setType(type);
    }

    typedef enum {  //public enum
        DEV_SWITCH,
        DEV_DIMMER,
        DEV_RGB,
        DEV_SHUTTER
    } en_devType;

public:
    int type() const {
        return(m_type);
    }
    QString description() const {
        return(m_description);
    }
    QString groupAddr() const {
        return(m_groupAddr);
    }
    QString value() const {
        return(m_value);
    }
    QString tags() const {
        return(m_tags);
    }

public slots:
    void setType( int type ) {
        m_type = type;
        emit typeChanged();
    }
    void setDescription(QString description ) {
        m_description = description;
        emit descriptionChanged();
    }
    void setGroupAddr( QString groupAddr ) {
        m_groupAddr = groupAddr;
        emit groupAddrChanged();
    }
    void setValue( QString value ) {
        m_value = value;
        emit valueChanged();
    }
    void setTags( QString tags ) {
        m_tags = tags;
        emit tagsChanged();
    }

signals:
    void typeChanged(void);
    void descriptionChanged(void);
    void groupAddrChanged(void);
    void valueChanged(void);
    void tagsChanged(void);

private:
    int m_type;
    QString m_description;
    QString m_groupAddr;
    QString m_value;
    QString m_tags;
};

#endif // GROUPADDROBJECT_H
