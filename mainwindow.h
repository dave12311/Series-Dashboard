#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMetaObject>
#include <QFileDialog>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

  public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

  private:
	//Loads save data to UI and seriesTitles
	void loadSaveData();

	//Returns save data from file
	QJsonArray readSaveFile();

	Ui::MainWindow* ui;
	QMetaObject::Connection newButtonConnection, removeButtonConnection;

	//User home path
	QString homePath;

	//Save file
	QFile* saveFile;

	//List of series titles
	QList<QString> seriesTitles;

  public slots:
	void newSeries();
	void removeSeries();
};
#endif // MAINWINDOW_H
