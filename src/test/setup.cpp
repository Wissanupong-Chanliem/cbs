#include "../modules/setup/setup.h"

int main(){
    setup::ProjectCreator creator = setup::ProjectCreator("abc");
    creator.create();
    return 0;
}