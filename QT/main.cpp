#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton btn("Qt Test OK");
    btn.resize(300, 120);
    btn.show();

    return app.exec();
}
