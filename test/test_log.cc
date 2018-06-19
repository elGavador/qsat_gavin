#include <time.h>
#include <stdio.h>

void log( const char* msg_type, const char* msg )
{

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	FILE *fp;

	fp = fopen("/home/qsat/qsat/log/err.log","a");

	fprintf(fp, "%d-%d-%d    %d:%d:%d    ",
			tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, 
			19+tm.tm_hour, tm.tm_min, tm.tm_sec);

	for( int i = 0; msg_type[i] != NULL; i++ )
	{
	     fprintf(fp, "%c", msg_type[i]);
	}

	fprintf(fp, "    ");	

	for( int i = 0; msg[i] != NULL; i++ )
	{
	     fprintf(fp, "%c", msg[i]);
	}

	fprintf(fp, "\n");

	fclose(fp);

}


int main()
{
	
	log("ERR", "Message success did not return success");

	return 0;
}
