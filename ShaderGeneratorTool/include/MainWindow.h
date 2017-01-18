#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NGLScene.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals :
    void exportClass(const QString &_file, bool _export);
    void vertexShaderChanged(const QString &_name);
    void fragmentShaderChanged(const QString &_name);
    void programNameChanged(const QString &_name);
private slots :
    void exportClassClicked();
    void vertexShaderClicked();
    void fragmentShaderClicked();
    void programNameChanged();

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *m_ui;
		/// @brief our openGL widget
		NGLScene *m_gl;
};

#endif // MAINWINDOW_H
