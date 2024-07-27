#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include <time.h>
#include<iostream.h>
#define T 50000
double a=5.6,b=0.01,c=3.2,d=1.2,k=1.2,a1=0.25,w1=0.16,a2=0,w2=0.16,sg,ww,I; 
double x1[1000002],x2[1000002],x3[1000002],x4[1000002],v1[1000002],v[1000002]; 
//double I=1,w1=0,D=0.1;
//double alpha=0.1,beta=0.02; 

double sgn(double x)
{
	if(x<0)
	{
		sg=-1;
	}
	if(x==0)
	{
		sg=0;
	}
	if(x>0)
	{
		sg=1;
	}
	return(sg);
}
//四阶神经网络    +0*pow(D,0.5)*W    +0.52*(a1*sgn(sin(w1*t/100)))    a1*(sin(w1*t/100)+cos(w1*t/100))
double f1(double x1,double x2,double x3,double x4,double v1,double v,double t)     
{
	return(-x1+1.2*tanh(x1)+2.7*tanh(x2)-3.7*tanh(x3)-2.2*tanh(x4)+a1*sgn(sin(w1*t/100)));  //I=0.5*(a1*sgn(sin(w1*t/100))+a2*sgn(sin(w2*t/100)))
}
double f2(double x1,double x2,double x3,double x4,double v1,double v,double t) 
{
	return(-x2-0*tanh(x1)+2.3*tanh(x2)+2.3*tanh(x3)+0*tanh(x4));
} 
double f3(double x1,double x2,double x3,double x4,double v1,double v,double t) 
{
	return(-x3+2.4*tanh(x1)-3*tanh(x2)+1.5*tanh(x3)-k*(a+b*v1)*tanh(x4));
}
double f4(double x1,double x2,double x3,double x4,double v1,double v,double t) 
{
	return(-x4+0.6*tanh(x1)+0.6*tanh(x2)+1.2*tanh(x3)+0.3*tanh(x4)+a1*sgn(sin(w1*t/100))); 	//+0.5*a1*sgn(tan(w1*t/100))
}
double f5(double x1,double x2,double x3,double x4,double v1,double v,double t) 
{
	return(c*tanh(x4)-d*(v1-sgn(v1)-sgn(v1+2)-sgn(v1-2))); //-sgn(v1) -sgn(v1)-sgn(v1+2)-sgn(v1-2)
	//return(c*tanh(x4)-d*(v1-sgn(v1)-sgn(v1+1)-sgn(v1-1))); 	
}
double f6(double x1,double x2,double x3,double x4,double v1,double v,double t) 
{
	return(c*tanh(x4)-d*(v)); 	
	//return(c*tanh(x4)-d*(v-sgn(v)-sgn(v+2)-sgn(v-2))); 	
}


