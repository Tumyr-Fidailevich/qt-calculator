#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool isOperator(QChar op)
{
     return operations.contains(op);
}

int getPriority(QChar op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

QString getLastTokenStartedFromPos(QString &str, int pos)
{
    QString token = "";
    while(pos >= 0 && str[pos].isSpace())
    {
        pos--;
    }
    while(pos >= 0 && !str[pos].isSpace())
    {
        token.prepend(str[pos]);
        pos--;
    }
    return token;
}

QString MainWindow::parseInput()
{

    return "";
}

void raiseErrorWindow()
{
    QMessageBox errorBox;
    errorBox.setIcon(QMessageBox::Critical);
    errorBox.setWindowTitle("Error");
    errorBox.setText("Divide by zero exception");
    errorBox.exec();
}

void MainWindow::addNumber(QChar number)
{
    if(_equationEvaluated)
    {
        ui->input->setText(number);
    }else
    {
        ui->input->setText(ui->input->text() + number);
    }
    _equationEvaluated = false;
}

void MainWindow::addOperation(QChar op)
{
    QString updatedInput = ui->input->text();
    QString token = getLastTokenStartedFromPos(updatedInput, updatedInput.length() - 1);
    if(!token.isEmpty())
    {
        if(isOperator(token.back()))
        {
            updatedInput[updatedInput.length() - 2] = op;
        }else
        {
            updatedInput += ' ' + op + ' ';
        }
        ui->input->setText(updatedInput);
         _isDotPlacebale = true;
        _equationEvaluated = false;
    }
}

void MainWindow::add0()
{
    addNumber('0');
}

void MainWindow::add1()
{
    addNumber('1');
}

void MainWindow::add2()
{
    addNumber('2');
}

void MainWindow::add3()
{
    addNumber('3');
}

void MainWindow::add4()
{
    addNumber('4');
}

void MainWindow::add5()
{
    addNumber('5');
}

void MainWindow::add6()
{
    addNumber('6');
}

void MainWindow::add7()
{
    addNumber('7');
}

void MainWindow::add8()
{
    addNumber('8');
}

void MainWindow::add9()
{
    addNumber('9');
}

void MainWindow::add_dot()
{
    const QString dot{'.'};
    if(_isDotPlacebale)
    {
        if(_equationEvaluated)
        {
            ui->input->setText(dot);
        }else
        {
            ui->input->setText(ui->input->text() + dot);
        }
        _isDotPlacebale = false;
        _equationEvaluated = false;
    }
}

void MainWindow::add_derivative()
{
    addOperation('/');
}

void MainWindow::add_multiplication()
{
    addOperation('*');
}

void MainWindow::add_minus()
{
    addOperation('-');
}

void MainWindow::add_plus()
{
    addOperation('+');
}

void MainWindow::deleteElement()
{
    if(!ui->input->text().isEmpty())
    {
        QString updatedInput = ui->input->text();
        int startedPos = updatedInput.length() - 1;
        QString token = getLastTokenStartedFromPos(updatedInput, startedPos);
        if(isOperator(token.back()))
        {
            token = getLastTokenStartedFromPos(updatedInput, startedPos - 3);
            updatedInput.chop(3);
        }else
        {
            updatedInput.chop(1);
        }
        _isDotPlacebale = !token.contains('.');
        ui->input->setText(updatedInput);
    }
    _equationEvaluated = false;
}

void MainWindow::deleteAll()
{
    ui->input->setText("");
    _isDotPlacebale = true;
    _equationEvaluated = false;
}

void MainWindow::evaluate()
{
    if(!ui->input->text().isEmpty())
    {
        try {
            QString answer = parseInput();
            _equationEvaluated = true;
            ui->input->setText(answer);
            _isDotPlacebale = false;
        }  catch (std::runtime_error &e) {
            ui->input->setText("");
            _isDotPlacebale = true;
            raiseErrorWindow();
        }
    }
}
