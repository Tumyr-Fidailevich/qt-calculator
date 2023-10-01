#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const QString operations = "*/+-";
const QString numbers = "0123456789";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool _equationEvaluated = false;
    bool _isDotPlacebale = true;
    std::string parseInput();
    void addNumber(char number);
    void addOperation(char op);
public slots:
    void add0();
    void add1();
    void add2();
    void add3();
    void add4();
    void add5();
    void add6();
    void add7();
    void add8();
    void add9();
    void add_dot();
    void add_derivative();
    void add_multiplication();
    void add_minus();
    void add_plus();
    void deletion();
    void evaluate();

};
#endif // MAINWINDOW_H
