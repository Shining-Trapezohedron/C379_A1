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
#include<unistd.h>
#include<stdlib.h>

#include"memchunk.h"
#define NUMCHUNKS 10
int main()
{
  int numChunks = NUMCHUNKS;
  int chunksFound = 0;
  int pageSize = getpagesize();
  fprintf(stdout,"GETTING MEMORY FOR CHUNK LIST\n");
  struct memchunk *chunkList = malloc( numChunks * sizeof( struct memchunk ) );
  fprintf(stdout,"RUNNING get_mem_layout WITH : %d FOR NUM CHUNKS\n",numChunks);
  chunksFound = get_mem_layout(chunkList, numChunks);

  fprintf(stdout, "get_mem_layout HAS FOUND : %d\n", chunksFound);
}
