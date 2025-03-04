// Determine whether three values represent the sides of a right triangle.
#include <iostream>
using namespace std; 

int main()
{
   int side1; // length of side 1
   int side2; // length of side 2
   int side3; // length of side 3
   int t;

   // get values of three sides
   cout << "Enter side 1: ";
   cin >> side1;

   cout << "Enter side 2: ";
   cin >> side2;

   cout << "Enter side 3: ";
   cin >> side3;
   
   if(side1>side2)
   {
       t=side1; side1=side2; side2=t;
   }
   
   if(side1>side3)
   {
       t=side1; side1=side3; side3=t;
   }
   
   if(side2>side3)
   {
       t=side2; side2=side3; side3=t;
   }
   
   if(side1*side1+side2*side2==side3*side3)
   {
       cout<<"These are the sides of a right triangle."<<endl;
   }
   else
   {
       cout<<"These do not form a right triangle."<<endl;
   }
   system( "pause" );
} // end main
