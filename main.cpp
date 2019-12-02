#include "webConnect.hpp"

int main (int argc, char const *argv[]) {
	while (true) {
		QTextCodec *codec = QTextCodec::codecForName ("utf-8");
		QTextCodec::setCodecForLocale (codec);
		QApplication app (argc, const_cast<char **>(argv));
		auto *queryPort = new QDialog;
		auto *portEdit = new QLineEdit;
		auto *portLabel = new QLabel;
		auto *portBtn = new QPushButton;
		auto *pathLabel = new QLabel;
		auto *pathEdit = new QLineEdit;
		pathLabel->setText ("Input Path");
		queryPort->setWindowTitle ("Input Port");
		auto *layoutPort = new QVBoxLayout (queryPort);
		portLabel->setText ("Input your port:");
		portBtn->setText ("submit");
		layoutPort->addWidget (portLabel);
		layoutPort->addWidget (portEdit);
		layoutPort->addWidget (pathLabel);
		layoutPort->addWidget (pathEdit);
		layoutPort->addWidget (portBtn);
		queryPort->setLayout (layoutPort);
		QObject::connect (portBtn, SIGNAL (clicked ()),
		                  queryPort, SLOT(accept ()));
		if (queryPort->exec () == QDialog::Accepted) {
			int port = 80;
			char *serverpath = getcwd (nullptr, 0);
			widget serverWindow (0);
			port = portEdit->text ().toInt ();
			QByteArray ba = pathEdit->text ().toLatin1 ();
			serverpath = ba.data ();
			std::cout << port << std::endl;
			serverWindow.portEdit->setText (portEdit->text ());
			webConnect conn (AF_INET, INADDR_ANY, port, serverpath);
			conn.preServer (AF_INET, SOCK_STREAM, IPPROTO_TCP);
			QObject::connect (serverWindow.startBtn, SIGNAL (clicked ()),
			                  &conn, SLOT(slotService ()));
			QObject::connect (serverWindow.startBtn, SIGNAL (clicked ()),
			                  &serverWindow, SLOT(change ()));
			QObject::connect (serverWindow.startBtn, SIGNAL (clicked ()),
			                  &serverWindow, SLOT(close ()));
			QObject::connect (&conn, &webConnect::outSignal, &serverWindow, &widget::slotOutput);
			serverWindow.show ();
			std::cout << "server start initing" << std::endl;
			std::thread service (&webConnect::service, &conn);
			service.detach ();
			QApplication::exec ();
			if (!serverWindow.state) {
				return 0;
			}
		}
	}
}