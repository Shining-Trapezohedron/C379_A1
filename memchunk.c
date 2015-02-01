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

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<setjmp.h> //Usage example from http://en.wikipedia.org/wiki/Setjmp.h
#include<signal.h>

#include"memchunk.h"

static jmp_buf buf;

int get_mem_layout (struct memchunk *chunk_list, int size);
int readable( char* myLoc );
int writable(char * myLoc);
int find_RW(char* myLoc);
void handler( int sig );

int chunkCount; //keep track of number of chunks found

int get_mem_layout (struct memchunk *chunk_list, int size){
  /*
    Scans the memory for a fixed amount of memory and returns
    amount of chunks found
    USAGE : int chunksfound = get_mem_layout(chunklist,size)
    RETURNTYPE: int
    RETURN VALUE: The number of chunks found
   */

  //Initialize variables
  int curRW = 0;
  int prevRW = 0;
  int pageSize = getpagesize();
  int pages = 0xffffffff / pageSize;//Found it!! had to divide page size
  fprintf(stderr,"NUMBER OF PAGES %d \n", pages);
  //Logic applied from
  //http://stackoverflow.com/questions/7910240/how-to-calculate-page-table-size
  char * pageAddr =(char*) 0x00000000; //initial address 
 
  
  for(int curPage = 0; curPage < pages; curPage++) {
    prevRW = curRW;
    curRW = find_RW(pageAddr);
    //fprintf(stderr, "prevRW : %d curRW : %d\n",prevRW, curRW);
    //sleep(1);
    //fprintf(stderr,"curRW : %d",curRW);
    //what if RW is no go
    if(curRW == -1) {
      pageAddr = pageAddr + pageSize; //move to next page
      continue;
      //try again
      //https://msdn.microsoft.com/en-us/library/0ceyyskb.aspx
    }
    if(chunkCount < size){
      if (curRW == prevRW){
	chunk_list[chunkCount-1].length += pageSize;
	//NOTETOSELF: chunkCount-1 may cause issue at -1 may need handling
      }
      else {
	//Store info into the struct
	chunk_list[chunkCount].start = pageAddr;
	chunk_list[chunkCount].length = pageSize;
	chunk_list[chunkCount].RW = curRW;	
	chunkCount++;
      }
    }
    else {
      if (curRW != prevRW) chunkCount++;
    }	
    pageAddr = pageAddr + pageSize;
  }
    return chunkCount;
  
}

int readable(char* myLoc) {
  /*
    Check if we can read a location
    USAGE int f = readable(myLoc)
    RETURN TYPE: int
    RETURN VALUE: 
    Will return a 1 or 0 false or true flag
    0 : false - cannot read
    1 : true - can read
  */
  char checkRead;
  //Signal info taken from
  //http://en.cppreference.com/w/c/program/SIG_types
  signal( SIGSEGV, handler);	
  if(setjmp(buf)==1)return 0; //seg fault
  checkRead = *myLoc; //Will not work unless I attempt assign
  return 1; //Return readable
}


int writable(char * myLoc) {
  /*
    Similar to readable method but looking at writing instead
    USAGE: int f = writable(myloc)
    RETURN TYPE: int
    RETURN VALUE:
    Will return a 1 or 0 false/true flag
    0 : false - cannot write
    1 : true - can write
  */
  signal(SIGSEGV,handler);
  char checkWrite;
  if(setjmp(buf)==1) return 0; //seg fault
  checkWrite = *myLoc;  //Will not work unless I attempt assign
  return 1;//writable
}


int find_RW(char* myLoc) {
  if(readable(myLoc) ) {
    if(writable(myLoc)) {
      return 1;
    }	
    else return 0;
  }
  else return -1;
}

void handler( int sig ) {
	longjmp(buf, 1);
}

