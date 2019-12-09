#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace dia {

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;

	explicit MainWindow(const MainWindow& )    = delete;
	explicit MainWindow(MainWindow&& )         = delete;

public:
	MainWindow& operator= (const MainWindow& ) = delete;
	MainWindow& operator= (MainWindow&& )      = delete;
};

} // namespace dia

#endif // MAINWINDOW_H
