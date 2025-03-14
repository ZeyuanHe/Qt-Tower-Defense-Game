#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QLabel>
#include "gamescene.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QLabel *goldLabel;
    static void updateGoldDisplay();
    QGraphicsView *view;

private:
    GameScene *scene;
};

#endif // MAINWINDOW_H
