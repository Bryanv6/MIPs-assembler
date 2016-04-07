#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
 const char* name;
  char* code;
} registers[] = {{"$0", "00000"},
                  {"$t0", "01000"},
                  {"$t1", "01001"},
                  {"$t2", "01010"},
                  {"$t3", "01011"},
                  {"$t4", "01100"},
                  {"$t5", "01101"},
                  {"$t6", "01110"},
                  {"$t7", "01111"},
                  {"$s0", "10000"},
                  {"$s1", "10001"},
                  {"$s2", "10010"},
                  {"$s3", "10011"},
                  {"$s4", "10100"},
                  {"$s5", "10101"},
                  {"$s6", "10110"},
                  {"$s7", "10111"}
                };
struct {

  const char* name;
  const char type;

} find_type[] = {{"add", 'r'},
                  {"nor", 'r'},
                  {"sll", 'r'},
                  {"addi", 'i'},
                  {"ori", 'i'},
                  {"lui", 'i'},
                  {"sw", 'i'},
                  {"lw", 'i'},
                  {"bne", 'i'},
                  {"j", 'j'},
                  {"la", 'a'}

};

struct r_Ins{

  char* op;
  char* opcode;
  char* rs;
  char* rt;
  char* rd;
  char* shamt;
  char* funct;
};
struct la_Ins{

  char* opcode;
  char* rs;
  char* rt;
  char* immed;
  char* label;
  int address;
};

struct i_Ins{


    char* op;
    char* opcode;
    char* rs;
    char* rt;
    char* immed;
    char* label;


};

struct j_Ins{
  char* op;
  char* opcode;
  char* label;

};
struct label{

  char* name;
  int address;

};


struct{

  struct la_Ins la_;
  struct r_Ins r_;
  struct i_Ins i_;
  struct j_Ins j_;
  struct label lab;
  int memory_address;
  int space;
} memory[200];