main()
{
	FILE *fp1; 
	double h=0.01;
	double k11,k12,k13,k14,k21,k22,k23,k24,k31,k32,k33,k34,k41,k42,k43,k44,k51,k52,k53,k54,k61,k62,k63,k64;
	long t;
	double I1=0,I2=0,I3=0;

	if((fp1=fopen("ISI.dat","w"))==NULL) return -1;  // 在matlab中显示三维图，在commend window中加入语句plot3(hyperlorenz(:,1),hyperlorenz(:,2),hyperlorenz(:,3))
	
	for(a1=-1.5;a1<1.5;a1+=0.001)
	{
		
		I1=0,I2=0,I3=0;
		x1[0]=0.1,x2[0]=0,x3[0]=0,x4[0]=0,v1[0]=0,v[0]=0;
		
		for(t=0;t<T;t++)
		{
			k11=f1(x1[t],x2[t],x3[t],x4[t],v1[t],v[t],t);
			k21=f2(x1[t],x2[t],x3[t],x4[t],v1[t],v[t],t);
			k31=f3(x1[t],x2[t],x3[t],x4[t],v1[t],v[t],t);
			k41=f4(x1[t],x2[t],x3[t],x4[t],v1[t],v[t],t);
			k51=f5(x1[t],x2[t],x3[t],x4[t],v1[t],v[t],t);
			k61=f6(x1[t],x2[t],x3[t],x4[t],v1[t],v[t],t);
			
			k12=f1(x1[t]+h*k11/2.0,x2[t]+h*k21/2.0,x3[t]+h*k31/2.0,x4[t]+h*k41/2.0,v1[t]+h*k51/2.0,v[t]+h*k61/2.0,t);
			k22=f2(x1[t]+h*k11/2.0,x2[t]+h*k21/2.0,x3[t]+h*k31/2.0,x4[t]+h*k41/2.0,v1[t]+h*k51/2.0,v[t]+h*k61/2.0,t);
			k32=f3(x1[t]+h*k11/2.0,x2[t]+h*k21/2.0,x3[t]+h*k31/2.0,x4[t]+h*k41/2.0,v1[t]+h*k51/2.0,v[t]+h*k61/2.0,t);
			k42=f4(x1[t]+h*k11/2.0,x2[t]+h*k21/2.0,x3[t]+h*k31/2.0,x4[t]+h*k41/2.0,v1[t]+h*k51/2.0,v[t]+h*k61/2.0,t);
			k52=f5(x1[t]+h*k11/2.0,x2[t]+h*k21/2.0,x3[t]+h*k31/2.0,x4[t]+h*k41/2.0,v1[t]+h*k51/2.0,v[t]+h*k61/2.0,t);
			k62=f6(x1[t]+h*k11/2.0,x2[t]+h*k21/2.0,x3[t]+h*k31/2.0,x4[t]+h*k41/2.0,v1[t]+h*k51/2.0,v[t]+h*k61/2.0,t);
			
			k13=f1(x1[t]+h*k12/2.0,x2[t]+h*k22/2.0,x3[t]+h*k32/2.0,x4[t]+h*k42/2.0,v1[t]+h*k52/2.0,v[t]+h*k62/2.0,t);
			k23=f2(x1[t]+h*k12/2.0,x2[t]+h*k22/2.0,x3[t]+h*k32/2.0,x4[t]+h*k42/2.0,v1[t]+h*k52/2.0,v[t]+h*k62/2.0,t);
			k33=f3(x1[t]+h*k12/2.0,x2[t]+h*k22/2.0,x3[t]+h*k32/2.0,x4[t]+h*k42/2.0,v1[t]+h*k52/2.0,v[t]+h*k62/2.0,t);
			k43=f4(x1[t]+h*k12/2.0,x2[t]+h*k22/2.0,x3[t]+h*k32/2.0,x4[t]+h*k42/2.0,v1[t]+h*k52/2.0,v[t]+h*k62/2.0,t);
			k53=f5(x1[t]+h*k12/2.0,x2[t]+h*k22/2.0,x3[t]+h*k32/2.0,x4[t]+h*k42/2.0,v1[t]+h*k52/2.0,v[t]+h*k62/2.0,t);
			k63=f6(x1[t]+h*k12/2.0,x2[t]+h*k22/2.0,x3[t]+h*k32/2.0,x4[t]+h*k42/2.0,v1[t]+h*k52/2.0,v[t]+h*k62/2.0,t);
			
			k14=f1(x1[t]+h*k13,x2[t]+h*k23,x3[t]+h*k33,x4[t]+h*k43,v1[t]+h*k53,v[t]+h*k63,t);
			k24=f2(x1[t]+h*k13,x2[t]+h*k23,x3[t]+h*k33,x4[t]+h*k43,v1[t]+h*k53,v[t]+h*k63,t);
			k34=f3(x1[t]+h*k13,x2[t]+h*k23,x3[t]+h*k33,x4[t]+h*k43,v1[t]+h*k53,v[t]+h*k63,t);
			k44=f4(x1[t]+h*k13,x2[t]+h*k23,x3[t]+h*k33,x4[t]+h*k43,v1[t]+h*k53,v[t]+h*k63,t);
			k54=f5(x1[t]+h*k13,x2[t]+h*k23,x3[t]+h*k33,x4[t]+h*k43,v1[t]+h*k53,v[t]+h*k63,t);
			k64=f6(x1[t]+h*k13,x2[t]+h*k23,x3[t]+h*k33,x4[t]+h*k43,v1[t]+h*k53,v[t]+h*k63,t);
			
			x1[t+1]=x1[t]+h*(k11+2*k12+2*k13+k14)/6.0;
			x2[t+1]=x2[t]+h*(k21+2*k22+2*k23+k24)/6.0;
			x3[t+1]=x3[t]+h*(k31+2*k32+2*k33+k34)/6.0;
			x4[t+1]=x4[t]+h*(k41+2*k42+2*k43+k44)/6.0;
			v1[t+1]=v1[t]+h*(k51+2*k52+2*k53+k54)/6.0;
			v[t+1]=v[t]+h*(k61+2*k62+2*k63+k64)/6.0;
			
			if(t>2000)
			{
				//fprintf(fp1,"%16.15f %16.15f %16.15f %16.15f %16.15f\n",v1[t+1],x1[t+1],x2[t+1],x3[t+1],x4[t+1]);
				//fprintf(fp1,"%16.15f %16.15f \n",v1[t+1],x4[t+1]);
				I3=I2;
				I2=I1;
				I1=x4[t+1];
				if((I2>I1)&&(I2>I3))
				{
					fprintf(fp1,"%f %f \n",a1,x4[t+1]); 
				}
				//	fprintf(fp1,"%16.15f %16.15f\n",t*h,x1[t+1]); //%16.13f
				
				//fprintf(fp2,"%16.13f %16.13f\n",x0,z0);
			}
		}
		
	}
	
	fclose(fp1);
	return -1;
}