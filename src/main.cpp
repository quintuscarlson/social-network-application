#include "socialnetworkwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // Initialize the Qt application
    SocialNetworkWindow w;       // Create the main application window
    w.show();                    // Display the main window
    return a.exec();             // Enter the Qt event loop
}
