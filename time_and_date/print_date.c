
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int print_date( int day, int month, int year )
{

    /* lets make the assumption that the date is already
     * checked to be valid */

    /*
     *  size_t strftime(char *s, size_t max, const char *format,
     *                 const struct tm *tm);
     *
     * DESCRIPTION
     * The  strftime() function formats the broken-down time tm
     * according to the format specification format and places the
     * result in the character array s of size max.
     *   The broken-down time structure tm is defined in <time.h>.
     *
     * struct tm {
     *  int     tm_sec;         * seconds after the minute [0-60]
     *  int     tm_min;         * minutes after the hour [0-59]
     *  int     tm_hour;        * hours since midnight [0-23]
     *  int     tm_mday;        * day of the month [1-31]
     *  int     tm_mon;         * months since January [0-11]
     *  int     tm_year;        * years since 1900
     *  int     tm_wday;        * days since Sunday [0-6]
     *  int     tm_yday;        * days since January 1 [0-365]
     *  int     tm_isdst;       * Daylight Savings Time flag
     *  long    tm_gmtoff;      * offset from UTC in seconds
     *  char    *tm_zone;       * timezone abbreviation
     * };
     */

    size_t n;
    char buffer[128] = "";

    struct tm *e_time = calloc( (size_t) 1, sizeof(struct tm) );

    (*e_time).tm_year = year - 1900;
    e_time->tm_mon = month - 1;
    e_time->tm_mday = day;
    e_time->tm_isdst = -1;

    mktime(e_time);

    n = strftime( buffer, (size_t) 128, "+%Y %m %d %A %a %B %b dn=%j wd=%u wn=%V", e_time);

    printf ( "%s\n", buffer );

    free(e_time);

    return (n);

}

