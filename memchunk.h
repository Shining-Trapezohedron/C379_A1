/*
    memchunk- A simple program to experiment with system memory by James Devito
    Copyright (C) 2015  James Devito 1279233

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MEMCHUNKHEADER
#define MEMCHUNKHEADER

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<setjmp.h> //Usage example from http://en.wikipedia.org/wiki/Setjmp.h
#include<signal.h>


struct memchunk {
  void *start;
  unsigned long length;
  int RW;
};


int get_mem_layout (struct memchunk *chunk_list, int size);
int readable( char* myLoc );
int writable(char * myLoc);
int find_RW(char* myLoc);
void handler( int sig );

#endif
