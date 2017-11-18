//Write a program for simple RSA algorithm to encrypt and decrypt the data.

#include<stdio.h>

int multi(int text,int cd,int n)
{
   	int i,rem=1;
  	for(i=1;i<=cd;i++)
  		rem=(rem*text)%n;
  	return rem;
}

int gcd(int x,int y)
{
 	 return y==0?x:gcd(y,x%y);
}

short prime(int num)
{
	int i;
	for(i=2;i<=num/2;i++)
		if(num%i==0)
			return 1;
	return 0;
}

int main()
{
	char msg[100];
	int cipher[100],i,n,d,e,p,z,len,q;
	do
	{
		printf("\nEnter two large prime nos:");
		scanf("%d%d",&p,&q);
	}while(prime(p)||prime(q));
	n=p*q;
	z=(p-1)*(q-1);
	do
	{
		printf("\nEnter prime value of e relative to %d:",z);
		scanf("%d",&e);
	}while((gcd(e,z)!=1)||e>n);
	for(d=2;d<=z;d++)
		if((e*d)%z==1)
			break;
	printf("enter the message:\n");
	len=read(0,msg,100)-1;
	
	printf("\nCiphertext:");
	for(i=0;i<len;i++)
		printf("%d",cipher[i]=multi(msg[i],e,n));
	printf("\nDecrypted ciphertext:\n");
	for(i=0;i<len;i++)
		printf("%c",multi(cipher[i],d,n));
	return 0;
}
