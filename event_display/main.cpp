#include "C_mainwindow.h"
#include <QApplication>
#include <getopt.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    C_MainWindow w;
    w.show();

   int events = 10000;
    int c;
    while(1)
    {
        static struct option long_options[] = {
            { 0, 0, 0, 0 }
        };

        int option_index = 0;

        c = getopt_long(argc, argv, "", long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {
            default:
                break;
        }
    }

    while (optind < argc)
    {
        std::cout << "Display " << argv[optind] << std::endl;
        w.openFile(argv[optind]);
        break;
    }

    return app.exec();
}
