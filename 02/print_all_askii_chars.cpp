#include<iostream>

void print_all_chars(int askii_code)
{
    union 
    {
        int iv;
        char cv;
    } cu = { .iv = askii_code};
    std::cout << cu.cv; 
}
int main() 
{
   for (std::size_t i = 32; i <= 127; i++) 
   {
      print_all_chars(i);
   }
   return 0;
}
