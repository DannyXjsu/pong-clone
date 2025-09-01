#include <stdio.h>
#include "app.h"


int main (int argc, const char **argv)
{   
    app_initialize(argc, argv);

    while(app_loop)
    {
        app_handle_events();
        app_process();
        app_render();
    }

    app_finalize();
    return 0;
}