#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	//Get home path
	homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first();

	//Load save file
	saveFile = new QFile(homePath + "/.seriesdashboard");

	//Load config file
	loadConfigFile();

	//Setup action connections
	connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newSeries);
	connect(ui->actionRemove, &QAction::triggered, this, &MainWindow::removeSeries);
	connect(ui->watchButton, &QPushButton::clicked, this, &MainWindow::openEpisode);
	connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::setNext);
	connect(ui->previousButton, &QPushButton::clicked, this, &MainWindow::setPrevious);

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
	QString path = folder.path();

	bool alreadyExists = false;

	QList<SeriesEntry>::ConstIterator i;
	for (i = seriesEntries.begin(); i != seriesEntries.end(); i++) {
		if (i->name.compare(name) == 0) {
			alreadyExists = true;
			break;
		}
	}

	if (alreadyExists) {
		QMessageBox error;
		error.critical(this, "Error", "Series already added");
	} else {
		//Create new entry
		QJsonObject newObject;
		newObject.insert("path", path);
		newObject.insert("episode", 1);

		saveDataArray.append(newObject);

		QJsonDocument writeDocument(saveDataArray);

		//Write to file
		if (saveFile->open(QIODevice::WriteOnly)) {
			saveFile->write(writeDocument.toJson(QJsonDocument::Compact));
			saveFile->close();

			//Add to UI
			SeriesEntry newEntry;
			newEntry.name = name;
			newEntry.path = path;
			newEntry.episode = 1;

			seriesEntries.append(newEntry);
			ui->seriesBox->addItem(name);
			ui->seriesBox->setCurrentText(name);
		} else {
			QMessageBox error;
			error.critical(this, "Error",  "Could not open save file");
		}
	}
}

void MainWindow::removeSeries() {
//TODO: Remove series
}

void MainWindow::loadSaveData() {
	if (readSaveFile()) {
		SeriesEntry newEntry;
		QDir folder;
		for (int i = 0; i < saveDataArray.count(); i++) {
			folder.setPath(saveDataArray.at(i).toObject().value("path").toString());
			newEntry.path = folder.path();
			newEntry.name = folder.dirName();
			newEntry.episode = saveDataArray.at(i).toObject().value("episode").toInt();
			if (!newEntry.name.isNull()) {
				seriesEntries.append(newEntry);
				ui->seriesBox->addItem(newEntry.name);
			}
		}
	}
}

bool MainWindow::readSaveFile() {
	if (saveFile->exists()) {
		if (saveFile->open(QIODevice::ReadOnly)) {
			QByteArray data = saveFile->readAll();
			saveFile->close();

			QJsonParseError parseError;
			QJsonDocument saveDocument = QJsonDocument::fromJson(data, &parseError);

			if (parseError.error != QJsonParseError::NoError) {
				QMessageBox error;
				error.critical(this, "Parse error", "Could not parse save file");
				return false;
			} else {
				saveDataArray = saveDocument.array();
				return true;
			}
		} else {
			QMessageBox error;
			error.critical(this, "Error", "Save file cannot be opened");
			return false;
		}
	} else {
		return false;
	}
}

void MainWindow::openEpisode() {
	QString name = ui->seriesBox->currentText();

	const SeriesEntry* selected = nullptr;
	QList<SeriesEntry>::ConstIterator i;
	for (i = seriesEntries.begin(); i != seriesEntries.end(); i++) {
		if (i->name.compare(name) == 0) {
			selected = &*i;
			break;
		}
	}

	if (selected != nullptr) {
		QDir folder(selected->path);
		folder.setFilter(QDir::Files);
		QStringList extensions;

		QJsonArray extensionArray = parseConfig.find("extensions")->toArray();
		for (int i = 0; i < extensionArray.count(); i++) {
			extensions << extensionArray.at(i).toString();
		}
		folder.setNameFilters(extensions);
		QStringList files = folder.entryList();

		int ep;

		bool found = false;

		QStringList::ConstIterator j;
		for (j = files.begin(); j != files.end(); j++) {
			ep = parseEpisodeNumber(*j);
			if (ep != -1) {
				if (ep == selected->episode) {
					found = true;
					QString url = "file:";
					url.append(folder.path());
					url.append("/");
					url.append(*j);
					QDesktopServices::openUrl(QUrl(url));
					break;
				}
			} else {
				QMessageBox error;
				error.critical(this, "RegEx Error", "Could not parse episode name");
				break;
			}
		}

		if (found == false) {
			QMessageBox error;
			error.critical(this, "Error", "Could not find episode");
		}
	}
}

int MainWindow::parseEpisodeNumber(QString name) {
	//Setup RegEx
	QRegularExpression episodeFilter;
	episodeFilter.setPattern(parseConfig.find("regex")->toString());
	episodeFilter.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

	QRegularExpressionMatch match = episodeFilter.match(name);
	if (match.hasMatch()) {
		return match.captured(0).toInt();
	} else {
		return -1;
	}
}

void MainWindow::changeSelectedEpisode(int num) {
	QString name = ui->seriesBox->currentText();

	QJsonArray array;
	QJsonObject object;

	bool writeEnable = true;

	QList<SeriesEntry>::Iterator i;
	for (i = seriesEntries.begin(); i != seriesEntries.end(); i++) {
		if (i->name.compare(name) == 0) {
			if (i->episode > 1) {
				i->episode += num;
			} else {
				QMessageBox error;
				error.warning(this, "Error", "Episode number must be larger than 0");
				writeEnable = false;
				break;
			}
		}

		object.insert("path", i->path);
		object.insert("episode", i->episode);
		array.append(object);
	}

	QJsonDocument writeDocument(array);

	if (writeEnable) {
		if (saveFile->open(QIODevice::WriteOnly)) {
			saveFile->write(writeDocument.toJson(QJsonDocument::Compact));
			saveFile->close();
		} else {
			QMessageBox error;
			error.critical(this, "Error", "Could not open save file");
		}
	}
}

void MainWindow::setNext() {
	changeSelectedEpisode(1);
}

void MainWindow::setPrevious() {
	changeSelectedEpisode(-1);
}

void MainWindow::loadConfigFile() {
	QFile configFile(homePath + "/.config/seriesdashboard.json");

	if (!configFile.exists()) {
		QJsonArray extensions;
		extensions.append("*.mkv");
		extensions.append("*.mov");
		extensions.append("*.mp4");

		QJsonObject object;
		object.insert("regex", "((?<=\\.|\\s)\\d{2,3}(?=\\.|\\s))|((?<=S\\d\\dE)\\d\\d)|((?<=S\\d\\d\\.E)\\d\\d)");
		object.insert("extensions", extensions);

		QJsonDocument config(object);

		if (configFile.open(QIODevice::NewOnly)) {
			configFile.write(config.toJson(QJsonDocument::Indented));
			configFile.close();
		} else {
			QMessageBox error;
			error.critical(this, "File Error", "Could not write config file");
		}
	} else {
		if (configFile.open(QIODevice::ReadOnly)) {
			QByteArray configString = configFile.readAll();
			configFile.close();

			QJsonParseError parseError;
			QJsonDocument configDocument = QJsonDocument::fromJson(configString, &parseError);

			if (parseError.error == QJsonParseError::NoError) {
				parseConfig = configDocument.object();
			} else {
				QMessageBox error;
				error.critical(this, "Parse Error", "Could not parse config file");
			}
		}
	}
}
