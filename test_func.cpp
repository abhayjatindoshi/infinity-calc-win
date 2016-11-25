#include "test_func.h"
#include "ui_test_func.h"
#include "dashboard.h"
#include "sources/INT.h"
#include <qDebug>

test_func::test_func(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test_func)
{
    ui->setupUi(this);
    //[14-11-2016] To disable window resize and maximise button
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    //[24-11-2016] move to the next box when tab key pressed
    ui->value1->setTabChangesFocus(true);
    ui->value2->setTabChangesFocus(true);
}

test_func::~test_func()
{
    delete ui;
}

void test_func::on_back_clicked()
{
    //[15-11-2016] links the back button to dashboard
    dashboard *dash = new dashboard();
    this->close();
    dash->show();
}

void test_func::on_add_clicked()
{
    //[22-11-2016] hits google server with event
    ga.hit_event("Test Func","add");
    INT num1,num2;
    QString solution;
    //[18-11-2016] tries to process two strings that are specified
    try{
        num1= ui->value1->toPlainText().toStdString();
        num2= ui->value2->toPlainText().toStdString();
        solution = QString::fromStdString((num1+num2).to_string());
        ui->digits->setText("No. of digits:"+QString::number(solution[0] == '-' ? solution.length()-1 : solution.length()));
    //[19-11-2016] added exception for wrong errors
    }catch(exception& e){
        solution = e.what();
        ui->digits->setText("");
    }
    //[18-11-2016] sets the result to text
    ui->result->setText(solution);
}

void test_func::on_subtract_clicked()
{
    //[22-11-2016] hits google server with event
    ga.hit_event("Test Func","subtract");
    INT num1,num2;
    QString solution;
    //[18-11-2016] tries to process two strings that are specified
    try{
        num1= ui->value1->toPlainText().toStdString();
        num2= ui->value2->toPlainText().toStdString();
        solution = QString::fromStdString((num1-num2).to_string());
        ui->digits->setText("No. of digits:"+QString::number(solution[0] == '-' ? solution.length()-1 : solution.length()));
    //[19-11-2016] added exception for wrong errors
    }catch(exception& e){
        solution = e.what();
        ui->digits->setText("");
    }
    //[18-11-2016] sets the result to text
    ui->result->setText(solution);
}

void test_func::on_multiply_clicked()
{
    //[22-11-2016] hits google server with event
    ga.hit_event("Test Func","multiply");
    INT num1,num2;
    QString solution;
    //[18-11-2016] tries to process two strings that are specified
    try{
        num1= ui->value1->toPlainText().toStdString();
        num2= ui->value2->toPlainText().toStdString();
        solution = QString::fromStdString((num1*num2).to_string());
        ui->digits->setText("No. of digits:"+QString::number(solution[0] == '-' ? solution.length()-1 : solution.length()));
    //[19-11-2016] added exception for wrong errors
    }catch(exception& e){
        solution = e.what();
        ui->digits->setText("");
    }
    //[18-11-2016] sets the result to text
    ui->result->setText(solution);
}

void test_func::on_divide_clicked()
{
    //[22-11-2016] hits google server with event
    ga.hit_event("Test Func","divide");
    INT num1,num2;
    QString solution;
    //[18-11-2016] tries to process two strings that are specified
    try{
        num1= ui->value1->toPlainText().toStdString();
        num2= ui->value2->toPlainText().toStdString();
        solution = QString::fromStdString((num1/num2).to_string());
        ui->digits->setText("No. of digits:"+QString::number(solution[0] == '-' ? solution.length()-1 : solution.length()));
    //[19-11-2016] added exception for wrong errors
    }catch(exception& e){
        solution = e.what();
        ui->digits->setText("");
    }
    //[18-11-2016] sets the result to text
    ui->result->setText(solution);
}

void test_func::on_mod_clicked()
{
    //[22-11-2016] hits google server with event
    ga.hit_event("Test Func","mod");
    INT num1,num2;
    QString solution;
    //[18-11-2016] tries to process two strings that are specified
    try{
        num1= ui->value1->toPlainText().toStdString();
        num2= ui->value2->toPlainText().toStdString();
        solution = QString::fromStdString((num1%num2).to_string());
        //[25-11-2016] to display the number of digits of the output
        ui->digits->setText("No. of digits:"+QString::number(solution[0] == '-' ? solution.length()-1 : solution.length()));
    //[19-11-2016] added exception for wrong errors
    }catch(exception& e){
        solution = e.what();
        //[25-11-2016] set blank for digits of invalid output
        ui->digits->setText("");
    }
    //[18-11-2016] sets the result to text
    ui->result->setText(solution);
}
