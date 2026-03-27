#include "mainwindow.h"

#include <QWidget>
#include <QVBoxLayout> 
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QStatusBar>
#include <QMessageBox>
#include <qstack.h>
#include <qstring.h>
#include <qchar.h>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setupUI();
    setFixedSize(400, 600);
    statusBar()->showMessage("Ready!");
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget* central = new QWidget;
    setCentralWidget(central);

    EditCal = new QLineEdit;
    Result = new QLabel("0");

    EditCal->setAlignment(Qt::AlignRight);
    Result->setAlignment(Qt::AlignRight);

    EditCal->setMinimumHeight(100);
    Result->setMinimumHeight(30);

    //btn
    btn0 = new QPushButton("0");
    btn1 = new QPushButton("1");
    btn2 = new QPushButton("2");
    btn3 = new QPushButton("3");
    btn4 = new QPushButton("4");
    btn5 = new QPushButton("5");
    btn6 = new QPushButton("6");
    btn7 = new QPushButton("7");
    btn8 = new QPushButton("8");
    btn9 = new QPushButton("9");

    additionBtn = new QPushButton("+");
    subtractionBtn = new QPushButton("−");  
    multiplicationBtn = new QPushButton("×");
    divisionBtn = new QPushButton("÷");

    roundBracketopen = new QPushButton("(");
    roundBracketclose = new QPushButton(")");

    dotBtn = new QPushButton(".");

    calculatorBtn = new QPushButton("=");
    deleteBtn = new QPushButton("C");
    delete1Btn = new QPushButton("CE");

    // rải signal slot lên nút click
    auto connectBtn = [&](QPushButton* btn)
        {
            connect(btn, &QPushButton::clicked, this, [=]() {
                appendText(btn->text());
                });
        };

    //connect 
    connectBtn(btn0);
    connectBtn(btn1);
    connectBtn(btn2);
    connectBtn(btn3);
    connectBtn(btn4);
    connectBtn(btn5);
    connectBtn(btn6);
    connectBtn(btn7);
    connectBtn(btn8);
    connectBtn(btn9);

    connectBtn(additionBtn);
    connectBtn(subtractionBtn);
    connectBtn(multiplicationBtn);
    connectBtn(divisionBtn);

    connectBtn(dotBtn);
    connectBtn(roundBracketopen);
    connectBtn(roundBracketclose);

    calculatorBtn->setObjectName("equalBtn");
    deleteBtn->setObjectName("deleteBtn");
    delete1Btn->setObjectName("delete1Btn");

    central->setStyleSheet(
        "QWidget { background-color: #121212; }"

        "QLineEdit {"
        "  font-size: 18px;"
        "  padding: 8px;"
        "  background: #2d2d2d;"
        "  color: white;"
        "  border-radius: 8px;"
        "}"

        "QLabel {"
        "  font-size: 28px;"
        "  font-weight: bold;"
        "  background: black;"
        "  color: white;"
        "  padding: 10px;"
        "  border-radius: 8px;"
        "}"

        "QPushButton {"
        "  font-size: 18px;"
        "  min-width: 70px;"
        "  min-height: 70px;"
        "  border-radius: 10px;"
        "  background-color: #333;"
        "  color: white;"
        "}"

        "QPushButton:hover { background-color: #555; }"
        "QPushButton:pressed { background-color: #222; }"

        //nút
        "QPushButton#equalBtn {"
        "  background-color: #2196F3;"
        "  color: white;"
        "}"
        "QPushButton#equalBtn:hover { background-color: #1976D2; }"
        "QPushButton#equalBtn:pressed { background-color: #0D47A1; }"

        //nút
        "QPushButton#deleteBtn {"
        "  background-color: #e53935;"
        "  color: white;"
        "}"
        "QPushButton#deleteBtn:hover { background-color: #c62828; }"
        "QPushButton#deleteBtn:pressed { background-color: #b71c1c; }"

        //nút
        "QPushButton#delete1Btn {"
        "  background-color: #FFB74D;"   
        "  color: black;"
        "}"
        "QPushButton#delete1Btn:hover { background-color: #FFA726; }"
        "QPushButton#delete1Btn:pressed { background-color: #FB8C00; }"
    );


    //connect
    connect(calculatorBtn, &QPushButton::clicked, this, &MainWindow::calculator);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteCalculator);
    connect(delete1Btn, &QPushButton::clicked, this, &MainWindow::deleteOneChar);

    QVBoxLayout* displayLayout = new QVBoxLayout;

    displayLayout->addWidget(EditCal);
    displayLayout->addWidget(Result);

    //btn layout 
    QGridLayout* grid = new QGridLayout;
    grid->addWidget(additionBtn,0,0);
    grid->addWidget(subtractionBtn, 0, 1);
    grid->addWidget(multiplicationBtn, 0, 2);
    grid->addWidget(divisionBtn, 0, 3);

    grid->addWidget(btn7, 1, 0);
    grid->addWidget(btn8, 1, 1);
    grid->addWidget(btn9, 1, 2);
    grid->addWidget(deleteBtn, 1, 3);

    grid->addWidget(btn4, 2, 0);
    grid->addWidget(btn5, 2, 1);
    grid->addWidget(btn6, 2, 2);
    grid->addWidget(delete1Btn, 2, 3);

    grid->addWidget(btn1, 3, 0);
    grid->addWidget(btn2, 3, 1);
    grid->addWidget(btn3, 3, 2);
    grid->addWidget(roundBracketclose, 3, 3);

    grid->addWidget(btn0, 4, 1);
    grid->addWidget(roundBracketopen, 4, 2);

    grid->addWidget(calculatorBtn, 4, 3);
    grid->addWidget(dotBtn, 4, 0);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(displayLayout);
    mainLayout->addLayout(grid);

    central->setLayout(mainLayout);
}


