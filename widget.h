//
// Created by 张淇 on 2019/11/27.
//

#ifndef NETWORK_LAB1_WIDGET_H
#define NETWORK_LAB1_WIDGET_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QApplication>
#include <QTextCodec>
#include <QtGui>
#include <QObject>
#include <QTextCodec>
#include <QVBoxLayout>
#include <QTextStream>
#include <QCloseEvent>

class widget : public QWidget {
Q_OBJECT

public:

	QLabel *portEdit;
	QLabel *portLabel, *clientLabel;
	QPushButton *startBtn, *portBtn;
	QTextEdit *clientText;
	int port;
	bool state;

public slots:

	static void showFileDialog ();

	static void clickedSlot ();

public:
	explicit widget (QWidget *parent = nullptr);

	explicit widget (int mode, QWidget *parent = nullptr);


	~widget () override;

public slots:

	void slotOutput (const QString &out);

	void slotPort ();
};

#endif //NETWORK_LAB1_WIDGET_H