int main(){
int o = 0;
while(o < 200)
  memory[o++].lab.name = " ";

char* types[] = {"add", "addi","nor","ori","sll","lui","sw","lw","bne","j","la"};

char word[100];
char word2[100];
int num = 0;
int i = 0;
int location = 0;
memory[num].memory_address = 0;
int check = 0;
int checkSpace = 0;
int checkWord = 0;
int count = 0;

while((scanf(" %[^\n]", word2)) != EOF){

  char* in;
  in = strtok(word2, " .\t");

  if(strcmp(in,"text") == 0){
    continue;
  }
  else if(strcmp(in,"data") == 0){
    check = 1;
  }



while(in != NULL){

  if(check == 1){

    if((strcmp(in, "space") == 0) || (checkSpace == 1)){
      if(checkSpace == 1){
        char* my_copy;
        my_copy = malloc(sizeof(char) * strlen(in));
        strcpy(my_copy,in);
        memory[num].lab.address = num*4;

        checkSpace = 0;
      }
      checkSpace = 1;

    }
   if((strcmp(in, "word") == 0) || (checkWord == 1)){
      if(checkWord == 1){
        char* my_copy;
        my_copy = malloc(sizeof(char) * strlen(in));
        strcpy(my_copy,in);
        memory[num].lab.address = num*4;
        memory[num].space = memory[num].space + memory[num].lab.address;
        checkWord = 0;
      }
      checkWord= 1;
    }

  }
  int t = 0;
  while( t < strlen(in)){
    if(in[t] == ':'){

      char* my_copy;
      my_copy = malloc(sizeof(char) * strlen(in));
      strcpy(my_copy,in);
        memory[num].lab.name = my_copy;
        memory[num].lab.address = 4*num;

        break;
    }
    t++;
  }



  in = strtok(NULL, " .\t");
}



  num++;
}
count = num;
num = 0;
location = 0;

rewind(stdin);

while((scanf(" %[^\n]", word)) != EOF){

char* in;
i = 0;
in = strtok(word," ,()\t");


int found = 0;


  while(in != NULL){
    i = 0;
    while(i < 11){
      if(strcmp(in,find_type[i].name) == 0){
          found = 1;
          break;
      }
      i++;
    }
    if(found == 1)
      break;
    in = strtok(NULL," ,()\t");
  }

if(find_type[i].type == 'r')
  memory[num].r_.opcode = find_type[i].name;
else if(find_type[i].type == 'i')
  memory[num].i_.opcode = find_type[i].name;
else if(find_type[i].type == 'j')
  memory[num].j_.opcode = find_type[i].name;
else if(find_type[i].type == 'a')
  memory[num].la_.opcode = "la";

in = strtok(NULL, " ,()");


while(in != NULL){

  if(find_type[i].type == 'r'){
    if(memory[num].r_.opcode == "sll"){
      int j = 0;
      while(j < 17){
        if(strcmp(in,registers[j].name) == 0){
            if(memory[num].r_.rd == '\0')
              memory[num].r_.rd = registers[j].code;
            else if(memory[num].r_.rt == '\0')
              memory[num].r_.rt = registers[j].code;

              break;
            }
            else if(memory[num].r_.shamt == '\0' && memory[num].r_.rd != '\0' && memory[num].r_.rt != '\0'){
              char* my_copy;
              my_copy = malloc(sizeof(char) * strlen(in));
              strcpy(my_copy,in);
              memory[num].r_.shamt = my_copy;
            }
            j++;
          }
          memory[num].r_.rs = "00000";
          memory[num].r_.op = "000000";
          memory[num].r_.funct = "000000";
    }
    else{
      int j = 0;
      while(j < 17){
        if(strcmp(in,registers[j].name) == 0){
            if(memory[num].r_.rd == '\0')
              memory[num].r_.rd = registers[j].code;
            else if(memory[num].r_.rs == '\0')
              memory[num].r_.rs = registers[j].code;
            else if(memory[num].r_.rt == '\0')
              memory[num].r_.rt = registers[j].code;

          break;
        }
        j++;
      }

        if(memory[num].r_.opcode = "add"){
          memory[num].r_.funct = "100000";
          memory[num].r_.shamt = "00000";
          memory[num].r_.op = "000000";
        }
        else{
          memory[num].r_.funct = "100111";
          memory[num].r_.op = "000000";
          memory[num].r_.shamt = "00000";
        }

    }

  }
    else if(find_type[i].type == 'i'){

      if(memory[num].i_.opcode == "lw" || memory[num].i_.opcode == "sw"){
          int j = 0;
        while( j < 17){
          if(strcmp(in,registers[j].name) == 0){
              if(memory[num].i_.rs == '\0')
                memory[num].i_.rs = registers[j].code;
              else if(memory[num].i_.rt == '\0')
                memory[num].i_.rt = registers[j].code;

              break;
            }
            else if(*in >= '0' && *in <= '9'){
              char* my_copy;
              my_copy = malloc(sizeof(char) * strlen(in));
              strcpy(my_copy,in);
              memory[num].i_.immed = my_copy;
              break;
            }
            j++;
          }

            if(memory[num].i_.opcode == "lw")
              memory[num].i_.op = "100011";
            else if(memory[num].i_.opcode == "sw")
              memory[num].i_.op = "101011";
      }
      else if(memory[num].i_.opcode == "addi" || memory[num].i_.opcode == "ori"){
        int j = 0;
        while(j < 17){
          if(strcmp(in,registers[j].name) == 0){
            if(memory[num].i_.rt == '\0')
              memory[num].i_.rt = registers[j].code;
              else if(memory[num].i_.rs == '\0')
              memory[num].i_.rs = registers[j].code;

              break;
            }
          else if((*in >= '0' && *in <= '9') || *in == '-'){
            char* my_copy;
            my_copy = malloc(sizeof(char) * strlen(in));
            strcpy(my_copy,in);
            //printf("\n%s\n", my_copy);
            memory[num].i_.immed = my_copy;
              break;
          }
          j++;

        }
        if(memory[num].i_.opcode == "addi")
          memory[num].i_.op = "001000";
        else
          memory[num].i_.op = "001101";
      }
      else if(memory[num].i_.opcode == "bne"){
        int j = 0;
        while( j < 17){
          if(strcmp(in,registers[j].name) == 0){
            if(memory[num].i_.rs == '\0')
              memory[num].i_.rs = registers[j].code;
            else if(memory[num].i_.rt == '\0')
              memory[num].i_.rt = registers[j].code;

              break;
            }
            else if(memory[num].i_.label == '\0' && memory[num].i_.rs != '\0' && memory[num].i_.rt != '\0'){
              char* my_copy;
              my_copy = malloc(sizeof(char) * strlen(in));
              strcpy(my_copy,in);
              strcat(my_copy, ":");


              memory[num].i_.label = my_copy;
              break;
            }
            j++;
          }


          memory[num].i_.op = "000101";

      }
      else if(memory[num].i_.opcode == "lui"){
        int j = 0;
        while( j < 17){
          if(strcmp(in,registers[j].name) == 0){
            if(memory[num].i_.rt == '\0')
              memory[num].i_.rt = registers[j].code;
          break;


          }
          else if(*in >= '0' && *in <= '9'){
            char* my_copy;
            my_copy = malloc(sizeof(char) * strlen(in));
            strcpy(my_copy,in);
            memory[num].i_.immed = my_copy;
            break;
          }
          j++;
        }
      memory[num].i_.op = "001111";
      }
    }
    else if(find_type[i].type == 'j'){

      if(memory[num].j_.label == '\0'){
        char* my_copy;
        my_copy = malloc(sizeof(char) * strlen(in));
        strcpy(my_copy,in);
        strcat(my_copy, ":");
        memory[num].j_.label = my_copy;

      }
    memory[num].j_.op = "000010";
    }
    else if(find_type[i].type == 'a'){
      int j = 0;
      while( j < 17){
        if(strcmp(in,registers[j].name) == 0){
          if(memory[num].i_.rt == '\0'){
            memory[num].i_.op = "001111";
            memory[num].i_.rt = registers[j].code;
            //printf("\n%d\n", num);
            memory[num].memory_address = 4*num;
            memory[num].i_.rs = "00000";
            num++;
            memory[num].la_.opcode = "la";
            memory[num].i_.rt = registers[j].code;
            memory[num].i_.rs = registers[j].code;
            memory[num].i_.op = "001101";
          }
        break;
      }
      else{
        char* my_copy;
        my_copy = malloc(sizeof(char) * strlen(in));
        strcpy(my_copy,in);
        strcat(my_copy, ":");
        //printf("\n/%s/\n", my_copy);
        memory[num].la_.label = my_copy;
      }
      j++;
      }

}


    //}

in = strtok(NULL, " ,()\t");
}

  memory[num].memory_address = 4*num;
  if(memory[num].r_.opcode != '\0' || memory[num].i_.opcode != '\0' || memory[num].j_.opcode != '\0' || memory[num].la_.opcode != '\0')
    num++;

}

int p = 0;

while(p < num){
  if(memory[p].r_.opcode != '\0'){
    char str[32];
    printf("0x%05X: ", memory[p].memory_address);
    strcpy(str, memory[p].r_.op);
    strcat(str, memory[p].r_.rs);
    strcat(str, memory[p].r_.rt);
    strcat(str, memory[p].r_.rd);
    strcat(str, memory[p].r_.shamt);
    strcat(str, memory[p].r_.funct);
    printf("0x%08X\n", strtol(str, NULL, 2));
  }
 else if(memory[p].i_.opcode != '\0'){
    if(memory[p].i_.opcode == "bne"){

      char str[16];
      printf("0x%05X: ", memory[p].memory_address);
      strcpy(str, memory[p].i_.op);
      strcat(str, memory[p].i_.rs);
      strcat(str, memory[p].i_.rt);

      printf("0x%04X", strtol(str, NULL, 2));
      int k = 0;
      while(k < num){

        if(strcmp( memory[p].i_.label, memory[k].lab.name) == 0){
          int des;
          if(memory[p].memory_address < memory[k].lab.address)
            des = memory[k].lab.address/4 - memory[p].memory_address/4;
          else
            des = memory[p].memory_address/4 - memory[k].lab.address/4;
          printf("%04X\n", des);
          break;
        }
        k++;
      }
    }
    else{
      char str[32];
      printf("0x%05X: ", memory[p].memory_address);
      strcpy(str, memory[p].i_.op);
      strcat(str, memory[p].i_.rs);
      strcat(str, memory[p].i_.rt);
      printf("0x%04X", strtol(str, NULL, 2));
      printf("%04X\n", strtol(memory[p].i_.immed, NULL, 10) & 0xffff);
}
}
  else if(memory[p].j_.opcode != '\0'){

   char str[8];
   printf("0x%05X: ", memory[p].memory_address);
   int des;
   int k = 0;
    while( k < num){

      if(strcmp( memory[p].j_.label, memory[k].lab.name) == 0){

          des = memory[k].lab.address/4;
        break;
      }
      k++;

    }

    strcpy(str, memory[p].j_.op);
    strcat(str, "00");
    printf("0x%02X%06X\n", strtol(str,NULL,2),des);

  }
  else if(memory[p].la_.opcode != '\0'){
    int des;
    int count = num;
    int k = 0;
    while(k < count){

       if(strcmp(memory[p + 1].la_.label, memory[k].lab.name) == 0){

         des = memory[k].lab.address/4 - memory[p].memory_address/4;
         break;
       }
       k++;
    }

    char str[32];
    printf("0x%05X: ", memory[p].memory_address);
    strcpy(str, memory[p].i_.op);
    strcat(str, memory[p].i_.rs);
    strcat(str, memory[p].i_.rt);
    printf("0x%04X", strtol(str, NULL, 2));
    printf("%04X\n", (des >> 8));

    char str1[32];
    printf("0x%05X: ", memory[++p].memory_address);
    strcpy(str1, memory[p].i_.op);
    strcat(str1, memory[p].i_.rs);
    strcat(str1, memory[p].i_.rt);
    printf("0x%04X", strtol(str1, NULL, 2));
    printf("%04X\n", des);

  }
  p++;
}




  return 0;
};
