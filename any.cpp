#include <cstdlib>
#include <iostream>
#include <any>

int main(void){
    int i = 7;
    int *i_p = &i;

    //  void pointer + features 
    void *pointer_to_void = nullptr; 
    pointer_to_void = &i; 

	std::cout << "pointer "<< i_p << " points to " << *i_p << std::endl; 
    // void pointer with typecast to int poiter 
	std::cout << "pointer_to_void" <<  pointer_to_void  << " points to " << *((int*)pointer_to_void) <<  std::endl;   
    return 0;
}
