#include <stdio.h>
#include <stdlib.h>

#define beta 0.01
#define N 21
#define Ns 40//number of samples
#define Fs 8000//sampling frequency
#define pi 3.1415926
#define desired 2*cos(2*pi*T*100/Fs)// desired signal
#define noise sin(2*pi*T*1000/Fs) //noise signa1

int main()
{
long I,T;
double D,Y,E;

double W[N+1]={0.0};
double X[N+1]={0.0};

FILE *DESIRED,*Y_out,*error;
DESIRED=fopen("desired.txt","w++");
Y_out=fopen("Y_OUT.txt","w++");
error=fopen("ERROR.txt","w++");

for(T=0;T<Ns;T++)
{
X[0]=noise;
D=desired;
Y=0;
for(I=0;I<=N;I++)
Y+=(W[I]*X[I]);//calculate filter output;
E=D-Y;
for(I=N;I>=0;I--)
{
    W[I]=W[I]+(beta*E*X[I]);//update filter coefficients
    if(I!=0)
    X[I]=X[I-1];//update data sample

}

fprintf(DESIRED,"\n%10g  %10f",(float) T/Ns,D);
fprintf(Y_out,"\n%10g  %10f",(float) T/Fs,Y);
fprintf(error,"\n%10g %10f",(float) T/Fs,E);

}
fclose(DESIRED);
fclose(Y_out);
fclose(error);

}
