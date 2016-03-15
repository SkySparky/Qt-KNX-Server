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

    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int root READ root WRITE setRoot NOTIFY rootChanged)
    Q_PROPERTY(QString tags READ tags WRITE setTags NOTIFY tagsChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

    Q_PROPERTY(QString groupAddr READ groupAddr WRITE setGroupAddr NOTIFY groupAddrChanged)
    Q_PROPERTY(QString groupAddr1 READ groupAddr1 WRITE setGroupAddr1 NOTIFY groupAddr1Changed)
    Q_PROPERTY(QString groupAddr2 READ groupAddr2 WRITE setGroupAddr2 NOTIFY groupAddr2Changed)
    Q_PROPERTY(QString groupAddr3 READ groupAddr3 WRITE setGroupAddr3 NOTIFY groupAddr3Changed)
    Q_PROPERTY(QString groupAddr4 READ groupAddr4 WRITE setGroupAddr4 NOTIFY groupAddr4Changed)

    Q_PROPERTY(QString statusAddr READ statusAddr WRITE setStatusAddr NOTIFY statusAddrChanged)
    Q_PROPERTY(QString statusAddr1 READ statusAddr1 WRITE setStatusAddr1 NOTIFY statusAddr1Changed)
    Q_PROPERTY(QString statusAddr2 READ statusAddr2 WRITE setStatusAddr2 NOTIFY statusAddr2Changed)
    Q_PROPERTY(QString statusAddr3 READ statusAddr3 WRITE setStatusAddr3 NOTIFY statusAddr3Changed)
    Q_PROPERTY(QString statusAddr4 READ statusAddr4 WRITE setStatusAddr4 NOTIFY statusAddr4Changed)

    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString value1 READ value1 WRITE setValue1 NOTIFY value1Changed)
    Q_PROPERTY(QString value2 READ value2 WRITE setValue2 NOTIFY value2Changed)
    Q_PROPERTY(QString value3 READ value3 WRITE setValue3 NOTIFY value3Changed)
    Q_PROPERTY(QString value4 READ value4 WRITE setValue4 NOTIFY value4Changed)


public:
    typedef struct {
        int     index;              // device index
        int     type;               // device type (see: en_devType)
        int     root;           // 1: root device that is displayed on main screen, 0: no root (default)
        QString description;    // device description
        QString tags;           // tags

        QString groupAddr;      // device group Address
        QString groupAddr1;      // device group Address
        QString groupAddr2;      // device group Address
        QString groupAddr3;      // device group Address
        QString groupAddr4;      // device group Address

        QString statusAddr;     // device status address
        QString statusAddr1;     // device status address
        QString statusAddr2;     // device status address
        QString statusAddr3;     // device status address
        QString statusAddr4;     // device status address

        QString value;          // current device value (1Byte)
        QString value1;          // current device value (1Byte)
        QString value2;          // current device value (1Byte)
        QString value3;          // current device value (1Byte)
        QString value4;          // current device value (1Byte)
    } tp_groupAddrObj;

    GroupAddrObject(tp_groupAddrObj & objData) {

        m_obj.index = objData.index;
        m_obj.type = objData.type;
        m_obj.root = objData.root;
        m_obj.tags = objData.tags;
        m_obj.description = objData.description;

        m_obj.groupAddr = objData.groupAddr;
        m_obj.groupAddr1 = objData.groupAddr1;
        m_obj.groupAddr2 = objData.groupAddr2;
        m_obj.groupAddr3 = objData.groupAddr3;
        m_obj.groupAddr4 = objData.groupAddr4;

        m_obj.statusAddr = objData.statusAddr;
        m_obj.statusAddr1 = objData.statusAddr1;
        m_obj.statusAddr2 = objData.statusAddr2;
        m_obj.statusAddr3 = objData.statusAddr3;
        m_obj.statusAddr4 = objData.statusAddr4;

        m_obj.value = objData.value;
        m_obj.value1 = objData.value1;
        m_obj.value2 = objData.value2;
        m_obj.value3 = objData.value3;
        m_obj.value4 = objData.value4;

        setTags(m_obj.tags);
        setType(m_obj.type);
        setValue(m_obj.value);
        setValue1(m_obj.value1);
        setValue2(m_obj.value2);
        setValue3(m_obj.value3);
        setValue4(m_obj.value4);
    }

    typedef enum {  //public enum
        DEV_SWITCH,
        DEV_DIMMER,
        DEV_RGB,
        DEV_SHUTTER,
        DEV_TAGBUTTON,
        DEV_TEMP
    } en_devType;

