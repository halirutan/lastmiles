
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <string.h>
#include <strings.h>
#include <locale.h>
#include <math.h>
#include <gmp.h>
#include <mpfr.h>

#define PREC 113 /* similar to IEEE 754-2008 128-bit type */

int main (int argc, char *argv[])
{
    int inex; /* mpfr retval */
    long bit_prec = PREC;
    long delta_bit_prec;
    mpfr_prec_t actual_prec; /* see _MPFR_PREC_FORMAT */
    char *endptr, *str;

    /* buffer to compare what we receive to what was actually input */
    char *buf;
    int chars_formatted;
    int input_attempt_loop = 0;

    mpfr_t input_m;

    /* only function with for the C or POSIX class. */
    if ( setlocale( LC_ALL, "POSIX" ) == NULL ) {
        fprintf(stderr,"FAIL : could not set LC_ALL=\"POSIX\"\n");
        return (EXIT_FAILURE);
    }

    /* only function with for the C or POSIX class. */
    if ( setlocale( LC_CTYPE, "POSIX" ) == NULL ) {
        fprintf(stderr,"FAIL : could not set LC_CTYPE=\"POSIX\"\n");
        return (EXIT_FAILURE);
    }

    /* check if a test integer was on the command line */
    if (argc<2){
        fprintf(stderr,"FAIL : test number and optional bit precision?\n");
        fprintf(stderr,"     : %s <integer> <bit precision>\n", argv[0]);
        fprintf(stderr,"     : default bit precision is %i\n\n", PREC);
        return (EXIT_FAILURE);
    }

    /* check if a bit precision parameter was on the command line */
    if (argc>2){
        errno = 0; /* To distinguish success/failure after call */
        str = argv[2];
        bit_prec = strtol(str, &endptr, 10);

        if ( ( (errno == ERANGE)
               &&
               ( (bit_prec == LONG_MAX)
                 || 
                 (bit_prec == LONG_MIN)
               ) )
             || (errno != 0 && bit_prec == 0)) {
            perror("FAIL : strtol could not parse bit precision.");
            exit(EXIT_FAILURE);
        }

        if (endptr == str) {
            fprintf(stderr, "No bit precision seen.\n");
            exit(EXIT_FAILURE);
        }

        if (*endptr != '\0'){ /* Not necessarily an error... */
            fprintf(stderr,"INFO : Further characters after bit");
            fprintf(stderr," precision ignored : %s\n", endptr);
        }

        if (bit_prec>1023){
            bit_prec = 1024;
            printf("WARN : limit precision to 1024 bits.\n");
        }

    } else {
        bit_prec = PREC;
    }
    delta_bit_prec = bit_prec / 2;
    printf("INFO : We shall attempt %i bits of precision.\n", bit_prec);
    mpfr_set_default_prec((mpfr_prec_t)bit_prec);
    mpfr_init2 (input_m, (mpfr_prec_t) bit_prec);

input_try:
    if (argc>1){
        /* int mpfr_set_str(mpfr_t rop, const char *s, int base, mpfr_rnd_t rnd)
         *
         *   Set rop to the value of the string s in base base, rounded
         *   in the direction rnd. See the documentation of mpfr_strtofr
         *   for a detailed description of the valid string formats.
         *   Contrary to mpfr_strtofr, mpfr_set_str requires the whole
         *   string to represent a valid floating-point number.
         *
         *   The meaning of the return value differs from other MPFR
         *   functions: it is 0 if the entire string up to the final null
         *   character is a valid number in base base;
         *   otherwise it is -1, and rop may have changed (users interested
         *   in the ternary value should use mpfr_strtofr instead).    */
        if (input_attempt_loop>0) {
            printf("INFO : we shall attempt to read input again.\n");
        }
        inex = mpfr_set_str(input_m, argv[1], 10, MPFR_RNDN);
        if ( inex < 0 ) {
            printf("FAIL : some mysterious problem happened!\n");
            printf("     : we tried to interpret %s\n", argv[1]);
            printf("     : however we seemed to get ");
            mpfr_printf("%.Rf\n", input_m);
            return (EXIT_FAILURE);
        }

        if (mpfr_number_p(input_m)==0){
            fprintf(stderr,"FAIL : provide a reasonable decimal number.\n");
            return (EXIT_FAILURE);
        }

    } else {
        fprintf(stderr,"FAIL : provide a nice base ten number!\n");
        fprintf(stderr,"     : %s <some number> <bit precision>\n", argv[0]);
        return (EXIT_FAILURE);
    }

    if (input_attempt_loop<1) {
        printf("     : You seem to have entered %s\n", argv[1]);
        printf("     : Where mpfr_set_str() seems to see ");
        mpfr_printf("%.Rf\n", input_m);
    }

    /* int mpfr_snprintf (char *buf, size_t n, const char *template, …)
     *
     *    Form a null-terminated string corresponding to the optional
     *    arguments under the control of the template string template,
     *    and print it in buf. If n is zero, nothing is written and buf
     *    may be a null pointer, otherwise, the n-1 first characters
     *    are written in buf and the n-th is a null character. Return
     *    the number of characters that would have been written had n
     *    been sufficiently large, not counting the terminating null
     *    character, or a negative value if an error occurred. 
     */

    /* buffer big enough for the string plus a trailing null */
    buf = calloc((size_t)(strlen(argv[1])+1), (size_t)sizeof(unsigned char));
    chars_formatted = mpfr_snprintf(buf,(size_t)(strlen(argv[1])+1),"%.Rf\n", input_m);
    if (chars_formatted < 0 ){
        fprintf(stderr,"FAIL : mpfr_snprintf tossed an error.\n");
        return (EXIT_FAILURE);
    }

    printf("INFO : chars_formatted = %i\n", chars_formatted);
    printf("INFO : buf = \'%s\'\n", buf);

    if ( strcasecmp( argv[1], buf) == 0 ){
        printf("INFO : perfect match on data input.\n");
    }else{
        fprintf(stderr,"WARN : incorrect data on input.\n");
        fprintf(stderr,"     : this is most likely caused by ");
        fprintf(stderr,"insufficient bits\n     : of precision to ");
        fprintf(stderr,"represent the data correctly.\n");
        /* gradually increase the precision */
        bit_prec = bit_prec + delta_bit_prec;
        mpfr_set_default_prec((mpfr_prec_t)bit_prec);
        /* make input variable wider */
        mpfr_set_prec(input_m,(mpfr_prec_t)bit_prec);
        actual_prec=mpfr_get_default_prec();
        printf("INFO : Input variable re-initialized with");
        printf(" %i bits of precision.\n", (int)actual_prec);
        free(buf);
        buf = NULL;
        input_attempt_loop += 1;
        goto input_try;
    }

    free(buf);
    buf = NULL;
    mpfr_clear(input_m);
    return (EXIT_SUCCESS);

}

