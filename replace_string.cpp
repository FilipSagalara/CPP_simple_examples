#include <iostream>
#include <stdio.h>


using namespace std;

int main()
{
    char zdanko[] = "ala ma niesamowita ochote na sens";
    char slowo[] = "sens";
    char zamian[] = "keks";
    int dlugoscZdanka = sizeof(zdanko) / sizeof(char) - 1;
    int dlugoscSlowa = sizeof(slowo) / sizeof(char) - 1;
    for (int i = 0 ; i < dlugoscZdanka; i++)
    {
        bool zamieniansko = false;
        if(zdanko[i]==slowo[0]) //zgodzila sie pierwsza litera
        {
            zamieniansko = true;
            for(int j = i; j< i+ dlugoscSlowa; j++)
            {
                if(zdanko[j]!=slowo[j-i])
                {
                    zamieniansko = false;
                }
            }
            if(zamieniansko == true)
            {
                for(int j = i; j<i+dlugoscSlowa; j++)
                {
                    zdanko[j] = zamian[j-i];
                }
            }
        }


    }


    std::cout << zdanko;
    return 0;

}
