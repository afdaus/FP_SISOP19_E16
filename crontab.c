#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <pthread.h>
void ambil_waktu();
void ambil_perintah();
void konversi();
void proses();
void test();
void kosonginstruct();
void ngecek();
void *hit_waktu(void *arg);
void test_print();
void isistruct();
void ambil_file();
void buatwhile();
char car[10];
char hasil[200];
int i=0,urut=0;
int asli=1;
pthread_t tid[10];
char loc[]="/home/bastian/fp/crontab.data";
time_t waktu_lama;

struct config
{
    int angka[5];
    char perintah[300];
};

struct config con[10];

void ambil_waktu()
{
  int hit=0;
  FILE* filenya;
  filenya = fopen("crontab.data","r");
  while(!feof(filenya))
  {
      int *arg = malloc(sizeof(*arg));
      memset(con[urut].angka, 0, sizeof(con[urut].angka)*8);
      fgets(hasil,100,filenya);
      while(hasil[i]!='\0' && hit!=5)
      {
          car[i] = hasil[i];
          if(hasil[i]==' ')
          {
              hit++;
          }
          i++;
      }
      konversi();
      ambil_perintah();
      *arg = urut;
      pthread_create(&tid[urut],NULL,hit_waktu,arg);
      urut++;
      i=0;
      hit=0;
  }
  fclose(filenya);
  buatwhile();
}

void buatwhile()
{
  while(1)
  {
    ngecek();
      if(asli==0)
      {      
        urut=0;
        asli=1;
        memset(con, 0, sizeof(con));
        break;
      }
    sleep(1);
  }
  ambil_waktu();
}

void konversi()
{
  char nol = '0';
  int j=0,l=0;
  while(car[j]!='\0')
  {
      if(car[j]!='*' && car[j]!=' ' && car[j+1]!='\0')
      {
          if(car[j]!='*' && car[j+1]!=' ' && car[j+1]!='*') //ini buat ngecek angka 2 digit
          {
              con[urut].angka[l] = (car[j] - nol)*10 + (car[j+1]-nol);
              l++;    
          }
          else if(car[j+1]==' ' && car[j-1]==' ') //ngecek angka 1 digit
          {
              con[urut].angka[l] = car[j] - nol;
              l++;
          }
      }
      else if(car[j]=='*')
      {
          //buat bintang
          con[urut].angka[l]=61;
          l++;
      }
      j++;    
  }
}

void proses(int urut)
{
  int k=0,t=0;
  pid_t pr1= fork();
  if(pr1==0)
  {
      execl("/bin/bash","bash","-c",con[urut].perintah,NULL);
  }
}

void ambil_perintah()
{
  int k=0;
  int pos=i;
  char sement[300];
  while(hasil[pos]!='\0')
  {
      sement[k] = hasil[pos];
      k++;
      pos++;
  }
  strtok(sement,"\n");
  strcpy(con[urut].perintah,sement);
}

void *hit_waktu(void *arg)
{
  int temp = *((int *) arg);
  while(1)
  {
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      if (asli==0)
          {break;}
      if((con[temp].angka[0]==tm.tm_min || con[temp].angka[0]==61) && (con[temp].angka[1]==tm.tm_hour || con[temp].angka[1]==61) && (con[temp].angka[3]==tm.tm_mon+1 || con[temp].angka[3]==61) &&((con[temp].angka[2]==tm.tm_mday || con[temp].angka[2]==61) || (con[temp].angka[4]==tm.tm_wday || con[temp].angka[4]==61)))
      {
         proses(temp);
          sleep(60);
      }
      sleep(1);
  }
}

void ngecek()
{
   char filename[] = "crontab.data";
   char timeStr[ 100 ] = "";
   struct stat buf;
   time_t ltime;
   char datebuf [9];
   char timebuf [9];
   if (!stat(filename, &buf))
   {
    strftime(timeStr, 100, "%d-%m-%Y %H:%M:%S", localtime( &buf.st_mtime));
   }
   time(&ltime);
   if(difftime(ltime ,buf.st_mtime ) <= 1)
   {
      asli=0;
      sleep(2);
   }
   else
   {
      asli=1;
   }
}

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  ambil_waktu();

  exit(EXIT_SUCCESS);
}
