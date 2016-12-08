#include "test_source.h"

#include <QCoreApplication>
#include <QDebug>

int main(int argc,char *argv[])
{
    QCoreApplication a(argc, argv);
    TestSource testSource;

    testSource.start();

    a.exec();
    return 0;
}
