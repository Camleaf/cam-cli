#include <iostream>
#include <stateManager.h>
#include <extLoad.h>


int query_pass(string name, bool flag_add, bool flag_del){
    

    if (flag_add){
        
    } else if (flag_del){

    }
    
    return 0;
}


int add_pass(string name){
    
}

int get_pass(string name){

}


int delete_pass(string name){
    if (!pass_exists_disk(name)){
        cout << "Password `" << name << "` does not exist in local passwords";
        return 1;
    }
    
    


    return 0;
}
