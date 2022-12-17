#include<stdio.h>
#include<string.h>
//C Program to evaluate base64 encoding of a hexadecimal string and print it.
char Base64[68];
int binary(char s)
{
    char c=s;
    switch(c)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    }
}

char* hex_base(char x)
{
    char c=x;
    switch(c)
    {
    case '0':
        return "0000";
    case '1':
        return "0001";
    case '2':
        return "0010";
    case '3':
        return "0011";
    case '4':
        return "0100";
    case '5':
        return "0101";
    case '6':
        return "0110";
    case '7':
        return "0111";
    case '8':
        return "1000";
    case '9':
        return "1001";
    case 'A':
        return "1010";
    case 'B':
        return "1011";
    case 'C':
        return "1100";
    case 'D':
        return "1101";
    case 'E':
        return "1110";
    case 'F':
        return "1111";
    }
}
char* Hex_to_Binary(char h[100])
{
    char b[410],*p;
    int n,i,j=0,k;
    n=strlen(h);
    for(i=0;i<n;i++)
    {
        p=hex_base(h[i]);
        for(k=0;k<4;k++)
        {
            b[j]=*(p+k);
            j=j+1;
        }
    }
    b[j]='\0';
    return b;
}
int hex_to_base64(char input[100])
{
    char b[410];
    strcpy(Base64,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
    strcpy(b,Hex_to_Binary(input));
    int n,i=0,index=0,j,k,s,p;
    n=strlen(b);
    k=n%6;
    if(k==2)
    {
        b[n]=b[n+1]=b[n+2]=b[n+3]='0';
        k=2;
        n=n+4;
    }
    else if(k==4)
    {
        b[n]=b[n+1]='0';
        k=1;
        n=n+2;
    }

    while(i<n)
    {
        j=i+5;s=0;p=1;
        while(j>=i)
        {
            s=s+binary(b[j])*p;
            p=2*p;
            j=j-1;
        }
        printf("%c",Base64[s]);
        i=i+6;
    }
    if(k==1)
    {
        printf("=");
    }
    else if(k==2)
    {
        printf("==");
    }

    return 1;
}
int main()
{
    char input[100];int i;
    printf("Give the hex string to encode it to Base64:");
    gets(input);
    printf("\nThe corresponding binary string:%s",Hex_to_Binary(input));
    printf("\n Base64 encoded :");
    i=hex_to_base64(input);
    return 3;
}
