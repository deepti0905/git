#include <iostream>
using namespace std;

void permute ( string str, int start, int end)
{
 if(start == end)
 {
	 cout<<endl<<str.c_str();
	 return;
 }
 else
 {
	 for(int i=start; i<=end; i++)
	 {
		 char temp = str[start];
		 str[start]=str[i];
		 str[i]=temp;


		 permute(str, start+1, end);

		 temp = str[start];
		 str[start]=str[i];
		 str[i]=temp;
	 }
 }


}

int main()
{
	string arr= "abc";
	permute(arr,0,2);
	getchar();
}
