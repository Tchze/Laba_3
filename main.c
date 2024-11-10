#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double alpha=-200,beta=200;
double global_timer=0;

//-143.6092
double fun(double x){
    return pow(x+125,3)-45*x-18;
}

double findx_more(double x){
    return x-fun(x)/(fun(x)-fun(alpha))*(x-alpha);
}

double findx_less(double x){
    return x-fun(x)/(fun(beta)-fun(x))*(beta-x);
}

void do_nothing(int i,double x,double y){}

void print_line(int i,double x,double y){
    printf("|%10d|%20lf|%20lf|\n",i,x,y);
    for(int k=0;k<54;++k)
        printf("*");
    printf("\n");
}

int chorde(void (*pf)(int,double,double),double *x,double err,int n){
    int i=0;
    (*x)=alpha;
    double (*f)(double);
    if(fun(alpha)>0)
       f=findx_more;
    else f=findx_less;
    do{
        clock_t start_t=clock();
        ++i;
        (*x)=f(*x);
        pf(i,*x,fun(*x));
        global_timer+=(double)(clock()-start_t);
    }while(fabs(fun(*x))>err&&
                                (i<n||(!n)));
    printf("Time spent: %lf\n",global_timer);
    return i;
}

int halving(void (*pf)(int,double,double),double *x,double err,int n){
    double a=alpha,b=beta;
    int i=0;
    do{
        clock_t start_t=clock();
        ++i;
        (*x)=(a+b)/2;
        if(fun(*x)*fun(a)>0){
            a=*x;
        }else b=*x;
        pf(i,*x,fun(*x));
        global_timer+=(double)(clock()-start_t);
    }while(fabs(fun(*x))>err&&
                                (i<n||(!n)));
    printf("Time spent: %lf\n",global_timer);
    return i;
}

int main(){
    do{
        int mode;
        global_timer=0;
        int met;
        double x;
        do{
            printf("Enter mode:\n1-Find X\n2-Debug mode\n");
            scanf("%d",&mode);
        }while(mode!=1&&mode!=2);
        do{
            printf("Enter method:\n1-Chorde method\n2-Halving method\n");
            scanf("%d",&met);
        }while(met!=1&&met!=2);
        system("cls");

        if(mode==1){
            int n;
            double err;
            printf("Enter count of iterations: ");
            scanf("%d",&n);
            printf("Enter measurement error: ");
            scanf("%lf",&err);

            system("cls");
            int status=1,tn=n;
            int k=0;
            do{
                global_timer=0;
                if(met==1)
                    k=chorde(do_nothing,&x,err,tn);//
                else k=halving(do_nothing,&x,err,tn);//
                if(fabs(fun(x))>err){
                    printf("N: %d X: %lf Y: %lf\n",k,x,fun(x));
                    printf("Number of iterations is exceeded\n1-Repeat again\n2-Try to find in spite of N\nElse-end program with current result\n");
                    int t=getch();
                    printf("proceeding...");
                    system("cls");
                    if(t==49)//1
                        tn+=n;
                    else if(t==50)//2
                            status=2;
                    else status=0;
                }else{
                    status=0;
                }
            }while(status==1);
            if(status==2){
                global_timer=0;
                if(met==1)
                    k=chorde(do_nothing,&x,err,0);
                else k=halving(do_nothing,&x,err,0);
            }
            printf("N: %d X: %lf Y: %lf\n",k,x,fun(x));
        }else{
            double err;
            printf("Enter measurement error: ");
            scanf("%lf",&err);
            system("cls");
            for(int k=0;k<54;++k)
                printf("*");
            printf("\n|%10s|%20s|%20s|\n","N","X","F(X)");
            for(int k=0;k<54;++k)
                printf("*");
            printf("\n");

            global_timer=0;
            if(met==1)
                chorde(print_line,&x,err,0);
            else halving(print_line,&x,err,0);
        }
        getch();
        system("cls");
    }while(1);
    return 0;
}
