#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Datacpy();
int dealData();
void mydelay(int d);
char *where;
int j=0;
int lengthtracker=0;
char dataname[]="data.txt";
char datacpy[]="databackup.txt";
char ch0[]="ch0.txt";
char ch1[]="ch1.txt";
char ch2[]="ch2.txt";

int main(int argc, char *argv[])
{
	FILE *Lk, *D;
	while(1)
	{
 		sleep(1);
		D=fopen(dataname,"r");//open Data.txt and check it exist or not
		if(D)
		{
			fclose(D);

			Datacpy();//as part2.c, copy it and count the data length
			remove(dataname);
			printf("Retrieved.\n");

			printf("Dealing Data...\n");
			dealData();//separate three channel's data
			remove(datacpy);
			printf("Deal over.\n");
			sleep(5);
		}
		else
			close(D);
			
		sleep(2);
	}
	return 0;
}

int Datacpy()
{
	int c;
	FILE *fp, *Dbu;
	fp=fopen(dataname,"r");
	Dbu=fopen(datacpy,"w");
	lengthtracker=0;
	while((c=getc(fp))!=EOF)//copy from Data.txt to datacpy.txt
	{
		putc(c, Dbu);
		lengthtracker++;//count the length of data
	}
	fclose(fp);
	fclose(Dbu);
}

int dealData()
{
	int i, DL, length;
	length=lengthtracker;
	char *Nchannel, *tmp;
	char databuff[length];//define a databuff with the length we counted
	FILE *db, *c0, *c1, *c2;
	db=fopen(datacpy,"r");

	fgets(databuff, length+1, db);//transmit datacpy's data to databuff
	where=strchr(databuff,'#');//find first '#'
	
	tmp=databuff[where-databuff+2];//to know each channel's datalength
	DL=tmp-'0';
	j=0;

	while (strchr(where+2+DL+3, '#')!=NULL)
	{
		if(j!=0)//if program finded first '#', then continue. if not, then find next '#' after finded '#' + channel's datalength
			where=strchr(where+1+DL,'#');
		j++;//to know how many time we finded the '#'
		
		Nchannel=databuff[where-databuff+1];//to know the data belongs to which channel
		tmp=databuff[where-databuff+2];
		DL=tmp-'0';//DL=datalength

		if (Nchannel=='0')//check channel number
		{
			c0=fopen(ch0,"a");
			for(i=0;i<DL;i++)
			{
				fputc(databuff[where-databuff+3+i],c0);//transmit channel data from databuff to Ch0.txt
			}
			fclose(c0);
		}
		else if (Nchannel=='1')
		{
			c1=fopen(ch1,"a");
			for(i=0;i<DL;i++)
			{
				fputc(databuff[where-databuff+3+i],c1);
			}
			fclose(c1);
		}
		else if (Nchannel=='2')
		{
			c2=fopen(ch2,"a");
			for(i=0;i<DL;i++)
			{
				fputc(databuff[where-databuff+3+i],c2);
			}
			fclose(c2);
		}
	}
	fclose(db);
}
