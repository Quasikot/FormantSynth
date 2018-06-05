#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "syntezer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void Play(QString fn="pulse_filt.wav");
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    ~MainWindow();
signals:
    void keyPressSig(int);
    void keyReleaseSig(int);

private slots:
    void on_sound_Settings();


    void on_tabWidget_currentChanged(QWidget *arg1);

private:
    Ui::MainWindow *ui;
    Syntezer* active_synth;
};

#endif // MAINWINDOW_H