int compareOperator(QChar op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
double MainWindow::CalcPair(double a, double b, QChar c)
{
    if (c == '+') return a + b;
    if (c == '-') return a - b;
    if (c == '*') return a * b;
    if (c == '/')
    {
        if (b == 0)
        {
            QMessageBox::warning(this, "Fail", "Cannot divide by 0");
            return 0;
        }
        return a / b;
    }
    return 0;
}
void MainWindow::calculator()
{
    QString s = EditCal->text();

    QStack<double> v;
    QStack<QChar> ops;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ') continue;

        if ((s[i] >= '0' && s[i] <= '9') ||
            (s[i] == '-' && (i == 0 || s[i - 1] == '(')))
        {
            bool isNegative = false;

            if (s[i] == '-')
            {
                isNegative = true;
                i++;
            }

            double val = 0;

            while (i < s.length() && s[i] >= '0' && s[i] <= '9')
            {
                val = val * 10 + s[i].digitValue();
                i++;
            }

            if (i < s.length() && s[i] == '.')
            {
                i++;
                double frac = 0, base = 0.1;

                while (i < s.length() && s[i] >= '0' && s[i] <= '9')
                {
                    frac += s[i].digitValue() * base;
                    base *= 0.1;
                    i++;
                }

                val += frac;
            }

            if (isNegative) val = -val;

            v.push(val);
            i--;
        }

        else if (s[i] == '(')
        {
            ops.push(s[i]);
        }

        else if (s[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                if (v.size() < 2)
                {
                    QMessageBox::warning(this, "Error", "Invalid expression");
                    return;
                }

                double b = v.top(); v.pop();
                double a = v.top(); v.pop();
                QChar op = ops.top(); ops.pop();

                v.push(CalcPair(a, b, op));
            }

            if (!ops.empty()) ops.pop(); // bỏ ngoặc
        }

        else // operator
        {
            while (!ops.empty() &&
                compareOperator(ops.top()) >= compareOperator(s[i]))
            {
                if (v.size() < 2)
                {
                    QMessageBox::warning(this, "Error", "Invalid expression");
                    return;
                }

                double b = v.top(); v.pop();
                double a = v.top(); v.pop();
                QChar op = ops.top(); ops.pop();

                v.push(CalcPair(a, b, op));
            }

            ops.push(s[i]);
        }
    }

    while (!ops.empty())
    {
        if (v.size() < 2)
        {
            QMessageBox::warning(this, "Error", "Invalid expression");
            return;
        }

        double b = v.top(); v.pop();
        double a = v.top(); v.pop();
        QChar op = ops.top(); ops.pop();

        v.push(CalcPair(a, b, op));
    }

    if (!v.empty())
        Result->setText(QString::number(v.top(), 'g', 10));
}

//delete
void MainWindow::deleteCalculator()
{
    EditCal->clear();
    Result->setText("0");
}

//delete 1 char
void MainWindow::deleteOneChar()
{
    QString text = EditCal->text();

    if (!text.isEmpty())
    {
        text.chop(1); // xóa 1 ký tự cuối
        EditCal->setText(text);
    }
}


void MainWindow::appendText(QString val)
{
    QString current = EditCal->text();

    // convert UI -> logic
    if (val == "×") val = "*";
    if (val == "÷") val = "/";
    if (val == "−") val = "-";

    EditCal->setText(current + val);
}


