#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	//Get home path
	homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first();

	//Load save file
	saveFile = new QFile(homePath + "/.seriesdashboard");

	//Setup action connections
	newButtonConnection = connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newSeries);
	removeButtonConnection = connect(ui->actionRemove, &QAction::triggered, this, &MainWindow::removeSeries);

	//Load save data
	loadSaveData();
}

MainWindow::~MainWindow() {
	delete saveFile;
	delete ui;
}

void MainWindow::newSeries() {
	QDir folder(QFileDialog::getExistingDirectory(this, "Select", homePath, QFileDialog::ShowDirsOnly));
	QString name = folder.dirName();

	if (seriesTitles.contains(name)) {
		QMessageBox error;
		error.critical(this, "Error", "Series already added");
	} else {
		//TODO: write series to save file
	}
}

void MainWindow::removeSeries() {

}

void MainWindow::loadSaveData() {
	QJsonArray jsonArray = readSaveFile();
	if (!jsonArray.isEmpty()) {
		QString name;
		for (int i = 0; i < jsonArray.count(); i++) {
			name = jsonArray.at(i).toObject().value("title").toString();
			if (!name.isNull()) {
				seriesTitles.append(name);
				ui->seriesBox->addItem(name);
			}
		}
	}
}

QJsonArray MainWindow::readSaveFile() {
	QJsonArray jsonArray;
	if (saveFile->exists()) {
		if (saveFile->open(QIODevice::ReadOnly)) {
			QByteArray data = saveFile->readAll();
			saveFile->close();

			QJsonParseError parseError;
			QJsonDocument saveDocument = QJsonDocument::fromJson(data, &parseError);

			if (!data.isNull() && saveDocument.isNull()) {
				QMessageBox error;
				error.critical(this, "Parse error", "Could not parse save file");
			} else {
				jsonArray = saveDocument.array();
			}
		} else {
			QMessageBox error;
			error.critical(this, "Error", "Save file cannot be opened");
		}
	}
	return jsonArray;
}
