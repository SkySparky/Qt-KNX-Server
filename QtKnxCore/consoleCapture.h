#include <QtCore>
#include <QObject>
#include <iostream>
#include <cstring>


class ConsoleCapture : public QObject {
	Q_OBJECT

public:
	ConsoleCapture();

private slots:
	void AllQuit();
	void ReadLoop(void);

private:
	bool m_quit;
	void AddLog(QString logMsg);


signals:
		void Log(QString logString);
		void ConsoleMsg(QString msg);
};