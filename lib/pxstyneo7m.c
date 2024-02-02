#include <neo7m.h>
_io uint8_t nmeaMsg[1024];

_io int utcTimex;

_io int hoursx;
_io int minutesx;
_io int secondsx;

_io float latitudex;
_io float longitudex;

_io float speedx;

_io int datex;

_io int dayx;
_io int monthx;
_io int yearx;

_io int proccesingData(void);
// _io int clearVars(void);

_io int proccesingData(void)
{
    const char *startTag = "$GPRMC";
    const char *endlTag = "\r\n";
    int status = 200;

    char *startPtr = strstr((char *)nmeaMsg, startTag);
    if (startPtr == NULL)
        status = 1;
    else
    {
        while (startPtr != NULL)
        {
            char *endlPtr = strstr(startPtr, endlTag);

            if (endlPtr != NULL)
            {
                // clearVars();

                size_t lineLength = endlPtr - startPtr;
                char line[lineLength + 1];
                strncpy(line, startPtr, lineLength);
                line[lineLength] = '\0';

                char *buffers[20];

                char *buffer = strtok(line, ",");
                int tokenIndex = 0;
                while (buffer != NULL)
                {
                    buffers[tokenIndex++] = buffer;
                    buffer = strtok(NULL, ",");
                }
                if (tokenIndex == 10)
                {
                    utcTimex = atoi(buffers[1]);

                    hoursx = ((utcTimex / 10000) + 3) % 24;
                    minutesx = (utcTimex % 10000) / 100;
                    secondsx = utcTimex % 100;

                    latitudex = atof(buffers[3]) / 100.0;
                    longitudex = atof(buffers[5]) / 100.0;

                    speedx = atof(buffers[7]) * 1.852 / 3600.0;

                    datex = atoi(buffers[8]);

                    if (hoursx <= 2)
                        dayx = (datex / 10000) + 1;
                    else
                        dayx = datex / 10000;

                    monthx = (datex % 10000) / 100;
                    yearx = (datex % 100) + 2000;
                }
                else
                    status = 1;
            }
            else
            {
                break;
            }

            startPtr = strstr(endlPtr, startTag);
        }
    }

    return status;
}
/*
_io int clearVars(void)
{
    utcTimex = 0;

    hoursx = 0;
    minutesx = 0;
    secondsx = 0;

    latitudex = 0;
    longitudex = 0;

    speedx = 0;

    datex = 0;

    dayx = 0;
    monthx = 0;
    yearx = 0;

    return 1;
}
*/
int readData(char nmea[1024])
{
    strcpy((char *)nmeaMsg, nmea);
    return proccesingData();
}

int getHours(void)
{
    return hoursx;
};
int getMinutes(void)
{
    return minutesx;
};
int getSeconds(void)
{
    return secondsx;
};

float getLatitude(void)
{
    return latitudex;
};
float getLongitude(void)
{
    return longitudex;
};

int getSpeed(int type)
{
    return speedx;
};

int getDay(void)
{
    return dayx;
};
int getMonth(void)
{
    return monthx;
};
int getYear(void)
{
    return yearx;
};
