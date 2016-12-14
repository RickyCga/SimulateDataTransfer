#include <stdio.h>
#include <stdlib.h>

long ticks;
int Sensorlength[3]={26,10,26};
int SensorNumber=3;//sensor number

int main(int argc, char *argv[])
{
	int i, ch, tmp;
	char filename[20]="Sensor.txt";
	int SensorLengthTracking[3]={0,0,0};
	FILE *DataCh;
	
	while(1)
	{
		ticks++;
		printf("outputing...%5ld\n", ticks);
		
		ch=SensorNumber;
		sprintf(filename, "Sensor%d.txt", ch);//change output sensor.txt to sensor(sensor number).txt
		tmp=(rand()%Sensorlength[SensorNumber-1])+1;
		DataCh=fopen(filename,"a");
		for(i=SensorLengthTracking[0]%Sensorlength[SensorNumber-1];i<((SensorLengthTracking[0]%Sensorlength[SensorNumber-1])+tmp);i++)
			fprintf(DataCh,"%c", 'a'+(i%Sensorlength[SensorNumber-1]));
	  	SensorLengthTracking[0]=i;
      	fclose(DataCh);
		Sleep(200);//sleep 200 (ms) >> 5 Hz
	}
	return 0;
}

