#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMetaObject>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct SeriesEntry {
	QString path;
	QString name;
	int episode;
};

class MainWindow : public QMainWindow {
	Q_OBJECT

  public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

  private:
	//Generates config file /etc/seriesdashboard.json
	void loadConfigFile();

	//Loads save data to UI and seriesTitles
	void loadSaveData();

	//Return true if save data is loaded to saveDataArray
	bool readSaveFile();

	//Extract episode number from file name
	int parseEpisodeNumber(QString name);

	//Adds num to the currently selected episode number
	void changeSelectedEpisode(int num);

	void updateEpisodeLabel();

	Ui::MainWindow* ui;

	QJsonObject parseConfig;

	//User home path
	QString homePath;

	//Save file
	QFile* saveFile;

	//List of series entries
	QList<SeriesEntry> seriesEntries;

	QJsonArray saveDataArray;

	int labelEpisodeNumber;

  public slots:
	void newSeries();
	void removeSeries();
	void openEpisode();
	void setNext();
	void setPrevious();
};
#endif // MAINWINDOW_H
