#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<float.h>

// A structure to represent a Point in 2D plane
typedef struct Point
{
    int x, y;
}Point;


int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x - p2->x);
}
int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y - p2->y);
}

float dist(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}

float bruteForce(Point P[], int n)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

// A utility function to find minimum of two float values
float min(float x, float y)
{
    return (x < y)? x : y;
}

float stripClosest(Point strip[], int size, float d)
{
    float min = d;  // Initialize the minimum distance as d

    // Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}

float closestUtil(Point Px[], Point Py[], int n)
{
    // If there are 2 or 3 points, then use brute force
    if (n <= 3)
        return bruteForce(Px, n);

    // Find the middle point
    int mid = n/2;
    Point midPoint = Px[mid];


    // Divide points in y sorted array around the vertical line.
    // Assumption: All x coordinates are distinct.
    Point Pyl[mid+1];   // y sorted points on left of vertical line
    Point Pyr[n-mid-1];  // y sorted points on right of vertical line
    int li = 0, ri = 0;  // indexes of left and right subarrays
    for (int i = 0; i < n; i++)
    {
      if (Py[i].x <= midPoint.x)
         Pyl[li++] = Py[i];
      else
         Pyr[ri++] = Py[i];
    }

    // Consider the vertical line passing through the middle point
    // calculate the smallest distance dl on left of middle point and
    // dr on right side
    float dl = closestUtil(Px, Pyl, mid);
    float dr = closestUtil(Px + mid, Pyr, n-mid);

    // Find the smaller of two distances
    float d = min(dl, dr);

    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j] = Py[i], j++;

    // Find the closest points in strip.  Return the minimum of d and closest
    // distance is strip[]
    return min(d, stripClosest(strip, j, d) );
}

// The main functin that finds the smallest distance
// This method mainly uses closestUtil()
float closest(Point P[], int n)
{
    Point Px[n];
    Point Py[n];
    for (int i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }

    qsort(Px, n, sizeof(Point), compareX);
    qsort(Py, n, sizeof(Point), compareY);

    // Use recursive function closestUtil() to find the smallest distance
    return closestUtil(Px, Py, n);
}

// Driver program to test above functions
int main(){
    int N, i;
    struct Point *points, *pointsByY, *temp;

    //printf("11\n");
    //freopen("input.txt", "r", stdin);
    FILE* f = fopen("10points.txt", "r");
    N = 0;
    points = (Point *)malloc(sizeof(Point)*1000);
    pointsByY = (Point *)malloc(sizeof(Point)*1000);
    temp = (Point *)malloc(sizeof(Point)*1000);


    while (fscanf(f, "%d %d\n", &(points[N].x), &(points[N].y)) != EOF){
        //   printf("121313 %d\n", N);
           N++;
    }
    fclose(f);
     printf("12\n");

     for(int m = 0; m < N; M++){
        temp[m] = &points[m];
     }
    float min;
    if(N <= 3) {
        min = FLT_MAX;
        int i,j;
        for (i = 0; i < N; ++i){
            for (j = i+1; j < N; ++j){
                if (dist(points[i], points[j]) < min){
                    min = dist(points[i], points[j]);
                }   
            }
        }
        printf("the minimum distance is : \n");
        printf("%lf: (%ld, %ld) <---> (%ld, %ld)\n", min, &points[i].x, &points[i].y, &points[j].x, &points[j].y);
    }
  //  printf("sdsdsds\n");

   // qsort(points, N, sizeof(Point), cmpfunc);
   // printf("enddd\n");
  float result = closest(points, N);
  //  printf("sdsdsd\n");
  //  printf("dsdsdsdsdsd\n");
    // print the closest pair of points and their euclidean distance
   printf("closest pairs: %i\n", result;

    return 0;
}

