#include "pxstyneo7m.h"
_io uint8_t nmeaMsg[1024];

_io int utcTime;

_io int hours;
_io int minutes;
_io int seconds;

_io float latitudex;
_io float longitudex;

_io float speed;

_io int date;

_io int day;
_io int month;
_io int year;

_io int proccesingData(void);
_io int clearVars(void);

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
                    utcTime = atoi(buffers[1]);

                    hours = (utcTime / 10000) + 3;
                    minutes = (utcTime % 10000) / 100;
                    seconds = utcTime % 100;

                    latitudex = atof(buffers[3]) / 100.0;
                    longitudex = atof(buffers[5]) / 100.0;

                    speed = atof(buffers[7]) * 1.852 / 3600.0;

                    date = atoi(buffers[9]);

                    day = date / 10000;
                    month = (date % 10000) / 100;
                    year = date % 100;
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

_io int clearVars(void)
{
    utcTime = 0;

    hours = 0;
    minutes = 0;
    seconds = 0;

    latitudex = 0;
    longitudex = 0;

    speed = 0;

    date = 0;

    day = 0;
    month = 0;
    year = 0;

    return 1;
}

int readData(char nmea[1024])
{
    strcpy((char *)nmeaMsg, nmea);
    return proccesingData();
}

int getHours(void)
{
    return hours;
};
int getMinutes(void)
{
    return minutes;
};
int getSeconds(void)
{
    return seconds;
};

int getLatitude(void)
{
    return latitudex;
};
int getLongitude(void)
{
    return longitudex;
};

int getSpeed(int type)
{
    return speed;
};

int getDay(void)
{
    return day;
};
int getMonth(void)
{
    return month;
};
int getYear(void)
{
    return year;
};
