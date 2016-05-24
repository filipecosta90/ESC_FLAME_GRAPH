//
// Naive matrix multiplication
//

//
// Author:  P.J. Drongowski
// Date:    10 June 2013
//
// Copyright (c) 2013 Paul J. Drongowski
//

#include <stdlib.h>
#include <stdio.h>
/* 
#include "../test_common/test_common.h"
#include "../test_common/rpi_pmu.h"

*/
FILE* result_file = NULL ;

#define RESULT_FILE_NAME  "naive.txt"

#define MAX_MSIZE 1000
#define MSIZE     500
int matrix_size = MSIZE ;

float matrix_a[MSIZE][MSIZE] ;
float matrix_b[MSIZE][MSIZE] ;
float matrix_r[MSIZE][MSIZE] ;

//
// Run options (some not implemented)
//
int c_flag = 0 ;    // Measure cache behavior
int i_flag = 0 ;    // Measure IPC
int m_flag = 0 ;    // Set matrix size to N
int t_flag = 0 ;    // Measure TLB behavior

#define OPTIONS "cdhim:tv"  // Currently unimplemented (getopt)

char *usage_strings[] = {
	"  -c    Measure cache behavior",
	"  -d    Display debugging information",
	"  -h    Display usage information",
	"  -i    Measure IPC",
	"  -m N  Set the matrix dimensions to N elements",
	"  -t    Measure TLB behavior",
	"  -v    Display more information (verbose output)",
	NULL
} ;

int create_result_file(char* filename)
{
	if ((result_file = fopen(filename, "w")) == NULL) {
		fprintf(stderr, "Couldn't open result file\n") ;
		return( 0 ) ;
	}
	return( 1 ) ;
}

void initialize_matrices()
{
	int i, j ;

	for (i = 0 ; i < MSIZE ; i++) {
		for (j = 0 ; j < MSIZE ; j++) {
			matrix_a[i][j] = (float) rand() / RAND_MAX ;
			matrix_b[i][j] = (float) rand() / RAND_MAX ;
			matrix_r[i][j] = 0.0 ;
		}
	}
}

void multiply_matrices()
{
	int i, j, k ;

	for (i = 0 ; i < MSIZE ; i++) {
		for (j = 0 ; j < MSIZE ; j++) {
			float sum = 0.0 ;
			for (k = 0 ; k < MSIZE ; k++) {
				sum = sum + (matrix_a[i][k] * matrix_b[k][j]) ;
			}
			matrix_r[i][j] = sum ;
		}
	}
}


void run_no_events()
{
	initialize_matrices() ;
	multiply_matrices() ;
}

int main(int argc, char* argv[])
{
	int arg_count ;
	pid_t my_process_id ;
	unsigned long outer, middle, inner, total ;
	unsigned long long cycles ;
	unsigned int cpu_speed ;
	double elapsed = 0 ;
	int d_flag,h_flag, v_flag;

#ifdef _DEBUG
	d_flag = 1 ;
#endif

	// Parse any command line arguments. Use simple one character
	// option names preceded by a '-' character.
	for (arg_count = 1 ; arg_count < argc ; arg_count++)
	{
		if( argv[arg_count][0] == '-' )
		{
			switch( argv[arg_count][1] )
			{
				case 'c' :
					{
						// Measure data cache behavior
						c_flag = 1 ;
						break ;
					}
				case 'd' :
					{
						// Enable debug output
						d_flag = 1 ;
						break ;
					}
				case 'h' :
					{
						// Display usage information
						//display_usage_info(argv[0], usage_strings) ;
						h_flag = 1 ;
						break ;
					}
				case 'i' :
					{
						// Measure IPC
						i_flag = 1 ;
						break ;
					}
				case 'm' :
					{
						// Set matrix size
						fprintf(stderr, "*warning* -m is unimplemented\n") ;
						m_flag = 1 ;
						arg_count++ ;
						if (arg_count < argc)
						{
							matrix_size = atoi(argv[arg_count]) ;
							if ((matrix_size <= 0) || (matrix_size > MAX_MSIZE)) {
								fprintf(stderr, "*warning* Matrix size is limited to %d\n",
										MAX_MSIZE) ;
								matrix_size = MSIZE ;
							}
						}
						break ;
					}
				case 't' :
					{
						// Measure TLB behavior
						t_flag = 1 ;
						break ;
					}
				case 'v' :
					{
						v_flag = 1 ;
						break ;
					}
				default:
					{
						printf("Illegal option: %c\n", argv[arg_count][1]) ;
						break ;
					}
			}
		}
	}

	if (create_result_file(RESULT_FILE_NAME) == 0) {

		exit( EXIT_FAILURE ) ;
	}

	if (c_flag) {
		// Measure cache behavior
		// measure_cache() ;
	}
	else if (t_flag) {
		// Measure TLB behavior
		// measure_tlb() ;
	}
	else if (i_flag) {
		// Measure IPC (by default)
		//measure_cpi() ;
	} else {
		// Don't measurement any events
		run_no_events() ;
	}

	// print_heading("Naive matrix multiplication") ;
	// print_system_info() ;

	// Number of ARM instructions in the loop nest
	outer = 8 * MSIZE ;
	middle = 9 * MSIZE * MSIZE ;
	inner = 9 * MSIZE * MSIZE * MSIZE ;
	total = outer + middle + inner ;
	/* fprintf(result_file, "Run information\n") ; */
	/* fprintf(result_file, "  Outer loop instructions:  %lu\n", outer) ; */
	/* fprintf(result_file, "  Middle loop instructions: %lu\n", middle) ; */
	/* fprintf(result_file, "  Inner loop instructions:  %lu\n", inner) ; */
	/* fprintf(result_file, "  Total instructions:       %lu\n", total) ; */

	/* elapsed = get_elapsed_time() ; */
	/* cpu_speed = get_cpu_speed() ; // MHz */
	/* cycles = (long long int)(elapsed * 1000000.0 * (double)cpu_speed) ; */
	/* fprintf(result_file, "  Estimated cycles:         %llu\n", cycles) ; */
	/* fprintf(result_file, "  Cycles (scaled by 64):    %llu\n", cycles / 64) ; */

	/* if (c_flag || i_flag || t_flag) { */
	/*   fprintf(result_file,"Performance Monitor events\n") ; */
	/*   print_counts(result_file) ; */
	/* } */

	/* fprintf(result_file, "\nRun execution summary\n") ; */
	/* print_process_times() ; */
	/* print_elapsed_time() ; */

	/* close_result_file() ;  */
	return( EXIT_SUCCESS ) ;
}
