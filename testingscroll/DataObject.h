#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY onSetName)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY onSetIcon)
public:
    DataObject( QString name, QString icon ) : m_name(name), m_icon(icon) {

    }

public:
    QString name() const {
        return(m_name);
    }
    QString icon() const {
        return(m_icon);
    }

public slots:
    void setName( QString name ) {
        m_name = name;
    }
    void setIcon( QString icon ) {
        m_icon = icon;
    }

signals:
    void onSetName(void);
    void onSetIcon(void);

private:
    QString m_name;
    QString m_icon;
};

#endif // DATAOBJECT_H
