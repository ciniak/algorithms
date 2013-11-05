//============================================================================
// Name        : bitmap.cpp
// Author      : Michal Marcinkowski
// Description : www.spoj.com/problems/BITMAP
//============================================================================

#include <cstdio>
#include <vector>

using namespace std;

int bitmap[183][183];

void printResult(int xSize, int ySize) {
    for (int i = 0; i < xSize; i++) {
         for (int j = 0; j < ySize; j++) {
            printf("%d ", bitmap[i][j]);
         }
         printf("\n");
    }
}

int toVisit[35000][2];
int startNumber = 0, endNumber = 0, toVisitSize = 0;

int main() {
    int numberOfCases, xSize, ySize, pixelsNumber, currentPath, x, y, i, j;
    char nodes[183];
    scanf("%d", &numberOfCases);
    while(numberOfCases > 0) {
        startNumber = endNumber = toVisitSize = 0;
        scanf("%d %d", &xSize, &ySize);
         for (i = 0; i < xSize; i++) {
             scanf("%s", &nodes);
             for (j = 0; j < ySize; j++) {
                 if ((nodes[j] - '0')) {
                    toVisit[endNumber][0] = i;
                    toVisit[endNumber++][1] = j;
                    toVisitSize++;
                    bitmap[i][j] = 0;
                 } else {
                    bitmap[i][j] = 33500;
                 }
             }
         }
         while(toVisitSize) {
            x = toVisit[startNumber][0];
            y = toVisit[startNumber++][1];
            toVisitSize--;
            currentPath = bitmap[x][y] + 1;
            if ((x - 1) >= 0) {
                if (bitmap[x - 1][y] > currentPath) {
                    bitmap[x - 1][y] = currentPath;
                    toVisit[endNumber][0] = x - 1;
                    toVisit[endNumber++][1] = y;
                    toVisitSize++;
                }
            }
            if ((x + 1) < xSize) {
                if (bitmap[x + 1][y] > currentPath) {
                    bitmap[x + 1][y] = currentPath;
                    toVisit[endNumber][0] = x + 1;
                    toVisit[endNumber++][1] = y;
                    toVisitSize++;
                }
            }
            if ((y - 1) >= 0) {
                if (bitmap[x][y - 1] > currentPath) {
                    bitmap[x][y - 1] = currentPath;
                    toVisit[endNumber][0] = x;
                    toVisit[endNumber++][1] = y - 1;
                    toVisitSize++;
                }
            }
            if ((y + 1) < ySize) {
                if (bitmap[x][y + 1] > currentPath) {
                    bitmap[x][y + 1] = currentPath;
                    toVisit[endNumber][0] = x;
                    toVisit[endNumber++][1] = y + 1;
                    toVisitSize++;
                }
            }
        }
        printResult(xSize, ySize);
        numberOfCases--;
    }
}




