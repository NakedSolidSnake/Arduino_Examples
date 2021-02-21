#include "state.h"
#include "context.h"
#include "states/red_state.h"
#include <iostream>
#include <unistd.h>
#include <string>

int main(int argc, char const *argv[])
{    
    Context *context = new Context(new RedState()); 


    while(true)
    {
        context->exec();
    }
    
    return 0;
}
