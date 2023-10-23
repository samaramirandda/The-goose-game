char *truncate(char *str, int chars)
{
    int strLength = strlen(str);

    if (strLength > chars)
    {
        int truncatedLength = chars - 3;
        char *truncatedStr = (char *)malloc((truncatedLength + 4) * sizeof(char));

        strncpy(truncatedStr, str, truncatedLength);
        truncatedStr[truncatedLength] = '.';
        truncatedStr[truncatedLength + 1] = '.';
        truncatedStr[truncatedLength + 2] = '.';
        truncatedStr[truncatedLength + 3] = '\0';

        return truncatedStr;
    }
    else
    {
        return strdup(str);
    }
}

void getCurrentDate(char* buffer, size_t bufferSize)
{
    time_t t = time(NULL);
    struct tm* timeinfo = localtime(&t);

    int day = timeinfo->tm_mday;
    int month = timeinfo->tm_mon + 1;
    int year = timeinfo->tm_year + 1900;

    snprintf(buffer, bufferSize, "%02d-%02d-%04d", day, month, year);
}

void getCurrentTime(int* hour, int* minute)
{
    time_t t = time(NULL);
    struct tm* timeinfo = localtime(&t);

    *hour = timeinfo->tm_hour;
    *minute = timeinfo->tm_min;
}

int compareDates(char *date1, char *date2)
{
    int day1, month1, year1;
    int day2, month2, year2;

    sscanf(date1, "%d-%d-%d", &day1, &month1, &year1);
    sscanf(date2, "%d-%d-%d", &day2, &month2, &year2);

    if (year1 < year2)
        return -1;
    else if (year1 > year2)
        return 1;

    if (month1 < month2)
        return -1;
    else if (month1 > month2)
        return 1;

    if (day1 < day2)
        return -1;
    else if (day1 > day2)
        return 1;

    return 0;
}

void toString(char str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int toInt(char str[])
{
    int len = strlen(str);
    int i, num = 0;

    for (i = 0; i < len; i++)
    {
        num = num + ((str[len - (i + 1)] - '0') * pow(10, i));
    }

    return num;
}