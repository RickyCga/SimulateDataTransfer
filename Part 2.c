#include <stdio.h>
#include <stdlib.h>

int Sensor2Data(int d);
int lengthcounter=0;

int main(int argc, char *argv[]) {
	int i, j, c;
	char Sensor1[]="Sensor1.txt";
	char Sensor2[]="Sensor2.txt";
	char Sensor3[]="Sensor3.txt";
	char Sensorcpy1[]="Sensorcpy1.txt";
	char Sensorcpy2[]="Sensorcpy2.txt";
	char Sensorcpy3[]="Sensorcpy3.txt";

	FILE *Sen1, *Sen2, *Sen3, *Sdb1, *Sdb2, *Sdb3;
	
	while(1)
	{

		Sen1=fopen(Sensor1, "r");//open Sensor1.txt
		if(Sen1)//check it exist or not
		{
			Sdb1=fopen(Sensorcpy1, "w");//copy Sensor1.txt to Sensorcpy1
			lengthcounter=0;
			while((c=getc(Sen1))!=EOF)
			{
				putc(c, Sdb1);
				lengthcounter++;//count how many word in the Sensor1.txt when program copy it
			}
			fclose(Sen1);
			remove(Sensor1);
			fclose(Sdb1);

			Sensor2Data(1);//transmit Sensorcpy1.txt to data.txt and add "#1, %1" at the same time
			remove(Sensorcpy1);
		}
		else
			fclose(Sen1);
			
		Sen2=fopen(Sensor2, "r");//equal to Sensor1
		if(Sen2)
		{
			Sdb2=fopen(Sensorcpy2, "w");
			lengthcounter=0;
			while((c=getc(Sen2))!=EOF)
			{
				putc(c, Sdb2);
				lengthcounter++;
			}
			fclose(Sen2);
			remove(Sensor2);
			fclose(Sdb2);

			Sensor2Data(2);
			remove(Sensorcpy2);
		}
		else
			fclose(Sen2);

		Sen3=fopen(Sensor3, "r");//equal to Sensor1
		if(Sen3)
		{
			Sdb3=fopen(Sensorcpy3, "w");
			lengthcounter=0;
			while((c=getc(Sen3))!=EOF)
			{
				putc(c, Sdb3);
				lengthcounter++;
			}
			fclose(Sen3);
			remove(Sensor3);
			fclose(Sdb3);

			Sensor2Data(3);
			remove(Sensorcpy3);
		}
		else
			fclose(Sen3);
	}
	return 0;
}

int Sensor2Data(int d)
{
	char DataName[]="Data.txt";
	char Sensorcpy[]="Sensorcpy.txt";
	char databuff[lengthcounter];//define a databuff with the length we counted
	int i, j, ch;
	FILE *Data, *dealdata;
	ch=d-1;
	sprintf(Sensorcpy,"Sensorcpy%d.txt",d);//change Sensorcpy[] name
	
	dealdata=fopen(Sensorcpy,"r");
	fgets(databuff, lengthcounter+1, dealdata);//transmit Sensorcpy's data to databuff

	Data=fopen(DataName, "a");
	fprintf(Data,"#%c%c", '0'+ch, '0'+lengthcounter);//write down "#(ch)" in Data.txt
	for(i=0;i<lengthcounter;i++)
		fputc(databuff[i], Data);//write down databuff in Data.txt
	fprintf(Data,"%%%c",'0'+ch);//write down "%(ch)" in Data.txt
	printf("Recieve from sensor %d\n",d);
	
	fclose(dealdata);
	fclose(Data);
}

