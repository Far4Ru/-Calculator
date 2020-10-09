#include <QtWidgets>
#include <cmath>

#include "button.h"
#include "calculator.h"
#include "factorial.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;

    display = new QLineEdit("0");

    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    for (int i = 0; i < NumDigitButtons; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }

    Button *eButton = createButton(tr("e"), SLOT(epiClicked()));
    Button *piButton = createButton(tr("\317\200"), SLOT(epiClicked()));

    Button *pointButton = createButton(tr("."), SLOT(pointClicked()));
    Button *changeSignButton = createButton(tr("\302\261"), SLOT(changeSignClicked()));

    Button *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
    Button *clearButton = createButton(tr("C"), SLOT(clear()));
    Button *clearAllButton = createButton(tr("AC"), SLOT(clearAll()));

    Button *clearMemoryButton = createButton(tr("MC"), SLOT(clearMemory()));
    Button *readMemoryButton = createButton(tr("MR"), SLOT(readMemory()));
    Button *setMemoryButton = createButton(tr("MS"), SLOT(setMemory()));
    Button *addToMemoryButton = createButton(tr("M+"), SLOT(addToMemory()));

    Button *divisionButton = createButton(tr("\303\267"), SLOT(multiplicativeOperatorClicked()));
    Button *timesButton = createButton(tr("\303\227"), SLOT(multiplicativeOperatorClicked()));
    Button *logButton = createButton(tr("log"), SLOT(multiplicativeOperatorClicked()));
    Button *eeButton = createButton(tr("EE"), SLOT(multiplicativeOperatorClicked()));
    Button *degreeButton = createButton(tr("x\312\270"), SLOT(multiplicativeOperatorClicked()));
    Button *modButton = createButton(tr("Ост /"), SLOT(multiplicativeOperatorClicked()));
    Button *intButton = createButton(tr("Цел /"), SLOT(multiplicativeOperatorClicked()));
    Button *rootButton = createButton(tr("\312\270\342\210\232x"), SLOT(multiplicativeOperatorClicked()));
    Button *minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
    Button *plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));

    Button *lnButton = createButton(tr("ln"), SLOT(unaryOperatorClicked()));
    Button *log10Button = createButton(tr("log10"), SLOT(unaryOperatorClicked()));
    Button *squareRootButton = createButton(tr("\342\210\232x"), SLOT(unaryOperatorClicked()));
    Button *cubeRootButton = createButton(tr("\342\210\233x"), SLOT(unaryOperatorClicked()));
    Button *power2Button = createButton(tr("x\302\262"), SLOT(unaryOperatorClicked()));
    Button *power3Button = createButton(tr("x\302\263"), SLOT(unaryOperatorClicked()));
    Button *reciprocalButton = createButton(tr("1/x"), SLOT(unaryOperatorClicked()));
    Button *factorialButton = createButton(tr("x!"), SLOT(unaryOperatorClicked()));
    Button *sinButton = createButton(tr("sin"), SLOT(unaryOperatorClicked()));
    Button *cosButton = createButton(tr("cos"), SLOT(unaryOperatorClicked()));
    Button *tgButton = createButton(tr("tg"), SLOT(unaryOperatorClicked()));
    Button *ctgButton = createButton(tr("ctg"), SLOT(unaryOperatorClicked()));
    Button *tenxButton = createButton(tr("10\313\243"), SLOT(unaryOperatorClicked()));
    Button *exButton = createButton(tr("e\313\243"), SLOT(unaryOperatorClicked()));
    Button *arcsinButton = createButton(tr("arcsin"), SLOT(unaryOperatorClicked()));
    Button *arccosButton = createButton(tr("arccos"), SLOT(unaryOperatorClicked()));
    Button *arctgButton = createButton(tr("arctg"), SLOT(unaryOperatorClicked()));
    Button *arcctgButton = createButton(tr("arcctg"), SLOT(unaryOperatorClicked()));
    Button *shButton = createButton(tr("sh"), SLOT(unaryOperatorClicked()));
    Button *chButton = createButton(tr("ch"), SLOT(unaryOperatorClicked()));
    Button *thButton = createButton(tr("th"), SLOT(unaryOperatorClicked()));
    Button *cthButton = createButton(tr("cth"), SLOT(unaryOperatorClicked()));
    Button *equalButton = createButton(tr("="), SLOT(equalClicked()));

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 5);
    mainLayout->addWidget(backspaceButton, 1, 3, 1, 2);
    mainLayout->addWidget(clearButton, 1, 0);
    mainLayout->addWidget(clearAllButton, 2, 0);

    mainLayout->addWidget(clearMemoryButton, 3, 0);
    mainLayout->addWidget(readMemoryButton, 4, 0);
    mainLayout->addWidget(setMemoryButton, 5, 0);
    mainLayout->addWidget(addToMemoryButton, 6, 0);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 3;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 6, 1, 1, 2);
    mainLayout->addWidget(pointButton, 6, 3);
    mainLayout->addWidget(changeSignButton, 2, 1);

    mainLayout->addWidget(divisionButton, 2, 2);
    mainLayout->addWidget(timesButton, 2, 3);
    mainLayout->addWidget(minusButton, 2, 4);
    mainLayout->addWidget(plusButton, 3, 4, 2, 1);
    mainLayout->addWidget(equalButton, 5, 4, 2, 1);

    mainLayout->addWidget(squareRootButton, 3, 5);
    mainLayout->addWidget(cubeRootButton, 3, 6);
    mainLayout->addWidget(rootButton, 3, 7);

    mainLayout->addWidget(power2Button, 4, 5);
    mainLayout->addWidget(power3Button, 4, 6);
    mainLayout->addWidget(degreeButton, 4, 7);

    mainLayout->addWidget(logButton, 5, 5);
    mainLayout->addWidget(lnButton, 5, 6);
    mainLayout->addWidget(log10Button, 5, 7);

    mainLayout->addWidget(factorialButton, 6, 5);
    mainLayout->addWidget(exButton, 6, 6);
    mainLayout->addWidget(tenxButton, 6, 7);
    mainLayout->addWidget(eeButton, 6, 8);
    mainLayout->addWidget(reciprocalButton, 6, 9);

    mainLayout->addWidget(eButton, 1, 2);
    mainLayout->addWidget(piButton, 1, 1);

    mainLayout->addWidget(sinButton, 2, 5);
    mainLayout->addWidget(cosButton, 2, 6);
    mainLayout->addWidget(tgButton, 2, 7);
    mainLayout->addWidget(ctgButton, 2, 8);

    mainLayout->addWidget(arcsinButton, 3, 8);
    mainLayout->addWidget(arccosButton, 4, 8);
    mainLayout->addWidget(arctgButton, 5, 8);
    mainLayout->addWidget(arcctgButton, 1, 9);

    mainLayout->addWidget(shButton, 3, 9);
    mainLayout->addWidget(chButton, 4, 9);
    mainLayout->addWidget(thButton, 5, 9);
    mainLayout->addWidget(cthButton, 2, 9);

    mainLayout->addWidget(modButton, 1, 7, 1, 2);
    mainLayout->addWidget(intButton, 1, 5, 1, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));
}

