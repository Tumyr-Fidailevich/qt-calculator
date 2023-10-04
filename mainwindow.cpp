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

bool isDigit(QChar c)
{
    return c == '0' || c == '1' || c == '2' ||
           c == '3' || c == '4' || c == '5' ||
           c == '6' || c == '7' || c == '8' || c == '9';
}

int getPriority(QChar op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

QString getLastTokenStartedFromPos(QString &str, int pos) noexcept
{
    QString token = "";
    if(pos > str.length() - 1 || pos < 0) return "";
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

void fixInput(QString &input)
{
    QString token = getLastTokenStartedFromPos(input, input.length() - 1);
    if(isOperator(token.back()))
    {
        input += '0';
    }
    token.clear();
    for(int i = input.length() - 1; i >= 0; i--)
    {
        if(!input[i].isSpace())
        {
            token.prepend(input[i]);
        }
        if(input[i].isSpace() || i == 0)
        {
            if(token == '.' || token == "+." || token == "-.")
            {
                input[i + (i == 0 ? 0 : 1)] = '0';
            }
            token.clear();
        }
    }
    std::cout << input.toStdString() << std::endl;
}

QString getAnswer(QString &input)
{
    fixInput(input);
    std::stack<double> values;
    std::stack<QChar> operations;

    QTextStream stream(&input);
    QString token;

    while(!stream.atEnd()){
        stream >> token;
        if(isOperator(token.back()))
        {
            while (!operations.empty() && getPriority(operations.top()) >= getPriority(token.back())) {
                QChar op = operations.top();
                operations.pop();
                double right = values.top();
                values.pop();
                double left = values.top();
                values.pop();
                if (op == '+') {
                    values.push(left + right);
                } else if (op == '-') {
                    values.push(left - right);
                } else if (op == '*') {
                    values.push(left * right);
                } else if (op == '/') {
                    if (right == 0) {
                        throw std::runtime_error("Деление на ноль!");
                    }
                    values.push(left / right);
                }
            }
            operations.push(token.back());
        }else
        {
           values.push(token.toDouble());
        }
    }
    while (!operations.empty()) {
        QChar op = operations.top();
        operations.pop();
        double right = values.top();
        values.pop();
        double left = values.top();
        values.pop();
        if (op == '+') {
            values.push(left + right);
        } else if (op == '-') {
            values.push(left - right);
        } else if (op == '*') {
            values.push(left * right);
        } else if (op == '/') {
            if (right == 0) {
                throw std::runtime_error("Деление на ноль!");
            }
            values.push(left / right);
        }
    }
    return QString::number(values.top());
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

    if(token.isEmpty() && (op == '+' || op == '-'))
    {
        updatedInput = op;
        ui->input->setText(updatedInput);
    }else if(!token.isEmpty())
    {
        if(isOperator(token.back()))
        {
            QString nextToken = getLastTokenStartedFromPos(updatedInput, updatedInput.length() - 3);
            if((nextToken.isEmpty() || isOperator(nextToken.back())) && (op == '+' || op == '-'))
            {
                updatedInput.back() = op;
            }else if(!isOperator(nextToken.back()))
            {
                if((op == '+' || op == '-'))
                {
                    updatedInput += op;
                }else
                {
                    updatedInput[updatedInput.length() - 2] = op;
                }
            }else if(token.back() != '-' && token.back() != '+'){
                updatedInput[updatedInput.length() - 2] = op;
            }
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
    QString updatedInput = ui->input->text();
    if(!updatedInput.isEmpty())
    {
        int startedPos = updatedInput.length() - 1;
        QString token = getLastTokenStartedFromPos(updatedInput, startedPos);
        if(isOperator(token.back()))
        {
            token = getLastTokenStartedFromPos(updatedInput, startedPos - 2);
            if(isOperator(token.back()) || token.isEmpty())
            {
                updatedInput.chop(1);
            }else
            {
                updatedInput.chop(3);
            }
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
    QString input = ui->input->text();
    if(!input.isEmpty())
    {
        try {
            QString answer = getAnswer(input);
            _equationEvaluated = true;
            ui->input->setText(answer);
            _isDotPlacebale = !answer.contains('.');
        }  catch (std::runtime_error &e) {
            ui->input->setText("");
            _isDotPlacebale = true;
            raiseErrorWindow();
        }
    }
}
