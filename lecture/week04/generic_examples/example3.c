#include<stdlib.h>
#include<stdio.h>

void *min(void *val1, void *val2, int (*fp)(void *, void *))
{
	
	
	int cmpval = fp(val1, val2);
	if(cmpval <= 0){
		return val1;
	
	}else {
		return val2;
	}



}

int stringcmp(void *s1, void *s2){

char *string1 = (char *) s1;
char *string2 = (char *) s2;

return strcmp(s2, s1);	

}

int main(void){

	char *s1 = "hello";
	char *s2 = "nihao";
	
	char *string = (char *)min(s2, s1, stringcmp);
	printf("\nmin string = %s\n", string);

	return 0;
}
