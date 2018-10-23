#include <stdlib.h>
#include <stdio.h>

int square(int x) { 
	return x*x;
}

int timesTwo(int x) {
	return x*2;
}

double addGST( double val, int rate){
	double valPlusGST = val * (100.0 + rate)/100.0; 
	return valPlusGST;
}

int main(int argc, char *argv[])
{
	
	
	int (*fp)(int);
	fp = square;
	
	int n = (*fp)(10);
	printf("%d\n", n);
	
	
	fp = timesTwo;
	
	n = (*fp)(2);
	printf("%d\n", n);
	
	double (*fp2)(double, int);
	
	fp2 = addGST;
	
	n = (*fp2)(125, 10);
	printf("%d\n", n);
	

	
	
	/*	
	int (*fp)(int);    // declare fp as a point to function 

	fp = square;      //fp points to the square function

	int n = (*fp)(10); //call the square function with input 10

	printf(">> n (after calling function square) %d \n", n);

	fp = timesTwo;     //works without the &
					    //fp points to the timesTwo function

	n = (*fp)(2);      //call the timesTwo function with input 2
	printf(">> n (after calling function timesTwo) %d \n", n);

	n = fp(2);         //can also use normal function call
				        //notation 
	printf(">> n (after calling fp(2)) %d \n", n);

	double (*fpGST) (double, int); 

	fpGST = addGST;
	double val2 = fpGST(125, 10);
	printf(">> val2 is %.2f \n", val2);

*/

	return EXIT_SUCCESS;
}
#include<stdio.h>
#define N 5
#define M 3
struct stu
{
	char name[20];
	int num[16];
	float score[M];
	float aver;
}
student [N];

void sort(struct stu student[]);
void writefile(struct stu student[],char filename[],char mode[]);
int main()
{
    FILE *fp;
	struct stu *ptr=NULL;
	int i,j;
	printf("input data:\n");
	for(i=0;i<N;i++)
	{
        scanf("%s %s",student[i].name,student[i].num);
		student[i].aver=0;
		for(j=0;j<M;j++)
		{
            scanf("%f",&student[i].score[j]);
			student[i].aver += student[i].score[j];
		}
	}
    writetofile(student,"student.txt","w");
    writetofile(student,"sort.txt","w");
    writetofile(student,"sort2.txt","w");
    sort(student);
    writetofile(student,"sort.txt","a");
    ptr=(struct stu *)malloc(sizeof(struct stu));
    scanf("%s %s",ptr->name,ptr->num);
    ptr->aver=0;
    for( j=0;j<M;j++)
    {
        scanf("%f",&ptr->score[j]);
	    ptr->aver += ptr->score[j];
    }
    if ((fp=fopen("sort2.txt","a"))==NULL)
    {
        printf("cannot open file");
	    exit(0);
    }
    fprintf(fp,"%s %s",ptr->name,ptr->num);
    for( j=0;j<M;j++)
    fprintf(fp,"%7.2f",ptr->score[j]);
    fprintf(fp,"%7.2\n",ptr->aver/M);
	fclose(fp);
	return 0;
}
void sort (struct stu student[])
{
    struct stu temp;
	int i,j,k;
	for(i=0;i<N-1;i++)
	{
        k=i;
		for(j=i+1;j<N;j++)
		    if(student[j].aver < student[k].aver)
			k=j;
		if(k!=j)
		{
            temp=student[i];
			student[i]=student[k];
			student[k]=temp;
		}
	}
}
void Writetofile(struct stu student[],char filename[],char mode[])
{
    FILE *fp;
	int i,j;
	if((fp=fopen(filename,mode))==NULL)
	{
        fprintf(fp,"%s %s",student[i].name,student[i].num);
		for(j=0;j<M;j++)
		  fprintf(fp,"%7.2f",student[i].score[j]);
		fprintf(fp,"%7.2f\n",student[i].aver/M);
	}
	fclose(fp);
}

