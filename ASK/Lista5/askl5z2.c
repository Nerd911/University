long puzzLe2(char *s, char *d){
  char* a = s;
  do{
    char* temp1 = a + 1;
    char temp2 = *(temp1 - 1);
    char temp3;
    char* b = d;

    do{
      ++b;
      temp3 = *(b - 1);

      if(temp3 == 0)
        return (long)(a - d);
    }while(temp3 != temp2);
    a = temp1;
  }while(true);
}