void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}

void Calculator::unaryOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("\342\210\232x")) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } if (clickedOperator == tr("\342\210\233x")) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::pow(operand,1/3);
    } else if (clickedOperator == tr("x\302\263")) {
        result = std::pow(operand, 3.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    } else if (clickedOperator == tr("sin")) {
        result = std::sin(operand);
    } else if (clickedOperator == tr("cos")) {
        result = std::cos(operand);
    } else if (clickedOperator == tr("tg")) {
        result = std::tan(operand);
    } else if (clickedOperator == tr("ctg")) {
        result = 1/(std::tan(operand));
    } else if (clickedOperator == tr("ln")) {
        result = std::log(operand);
    } else if (clickedOperator == tr("log10")) {
        result = std::log(operand)/std::log(10);
    } else if (clickedOperator == tr("x!")) {
        result = factorial(operand);
    } else if (clickedOperator == tr("e\313\243")) {
        result = std::pow(M_E, operand);
    } else if (clickedOperator == tr("10\313\243")) {
        result = std::pow(10, operand);
    } else if (clickedOperator == tr("arcsin")) {
        result = std::asin(operand);
    } else if (clickedOperator == tr("arccos")) {
        result = std::acos(operand);
    } else if (clickedOperator == tr("arctg")) {
        result = std::atan(operand);
    } else if (clickedOperator == tr("arcctg")) {
        result = 1/(std::atan(operand));
    } else if (clickedOperator == tr("sh")) {
        result = std::sinh(operand);
    } else if (clickedOperator == tr("ch")) {
        result = std::cosh(operand);
    } else if (clickedOperator == tr("th")) {
        result = std::tanh(operand);
    } else if (clickedOperator == tr("cth")) {
        result = 1/(std::tanh(operand));
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}

void Calculator::additiveOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}

void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}

void Calculator::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void Calculator::clear()
{
    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

void Calculator::clearMemory()
{
    sumInMemory = 0.0;
}

void Calculator::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void Calculator::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void Calculator::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
}

Button *Calculator::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("Ошибка"));
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    } else if (pendingOperator == tr("x\312\270")) {
        factorSoFar = std::pow(factorSoFar, rightOperand);
    } else if (pendingOperator == tr("Цел /")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
        factorSoFar = (int)factorSoFar;
    } else if (pendingOperator == tr("Ост /")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar = fmod(factorSoFar, rightOperand);
    } else if (pendingOperator == tr("EE")) {
        factorSoFar *= std::pow(10, rightOperand);
    } else if (pendingOperator == tr("log")) {
        factorSoFar = std::log(factorSoFar)/std::log(rightOperand);
    } else if (pendingOperator == tr("\312\270\342\210\232x")) {
        factorSoFar = std::pow(factorSoFar, 1/rightOperand);
    }
    return true;
}

void Calculator::epiClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double epiValue = clickedButton->text().toDouble();

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    if (clickedOperator == tr("e")) {
        display->clear();
        epiValue = M_E;
    } else if (clickedOperator == tr("\317\200")) {
        display->clear();
        epiValue = M_PI;
    }
    display->setText(display->text() + QString::number(epiValue));
}
