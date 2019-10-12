#!/bin/sh
#echo `ls *.c | sed s/.c$/.o/ | xargs`
echo test_cplex.o cplex_add.o cplex_mult.o cplex_sub.o cplex_div.o \
	  cplex_sq.o cplex_mag.o cplex_theta.o cplex_sqrt.o cplex_cbrt.o \
	  cplex_vec_dot.o cplex_vec_cross.o cplex_check.o cplex_quad.o \
	  cplex_det.o cplex_cmp.o tohex.o check_status.o cplex_cramer.o \
	  cplex_vec_normalize.o cplex_vec_mag.o