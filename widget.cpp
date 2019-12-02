//
// Created by 张淇 on 2019/11/27.
//

#include <iostream>
#include "widget.h"

widget::widget (QWidget *parent) : QWidget (parent) {
	port = 80;
	state = false;
	portEdit = new QLabel;
	portLabel = new QLabel;
	clientLabel = new QLabel;
	startBtn = new QPushButton;
	portBtn = new QPushButton;
	clientText = new QTextEdit;

	portLabel->setText ("port:");
	clientLabel->setText ("client list");
	auto *layoutMain = new QVBoxLayout (this);
	auto *layoutPort = new QVBoxLayout ();
	auto *layoutMes = new QVBoxLayout ();

	layoutPort->addWidget (portLabel);
	layoutPort->addWidget (portEdit);
	layoutMes->addWidget (clientLabel);
	layoutMes->addWidget (clientText);

	layoutMain->addLayout (layoutMes);
	layoutMain->addLayout (layoutPort);

	this->setLayout (layoutMain);
}

widget::widget (int mode, QWidget *parent) : QWidget (parent) {
	port = 80;
	state = true;
	portEdit = new QLabel;
	portLabel = new QLabel;
	clientLabel = new QLabel;
	startBtn = new QPushButton;
	portBtn = new QPushButton;
	clientText = new QTextEdit;
	auto *layoutMain = new QVBoxLayout (this);
	auto *layoutPort = new QVBoxLayout ();
	auto *layoutMes = new QVBoxLayout ();
	if (mode == 0) {
		portLabel->setText ("port:");
		clientLabel->setText ("client list");
		startBtn->setText ("quit");
		layoutPort->addWidget (portLabel);
		layoutPort->addWidget (portEdit);
		layoutPort->addWidget (startBtn);
		layoutMes->addWidget (clientLabel);
		layoutMes->addWidget (clientText);

		layoutMain->addLayout (layoutMes);
		layoutMain->addLayout (layoutPort);

		this->setLayout (layoutMain);
	} else {
		portLabel->setText ("Input your port:");
		portBtn->setText ("submit");
		layoutPort->addWidget (portEdit);
		layoutPort->addWidget (portLabel);
		layoutPort->addWidget (portBtn);
		layoutMain->addLayout (layoutPort);
		this->setLayout (layoutMain);
		QObject::connect (portBtn, SIGNAL (clicked ()), this, SLOT(slotPort ()));
	}

}

widget::~widget () = default;

void widget::clickedSlot () {

}

void widget::showFileDialog () {

}

void widget::slotOutput (const QString &out) {
	clientText->insertPlainText (out);
}

void widget::slotPort () {
	port = portEdit->text ().toInt ();
	state = true;
}


void widget::change () {
	state = false;
}