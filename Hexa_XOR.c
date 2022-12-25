#include<stdio.h>
#include<string.h>
//C program to evaluate XOR of two hexadecimal strings in hexadecimal format.
extern const char base[]="0123456789ABCDEF";
int index(char x)
{
    int i;
    for(i=0;i<16;i++)
    {
         if(base[i]==x)
             return i;
    }
}
char character_xor(char x,char y)
{
   return base[index(x)^index(y)];
}

int hexa_xor(char h1[100],char h2[100],int n1,int n2)
{
      int i,j,k=n2-1;
      char h[n2+1];
      i=n1-1;j=n2-1;
      h[n2]='\0';
      while(i>=0)
      {
         h[k]=character_xor(h1[i],h2[j]);
         k=k-1;
         i=i-1;
         j=j-1;
      }
    while(j>=0)
    {
      h[k]=h2[j];
      k=k-1;
      j=j-1;
    }

    for(i=0;i<n2;i++)
       printf("%c",h[i]);

    return 1;
}
int main()
{
    int a,b,i,j;
    char x[100],y[100];
    printf("Give the first hex string:");
    gets(x);
    printf("Give the second hex string:");
    gets(y);
    printf("\nThe XOR of the two hex strings is: \n");
    a=strlen(x);
    b=strlen(y);
    if(a>=b)
    {
      j=hexa_xor(y,x,b,a);
    }
    else
    {
      j=hexa_xor(x,y,a,b);
    }

    return 0;
}
