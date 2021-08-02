
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
typedef struct Point {
    int x, y;
} Point;

int compareX(const void* a, const void* b)
{
    struct Point *p1 = (struct Point *)a,  *p2 = (struct Point *)b;
    return (p1->x - p2->x);
}
// Needed to sort array of points according to Y coordinate
int compareY(const void* a, const void* b)
{
    struct Point *p1 = (struct Point *)a,   *p2 = (struct Point *)b;
    return (p1->y - p2->y);
}

// A utility function to find minimum of two float values
float min(float x, float y)
{
    return (x < y)? x : y;
}

// A utility function to find the distance between two points
float dist(struct Point p1, struct Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}

// A Brute Force method to return the smallest distance between two points
// in P[] of size n
float bruteForce(struct Point P[], int n, struct Point *p1, struct Point *p2)
{
    float min = FLT_MAX;
    int i, j;
    for (i = 0; i < n; ++i)
        for (j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min){
                min = dist(P[i], P[j]);
                *p1 = P[i];
                *p2 = P[j];
            }
    return min;
}
// A utility function to find the distance between the closest points of
// strip of given size. All points in strip[] are sorted according to
// y coordinate. They all have an upper bound on minimum distance as d.
// Note that this method seems to be a O(n^2) method, but it's a O(n)
// method as the inner loop runs at most 6 times
float stripClosest(struct Point strip[], int size, float d, struct Point *p1, struct Point *p2)
{
    float min = d;  // Initialize the minimum distance as d

    qsort(strip, size, sizeof(struct Point), compareY);

    // Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    int i, j;
    for (i = 0; i < size; ++i)
        for (j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min){
                min = dist(strip[i], strip[j]);
                *p1 = strip[i];
                *p2 = strip[j];
            }

    return min;
}

// A recursive function to find the smallest distance. The array P contains
// all points sorted according to x coordinate
float closestUtil(struct Point P[], int n, struct Point *p1, struct Point *p2)
{
    static struct Point pTemp1, pTemp2, pTemp3, pTemp4;
    // If there are 2 or 3 points, then use brute force
    if (n <= 3)
        return bruteForce(P, n, &pTemp1, &pTemp2);

    // Find the middle point
    int mid = n/2;
    struct Point midpoint = P[mid];

    // Consider the vertical line passing through the middle point
    // calculate the smallest distance dl on left of middle point and
    // dr on right side
    float dl = closestUtil(P, mid, &pTemp1, &pTemp2);
    float dr = closestUtil(P + mid, n-mid, &pTemp3, &pTemp4);

    // assign the pair that has smaller distance
    if(dl < dr) {
        *p1 = pTemp1;
        *p2 = pTemp2;
    }else{
        *p1 = pTemp3;
        *p2 = pTemp4;
 }

    // Find the smaller of two distances
    float dmin = min(dl, dr);

    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    struct Point strip[n];
    int j = 0 , i;
    for (i = 0; i < n; i++){
        if (abs(P[i].x - midpoint.x) < dmin){
            strip[j] = P[i], j++;
        }
    }

    // Find the closest points in strip.  Return the minimum of d and closest
    // distance is strip[]
    double dmin_strip = stripClosest(strip, j, dmin, &pTemp1, &pTemp2);
    double final_min = dmin;
    if(dmin_strip < dmin) {
        *p1 = pTemp1;
        *p2 = pTemp2;
        final_min = dmin_strip;
    }
    return final_min;
}

struct Point * closestPoints(struct Point P[], int n)
{
   

    struct Point * closestPair = (struct Point *)malloc(2 * (sizeof(struct Point)));
    if (closestPair == NULL){
        fprintf(stderr, "Error: memory allocation failed");
        exit(EXIT_FAILURE);
    }
    struct Point p1, p2;

    qsort(P, n, sizeof(struct Point), compareX);

    // Use recursive function closestUtil() to find the smallest distance
    closestUtil(P, n, &p1, &p2);

    closestPair[0] = p1;
    closestPair[1] = p2;

    return closestPair;
}


// Test Driver
int main(){
     int N, i;
    struct Point *points, *pointsByY, *temp;

    //printf("11\n");
    //freopen("input.txt", "r", stdin);
    FILE* f = fopen("<1000></1000>points.txt", "r");
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
   Point* result = closestPoints(points, N);
  //  printf("sdsdsd\n");
  //  printf("dsdsdsdsdsd\n");
    // print the closest pair of points and their euclidean distance
   printf("closest pairs: %i, %i,|||| %i, %i \n ", result[0].x,result[0].y, result[1].x, result[1].y);

    return 0;
}
