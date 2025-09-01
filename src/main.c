#include <stdio.h>
#include "app.h"


int main (int argc, char **argv)
{   
    app_initialize();

    while(app_loop)
    {
        app_handle_events();
        app_process();
        app_render();
    }

    app_finalize();
    return 0;
}