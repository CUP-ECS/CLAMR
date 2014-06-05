/*
 *  Copyright (c) 2011-2012, Los Alamos National Security, LLC.
 *  All rights Reserved.
 *
 *  Copyright 2011-2012. Los Alamos National Security, LLC. This software was produced 
 *  under U.S. Government contract DE-AC52-06NA25396 for Los Alamos National 
 *  Laboratory (LANL), which is operated by Los Alamos National Security, LLC 
 *  for the U.S. Department of Energy. The U.S. Government has rights to use, 
 *  reproduce, and distribute this software.  NEITHER THE GOVERNMENT NOR LOS 
 *  ALAMOS NATIONAL SECURITY, LLC MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR 
 *  ASSUMES ANY LIABILITY FOR THE USE OF THIS SOFTWARE.  If software is modified
 *  to produce derivative works, such modified software should be clearly marked,
 *  so as not to confuse it with the version available from LANL.
 *
 *  Additionally, redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Los Alamos National Security, LLC, Los Alamos 
 *       National Laboratory, LANL, the U.S. Government, nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE LOS ALAMOS NATIONAL SECURITY, LLC AND 
 *  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
 *  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL LOS ALAMOS NATIONAL
 *  SECURITY, LLC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *  
 *  CLAMR -- LA-CC-11-094
 *  This research code is being developed as part of the 
 *  2011 X Division Summer Workshop for the express purpose
 *  of a collaborative code for development of ideas in
 *  the implementation of AMR codes for Exascale platforms
 *  
 *  AMR implementation of the Wave code previously developed
 *  as a demonstration code for regular grids on Exascale platforms
 *  as part of the Supercomputing Challenge and Los Alamos 
 *  National Laboratory
 *  
 *  Authors: Bob Robey       XCP-2   brobey@lanl.gov
 *           Neal Davis              davis68@lanl.gov, davis68@illinois.edu
 *           David Nicholaeff        dnic@lanl.gov, mtrxknight@aol.com
 *           Dennis Trujillo         dptrujillo@lanl.gov, dptru10@gmail.com
 * 
 */
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_OPENGL
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define OMPI_SKIP_MPICXX 1

#ifdef HAVE_MPI
#include <mpi.h>
#endif

#ifdef HAVE_MPE
#ifndef HAVE_MPI
#define MPE_NOMPI
#define CLOG_NOMPI
#endif
#define MPE_INTERNAL
#define MPE_GRAPHICS
#include "mpe.h"
#define MPE_DRAG_FIXED_RECT 8
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//keyboard input files
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <math.h>
#endif

#if !defined(FULL_PRECISION) && !defined(MIXED_PRECISION) && !defined(MINIMUM_PRECISION)
#define FULL_PRECISION
#endif
#ifdef NO_CL_DOUBLE
#undef  FULL_PRECISION
#undef  MIXED_PRECISION
#define MINIMUM_PRECISION
#endif

#if defined(MINIMUM_PRECISION)
   typedef float state_t; // this is for physics state variables ncell in size
   typedef float real_t; // this is used for intermediate calculations
   typedef float display_t; // for display variable
   typedef float spatial_t; // for spatial variables
   typedef float real_spatial_t; // for intermediate spatial variables

#elif defined(MIXED_PRECISION) // intermediate values calculated high precision and stored as floats
   typedef float state_t;
   typedef double real_t;
   typedef float display_t; // for display variable
   typedef float spatial_t; // for spatial variables
   typedef double real_spatial_t; // for intermediate spatial variables

#elif defined(FULL_PRECISION)
   typedef double state_t;
   typedef double real_t;
   typedef double display_t; // for display variable
   typedef double spatial_t; // for spatial variables
   typedef double real_spatial_t; // for intermediate spatial variables
#endif

void init_display(int *argc, char **argv, const char* string, int mype_in);
void set_idle_function(void (*function)(void));
void start_main_loop(void);
void free_display(void);
void set_viewmode(int display_view_mode_in);
void set_outline(int display_outline_in);
void set_mysize(int mysize_in);
void set_window(float display_xmin_in, float display_xmax_in, float display_ymin_in, float display_ymax_in);
void set_cell_coordinates(real_t *x_in, real_t *dx_in, real_t *y_in, real_t *dy_in);
void set_cell_data(real_t *data_in);
void set_cell_proc(int *display_proc_in);
void set_circle_radius(double display_circle_radius_in);
void draw_scene(void);

#ifdef __cplusplus
}
#endif

#endif

