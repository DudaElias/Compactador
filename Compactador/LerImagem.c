#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *p;
  char str[80],c;
  printf("\n\n Entre com um nome para o arquivo:\n");
  scanf("%s", &str);
  p = fopen(str,"r");
  while (!feof(p))
  {
           fscanf(p,"%c",&c);
           printf("%c",c);
  }
  fclose(p);
    return 0;
}
