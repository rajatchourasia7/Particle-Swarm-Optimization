#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctime>
#include<iostream>
using namespace std;
/*structure of each particle*/
typedef struct {
	double a,b;
	double v_a,v_b;
	double f;
	double pbest;
	double a_star,b_star;
}particlerec,*particle;
#define w_0 0.9
#define w_t 0.4
#define nparticles 10
#define t_max 45   //no. of iteratons
#define c1 2.0
#define c2 2.0
#define better(y1,y2) y1<y2
#define v_max 2.0
double range_a(double s)      //function to control the range of a between -50 and 50
	{
	if(s<-50||s>50)
	{
		if(s<-50) s=-50;
		else if(s>50) s=50;
	}
	return s;
	}
double range_b(double r)    //function to control the range of a between -30 and 30
	{ 
	if(r<-30||r>30)
	{
		if(r<-30) r=-30;
		else if(r>70) r=30;
	}
	return r;
	}
/*sum=(a-4)^2+(b-3)^2*/
void evaluate(particle p)
{
	p->f=(p->a-4)*(p->a-4)+(p->b-3)*(p->b-3);
}
void updatebest(particle p)    //update best position of a particle
{
	p->a_star=p->a;
	p->b_star=p->b;
	p->pbest=p->f;
}
void printvalue(particle p)
	{
		cout<<p->a<<"  "<<p->b<<"  ";
		cout<<" f(g) = ";
		cout<<p->f<<" ";
	}
int initialize(particle p)
	{
		int i,j,g=0;
		srand ( time(NULL) );
		for(i=0;i<nparticles;i++)
			{	
				p[i].a=(((rand()%100))-50);
				p[i].b=(((rand()%60))-30);
				//cout<<"\n Initial values x = "<<p[i].a;
				//cout<<"\n Initial values y = "<<p[i].b<<"\n";
				//printf("\np[%d].a= %f",i,p[i].a);
				//printf("	p[%d].b= %f",i,p[i].b);
				p[i].v_a=0.0;
				p[i].v_b=0.0;
				evaluate(&p[i]);
				//sprintvalue(&p[i]);
				updatebest(&p[i]);
				if(better(p[i].f,p[g].f)) g=i;
			}
		return g;
	}
#define New(type,n) (type *)Newcell(sizeof(type),n)
particle Newcell(int size,int n)
	{	particle New1;
		if((New1=(particle)malloc(size*n))==NULL)
	{
			printf("\n Not enough memory to create %d of \n",n);
			exit(1);
	}
		return New1;
	}
particle newparticles(int n)
	{
		int i;
		particle p;
		p=New(particlerec,n);
		return p;
	}
int main()
	{
		particle p;
		p=newparticles(nparticles);
		time_t l;
		srand ( time(0) );
		cout << rand() << " " << rand() << endl;
		int g=initialize(p);
	//	cout<<"\n The best particle is  \n";
	//	cout<<" x = "<<p[g].a<<" y = "<<p[g].b<<" v_x = "<<p[g].v_a<<" v_y = "<<p[g].v_b<<"\n";
	//	cout<<"	f(g)= ";
	//	printvalue(&p[g]);
		int i,j,t;
		float w=w_0;
		for(t=0;t<t_max;t++)
		{
		for(i=0;i<nparticles;i++)
			{
				p[i].v_a=w*p[i].v_a+
						c1*(((double)(rand()%100))/100)*(p[i].a_star-p[i].a)+
						c2*(((double)(rand()%100))/100)*(p[g].a-p[i].a);
				p[i].v_b=w*p[i].v_b+
						c1*(((double)(rand()%100))/100)*(p[i].b_star-p[i].b)+
						c2*(((double)(rand()%100))/100)*(p[g].b-p[i].b);
						/*printf("%f  ",((double)((rand()%10))));*/
						if(p[i].v_a<-v_max)
						p[i].v_a=-v_max;
						else if(p[i].v_a>v_max)
						p[i].v_a=v_max;
						p[i].a+=p[i].v_a;
						
						if(p[i].v_b<-v_max)
						p[i].v_b=-v_max;
						else if(p[i].v_b>v_max)
						p[i].v_b=v_max;
						p[i].b+=p[i].v_b;
						p[i].a=range_a(p[i].a);	
						p[i].b=range_b(p[i].b);
					/*	*/
						
				evaluate(&p[i]);
			//	cout<<"  f(g)=";
			//	printvalue(&p[i]);
				if(better(p[i].f,p[i].pbest))
					{
						if(better(p[i].f,p[g].f)) g=i;
						updatebest(&p[i]);
						//cout<<"		"<<g<<"		";
						//printvalue(&p[i]);
						//cout<<" ";
					}
					}
					//cout<<"\n The best particle is  "<<g<<"\n";
					//cout<<" x = "<<p[g].a<<" y = "<<p[g].b<<" v_x = "<<p[g].v_a<<" v_y = "<<p[g].v_b<<"\n";
									//cout<<"(x,y)"<<p[i].a<<","<<p[i].b<<"  ";
									
					
	
					printvalue(&p[g]);
					//cout<<"\n w = "<<w;
					cout<<"\nNext iteraion\n";
					w-=(w_0-w_t)/t_max;
				}
		return 0;
	}
