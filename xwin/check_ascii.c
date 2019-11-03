

/* not used anywhere at the moment */

int check_ascii_input(char *inp)
{
    /* ensure that the width and height are at least 512 pixels */
    char *buf = calloc((size_t)32, sizeof(unsigned char));
    int char_cnt, retval;

    retval = (int)strtol( inp, (char **)NULL, 10);
    char_cnt = snprintf(buf, (size_t)32, "%i", retval);
    /* did we get at least a single valid digit ? */
    if ( char_cnt < 1 ) {
        retval = -1;
    } else {
        /* compare the input string to the integer conversion */
        if ( strncmp( inp, buf, char_cnt) != 0 ){
            retval = -1;
        } else {
            /* ensure that we have at least 512 pixels */
            if ( retval < 512 ) retval = 512;
        }
    }
    free(buf);
    return retval;
}

