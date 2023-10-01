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

void MainWindow::addNumber(char number)
{
    const QString s{number};
    if(_equationEvaluated)
    {
        ui->input->setText(s);
    }else
    {
        ui->input->setText(ui->input->text() + s);
    }
    _equationEvaluated = false;
}

void MainWindow::addOperation(char op)
{
    if(!ui->input->text().isEmpty())
    {
        if(ui->input->text().endsWith(operations))
        {
            ui->input->text().back() = op;
        }else
        {
            ui->input->setText(ui->input->text() + op);
        }
         _isDotPlacebale = true;
        _equationEvaluated = false;
    }
}

std::string MainWindow::parseInput()
{
    return "";
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
    const QString s{'.'};
    if(_isDotPlacebale)
    {
        if(_equationEvaluated)
        {
            ui->input->setText(s);
        }else
        {
            ui->input->setText(ui->input->text() + s);
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

void MainWindow::deletion()
{
    if(!ui->input->text().isEmpty())
    {
        QString updatedInput = ui->input->text();
        if(ui->input->text().endsWith(operations))
        {
            int lastOpPos = updatedInput.length() - 1;
            int secondLastOpPos = 0;
            _isDotPlacebale = true;
            for(int i = lastOpPos - 1; !operations.contains(updatedInput[i]) || i >= 0; i--)
            {
                if(updatedInput[i] == '.')
                {
                    _isDotPlacebale = false;
                    break;
                }
            }
        }else if(ui->input->text().endsWith('.'))
        {
            _isDotPlacebale = true;
        }
        updatedInput.chop(1);
        ui->input->setText(updatedInput);
    }
}

void MainWindow::evaluate()
{
    if(!ui->input->text().isEmpty())
    {
        ui->input->setText(parseInput().c_str());
        _equationEvaluated = true;
    }
}
