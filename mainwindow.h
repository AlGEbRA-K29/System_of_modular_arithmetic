#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QAbstractListModel>
#include <QGradient>

#include "all_func.h"
#include "all_func_call.h"
#include "tests.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();


    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

 void on_lineEdit_cursorPositionChanged(int arg1, int arg2);
  void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);
    void on_lineEdit_3_cursorPositionChanged(int arg1, int arg2);

    void reset();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QString f_name;
    QString f_group;
    QLabel label;
    QLineEdit lineEdit;
    QLineEdit lineEdit_2;

    QStringList list_polynomial_field;
    QStringList list_finite_field;
    QStringList list_polynomial_ring;

};
#endif // MAINWINDOW_H
