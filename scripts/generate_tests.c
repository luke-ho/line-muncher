#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_LENGTH 8192

typedef struct _tests {
    char * filename;
    unsigned long long start_range;
    unsigned long long end_range;
} Tests;

static Tests tests[] = {
    {"../tests/1.txt", 1, 32}, // correct answer should be: 53 characters
    {"../tests/2.txt", 0, 100}, // correct answer should be: 191 characters
    {"../tests/3.txt", 0, 9999},
    //{"../tests/4.txt", 0, 9999 * 9999},
    //{"../tests/5.txt", 0, ~0},
    {"INVALID", 0, 0}, // THIS MUST BE THE LAST ENTRY
};

static unsigned char buffer[MAX_BUFFER_LENGTH];
static FILE * fp;

static unsigned long long get_num_digits(unsigned long long num) {
    unsigned long long ret = 1;
    while((num = num / 10) > 0)
        ret++;

    return ret;
}

static unsigned long long get_digit_at_location(unsigned long long num, unsigned long long digit, unsigned long long num_digits) 
{
    while ( num_digits != digit ) {
        num /= 10;
        num_digits--;
    }
    return num % 10;
}

static unsigned long long num_chars(unsigned long long start_range, unsigned long long end_range) {
    unsigned long long range = end_range;
    unsigned long long num_digits; 
    unsigned long long ret_val = 0;
    unsigned long long i = 0;
    unsigned char done = 0;
    unsigned long long next_decrease;
    
    printf("====== start:%llu, end:%llu =====\n", start_range, end_range);
    while (!done) {
        num_digits = get_num_digits(range);
        printf("num_digits(%llu), range(%llu)\n", num_digits, range);
        next_decrease = 1;
        for (i = 0; i < num_digits - 2 && num_digits > 1; ++i) {
            next_decrease *= 10; 
            next_decrease += 1;
        }
        if (num_digits > 1) {
            next_decrease *= 9;
        } else {
            next_decrease = 0;
        }
        if (next_decrease < start_range) {
            next_decrease = start_range;
        }
        printf("next_decrease(%llu), increase(%llu), range(%llu), num_digits(%llu)\n", next_decrease, ((range - next_decrease) * num_digits), range, num_digits);
        ret_val += ((range - next_decrease) * (num_digits));
        if ( next_decrease == start_range ) {
            ret_val--;
            break;
        }
        range = next_decrease;
    }
    printf("range(%llu, %llu):%llu\n", start_range, end_range, ret_val);
    return ret_val;
}

static char get_char_from_digit(unsigned char digit) 
{
    // TODO: Could update this to subtract by ASCII offset, but for now just be explicit.
    switch(digit)
    {
        case 0:
            return '0';
            break;
        case 1:
            return '1';
            break;
        case 2:
            return '2';
            break;
        case 3:
            return '3';
            break;
        case 4:
            return '4';
            break;
        case 5:
            return '5';
            break;
        case 6:
            return '6';
            break;
        case 7:
            return '7';
            break;
        case 8:
            return '8';
            break;
        case 9:
            return '9';
            break;
        default:
            return '\0';
            break;
    }   
}   

static void dump_to_file(unsigned char * buffer, unsigned long long * num, unsigned int * loc) 
{
    if (!buffer) return;
    if (!num) return;
    if (!loc) return;

    static unsigned long long num_digits;
    static unsigned long long i;
    static unsigned char digit;

    num_digits = get_num_digits(*num);

    // Can this whole number fit in the buffer?
    if ((*loc) + num_digits > MAX_BUFFER_LENGTH) {
        // flush out the whole buffer and reset loc
        //printf("Flushing buffer(%d): %s\n", *loc, buffer);
        fwrite(buffer, 1, *loc, fp);
        *loc = 0;
    }

    if ( num_digits == 1 ) {
        digit = get_digit_at_location(*num, 1, num_digits);
        //printf("\tDigit: %d =====\n", digit);
        buffer[(*loc)++] = get_char_from_digit(digit);
    } else {
        //printf("===== Num: %llu =====\n", *num);
        for ( i = num_digits; i > 0; i-- ) {
            digit = get_digit_at_location(*num, i, num_digits);
	    buffer[(*loc + i - 1)] = get_char_from_digit(digit);
        }
        *loc += num_digits;
    }
}

static void write_to_file(unsigned long long begin, unsigned long long end) 
{
    if ( begin > end ) { 
        printf("(%s) begin:%llu, end:%llu\n", __FUNCTION__, begin, end);
        return; 
    } 
    unsigned int i = 0;
    do {
        // Write to the buffer
        dump_to_file(buffer, &begin, &i); 
        begin++;
    } while ( begin != end + 1 );
    if (i) {
        // dump it out
        fwrite(buffer, 1, i, fp);
    }
}

int main() {
    unsigned int i;
    for ( i = 0 ; strcmp(tests[i].filename, "INVALID") != 0 ; ++i) {
        fp = fopen(tests[i].filename, "w");
        if ( !fp ) {
            fprintf(stderr, "Error while trying to open %s\n", tests[i].filename);
        }   
        printf("===== start:%llu, end:%llu =====\n", tests[i].start_range, tests[i].end_range);
        write_to_file(tests[i].start_range, tests[i].end_range);
        fclose(fp);
    }
    return 0;
}
