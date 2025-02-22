#include "quick_calc.h"
#include "ui_quick_calc.h"
#include "dashboard.h"
#include <chrono>
#include "INT.h"

quick_calc::quick_calc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::quick_calc)
{
    ui->setupUi(this);
    //[14-11-2016] To disable window resize and maximise button
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    //[24-11-2016] makes the box not to acept tab keys
    ui->expression->setTabChangesFocus(true);
}

quick_calc::~quick_calc()
{
    delete ui;
}

void quick_calc::on_back_clicked()
{
    //[15-11-2016] connects back button to dashboard
    dashboard *dash = new dashboard();
    this->close();
    dash->show();
}

void quick_calc::on_expression_textChanged()
{
    //[15-11-2016] updates the result box for every key pressed
    QString solution = "Invalid expression";
    //[19-11-2016] gets the expression as a string
    string exp = ui->expression->toPlainText().toStdString();
    //[19-11-2016] checks and parses the expression and returns the solution
    if(INT::check_expression(exp)){
        try{
            //[27-11-2016] starts the timer
            auto start = chrono::steady_clock::now();
            solution = solution.fromStdString(INT::parse(exp).to_string());
            //[27-11-2016] stops the timer
            auto end = chrono::steady_clock::now();
            //[27-11-2016] displays the time consumed
            ui->time->setText("Time: "+QString::number(chrono::duration<double, milli>(end-start).count())+"ms");
            //[25-11-2016] to set the number of digits of output
            ui->digits->setText("No. of digits: "+QString::number(solution[0] == '-' ? solution.length()-1 : solution.length()));
        }catch(exception &e){
            solution = e.what();
            //[25-11-2016] set blank for digits and time of invalid output
            ui->digits->setText("");
            ui->time->setText("");
        }
    }
    else{
        //[25-11-2016] set blank for digits and time of invalid output
        ui->digits->setText("");
        ui->time->setText("");
    }
    //[15-11-2016] sets the result box with a string
    ui->result->setText(solution);
}
