
/*
 *
 * 31  29  31  30 31  30  31 31 30 31 30 31   ^C
 * beta $    (mon%1 ? (mon < 7 ? 31 , 30) , (mon >= 7 ? 30 , 31))   ^C
 *
 * Any year that is evenly divisible by 4 is a leap year
 *
 * However, there is still a small error that must be 
 * accounted for. To eliminate this error, the Gregorian
 * calendar stipulates that a year that is evenly divisible
 * by 100 (for example, 1900) is a leap year only if it
 * is also evenly divisible by 400.
 *
 */

int valid_date ( int day, int month, int year )
{

    int days_in_month[12] = { 31, 28, 31, 30, 31, 30,
                              31, 31, 30, 31, 30, 31 };

    /* check for bad data */
    if ( ( day < 1 ) || ( day > 31 ) )
        return ( -1 );

    if ( ( month < 1 ) || ( month > 12 ) )
        return ( -1 );

    if ( ( year < 1800 ) || ( year > 2037 ) )
        return ( -1 );


    /* we need to check for leap year */
    if ( month == 2 )
        if ( ( ( year%4 == 0 ) && ( ( year%100 ) > 0 ) ) || ( year%400 == 0 ) )
            days_in_month[1] = 29;

    if ( day > days_in_month[month-1] )
        return ( 0 );


    return ( 1 );

}

