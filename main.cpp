#include <QApplication>

#include "calculator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Palculator");
    app.setApplicationDisplayName("Palculator");

    Calculator calc;
    calc.show();
    return app.exec();
}
