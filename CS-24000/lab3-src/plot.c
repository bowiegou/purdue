
#include <stdio.h>
#include <stdlib.h>

#include "rpn.h"

#define MAXCOLS 80
#define MAXROWS 40

char plot[MAXROWS][MAXCOLS];

void clearPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      plot[i][j] = ' ';
    }
  }
}

void printPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      printf("%c", plot[i][j]);
    }
    printf("\n");
  }
}

void plotXY(int x, int y, char c) {
  if ( x <0 || x>=MAXCOLS || y < 0 || y >=MAXROWS) return;
  plot[y][x]=c;
}

void createPlot( char * funcFile, double minX, double maxX) {
  int nvals = MAXCOLS;
  double yy[MAXCOLS];

  clearPlot();
  double miniX = minX;
  int i = 0;
  double minY;
  double maxY;
  double step = (maxX - minX) /80.0;
  // Evaluate function and store in vector yy
  for(;miniX <= maxX; miniX += step){
    yy[i] = rpn_eval(funcFile,miniX);
    i ++;
    printf("%lf\n", yy[i-1]);
  }
  minY = yy[0];
  maxY = yy[0];
  //Compute maximum and minimum y in vector yy
  for(i = 1;i < MAXCOLS; i++){
    if(yy[i] < minY) {
      minY = yy[i];
    }
    if(yy[i] > maxY) {
      maxY = yy[i];
    }

  }
  double stepY = (maxY - minY)/40.0;
  int cx;
  int cy;
  //printf("%lf %lf\n", minY,stepY );

  //printf("%d\n", (minY > 0) );
  if((int)minY <= 0){
    cx = 39-((int)((0-minY)/stepY));
    //printf("(%d)\n", cx );
  }
  if((int)minX <= 0) {
    cy = (0 - minX)/step;
  }
  
  if(&cx != NULL){
    for(i = 0; i < MAXCOLS;i++) {
      plotXY(i,cx,'_');
    }
  }
  if(&cy != NULL){
    for(i = 0; i < MAXROWS;i++) {
      plotXY(cy,i,'|');
    }
  }
  //miniX = minX;

  //Plot x and y axis
  for(i = 0;i < MAXCOLS; i++){
    //yy[i] = rpn_eval(funcFile,miniX);
    plotXY(i,(int)((maxY-yy[i])/stepY),'*');
    
  }

  // Plot function. Use scaling.
  // minX is plotted at column 0 and maxX is plotted ar MAXCOLS-1
  // minY is plotted at row 0 and maxY is plotted at MAXROWS-1

  printPlot();

}

int main(int argc, char ** argv)
{
  printf("RPN Plotter.\n");
  
  if (argc < 4) {
    printf("Usage: plot func-file xmin xmax\n");
    exit(1);
  }

  // Get arguments
  //printf("%s",argv[1]);
  //printf("%lf\n",atof(argv[2]) );
  createPlot(argv[1], atof(argv[2]), atof(argv[3]));

}
