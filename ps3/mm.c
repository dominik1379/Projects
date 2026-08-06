#include <stdio.h>

int main()
{
    int sucet = 0;
    int c;
    while(1)
    {
        c = getchar();
        if(c < '0' || c > '9')
            break;
        sucet += c - '0';
    }
    
    while(sucet > 9)
    {
        int N;
        N = sucet;
        sucet = 0;
        int r;
        
        while (N != 0) //uklada cisla do polia
		{
			r = N % 10;
			sucet += r; 
			N = N / 10;
		}		
    }
		printf("%d\n", sucet);
    
return 0;
}
