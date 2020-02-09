#include <stdio.h>
#include <stdlib.h>
int main() {
	FILE *fp; char c;
	fp=fopen("b.out","rb");
	int num = 0;
	printf("Magic bit is\n");
	int flag = 0;
	while((c=fgetc(fp))!=EOF){
		if(num<16)
			printf("%x",c);
		else
			break;
		num = num + 1;
		flag++;
		if(flag == 2){
			printf(" ");
			flag = 0;
		}
	}
	printf("\n");
	fclose(fp);
	return 0;
}