public:

    int index() const {  // Get device type (see: en_devType)
        return(m_obj.index);
    }
    int type() const {  // Get device type (see: en_devType)
        return(m_obj.type);
    }
    int root() const {  // Get device type (see: en_devType)
        return(m_obj.root);
    }
    QString description() const {   // Get device's descripton
        return(m_obj.description);
    }
    QString tags() const {  // Get device's tags
        return(m_obj.tags);
    }

    QString groupAddr() const { // Get device's group address
        return(m_obj.groupAddr);
    }
    QString groupAddr1() const { // Get device's group address
        return(m_obj.groupAddr1);
    }
    QString groupAddr2() const { // Get device's group address
        return(m_obj.groupAddr2);
    }
    QString groupAddr3() const { // Get device's group address
        return(m_obj.groupAddr3);
    }
    QString groupAddr4() const { // Get device's group address
        return(m_obj.groupAddr4);
    }

    QString statusAddr() const {    // Get device's status address
        return(m_obj.statusAddr);
    }
    QString statusAddr1() const {    // Get device's status address
        return(m_obj.statusAddr1);
    }
    QString statusAddr2() const {    // Get device's status address
        return(m_obj.statusAddr2);
    }
    QString statusAddr3() const {    // Get device's status address
        return(m_obj.statusAddr3);
    }
    QString statusAddr4() const {    // Get device's status address
        return(m_obj.statusAddr4);
    }

    QString value() const { // Get device's value
        return(m_obj.value);
    }
    QString value1() const { // Get device's value
        return(m_obj.value1);
    }
    QString value2() const { // Get device's value
        return(m_obj.value2);
    }
    QString value3() const { // Get device's value
        return(m_obj.value3);
    }
    QString value4() const { // Get device's value
        return(m_obj.value4);
    }

public slots:
    void setIndex( int index ) {  // Set device type (see: en_devType)
        m_obj.index = index;
        emit indexChanged();
    }
    void setRoot( int root ) {  // Set device type (see: en_devType)
        m_obj.root = root;
        emit rootChanged();
    }
    void setType( int type ) {  // Set device type (see: en_devType)
        m_obj.type = type;
        emit typeChanged();
    }
    void setDescription(QString description ) { // Set device description
        m_obj.description = description;
        emit descriptionChanged();
    }
    void setTags( QString tags ) {      //Set tags
        m_obj.tags = tags;
        emit tagsChanged();
    }

    void setGroupAddr( QString groupAddr ) {    // Set device group address
        m_obj.groupAddr = groupAddr;
        emit groupAddrChanged();
    }
    void setGroupAddr1( QString groupAddr1 ) {    // Set device group address
        m_obj.groupAddr1 = groupAddr1;
        emit groupAddr1Changed();
    }
    void setGroupAddr2( QString groupAddr2 ) {    // Set device group address
        m_obj.groupAddr2 = groupAddr2;
        emit groupAddr2Changed();
    }
    void setGroupAddr3( QString groupAddr3 ) {    // Set device group address
        m_obj.groupAddr3 = groupAddr3;
        emit groupAddr3Changed();
    }
    void setGroupAddr4( QString groupAddr4 ) {    // Set device group address
        m_obj.groupAddr4 = groupAddr4;
        emit groupAddr4Changed();
    }

    void setStatusAddr( QString statusAddr ) {  // Set status address
        m_obj.statusAddr = statusAddr;
        emit statusAddrChanged();
    }
    void setStatusAddr1( QString statusAddr1 ) {  // Set status address
        m_obj.statusAddr1 = statusAddr1;
        emit statusAddr1Changed();
    }
    void setStatusAddr2( QString statusAddr2 ) {  // Set status address
        m_obj.statusAddr2 = statusAddr2;
        emit statusAddr2Changed();
    }
    void setStatusAddr3( QString statusAddr3 ) {  // Set status address
        m_obj.statusAddr3 = statusAddr3;
        emit statusAddr3Changed();
    }
    void setStatusAddr4( QString statusAddr4 ) {  // Set status address
        m_obj.statusAddr4 = statusAddr4;
        emit statusAddr4Changed();
    }

    void setValue( QString value ) {    // Set value
        m_obj.value = value;
        emit valueChanged();
    }
    void setValue1( QString value1 ) {    // Set value
        m_obj.value1 = value1;
        emit value1Changed();
    }
    void setValue2( QString value2 ) {    // Set value
        m_obj.value2 = value2;
        emit value2Changed();
    }
    void setValue3( QString value3 ) {    // Set value
        m_obj.value3 = value3;
        emit value3Changed();
    }
    void setValue4( QString value4 ) {    // Set value
        m_obj.value4 = value4;
        emit value4Changed();
    }

signals:
    void indexChanged(void);        // emitted if device type is changed
    void typeChanged(void);         // emitted if device type is changed
    void rootChanged(void);         // emitted if device type is changed
    void descriptionChanged(void);  // emitted if device's description is changed
    void tagsChanged(void);         // emitted if device's tags are changed

    void groupAddrChanged(void);    // emitted if device's group address is changed
    void groupAddr1Changed(void);    // emitted if device's group address is changed
    void groupAddr2Changed(void);    // emitted if device's group address is changed
    void groupAddr3Changed(void);    // emitted if device's group address is changed
    void groupAddr4Changed(void);    // emitted if device's group address is changed

    void statusAddrChanged(void);   // emitted if device's status address is changed
    void statusAddr1Changed(void);   // emitted if device's status address is changed
    void statusAddr2Changed(void);   // emitted if device's status address is changed
    void statusAddr3Changed(void);   // emitted if device's status address is changed
    void statusAddr4Changed(void);   // emitted if device's status address is changed

    void valueChanged(void);        // emitted if device's value is changed
    void value1Changed(void);        // emitted if device's value is changed
    void value2Changed(void);        // emitted if device's value is changed
    void value3Changed(void);        // emitted if device's value is changed
    void value4Changed(void);        // emitted if device's value is changed


private:
    tp_groupAddrObj m_obj;  // internal object properties
};

#endif // GROUPADDROBJECT_H
