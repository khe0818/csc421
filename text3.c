#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<float.h>
#include <string.h>
typedef struct Point
{
 int x, y;
}Point;

float dmin = 0; 
Point final1;
Point final2;
int count = 0;
int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a; 
    Point *p2 = (Point *)b;
    return (p1->x - p2->x);
}
int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a; 
    Point *p2 = (Point *)b;
    return (p1->y - p2->y);
}

float calculateD(Point p1, Point p2)
{
      int X = p1.x - p2.x;
      int Y = p1.y - p2.y;
      return sqrt(X*X + Y*Y);

}
float bruteForce(Point P[], int n)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i){
        for (int j = i+1; j < n; ++j){
            if (calculateD(P[i], P[j]) < min){
                min = calculateD(P[i], P[j]);
            }
        }
    }
    return min;
}
float min(float x, float y)
{
    return (x < y)? x : y;
}
float closestPoint(Point p1, Point p2, float min){
    if(calculateD(p1,p2) < dmin){
        dmin = calculateD(p1,p2);
        final1 = p1;
        final2 = p2;
    }
    return dmin;
}

float stripClosest(Point strip[], int size, float d, int count)
{    
    float min = d; 
    for (int i = 0; i < size; ++i){
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j){
            if (calculateD(strip[i],strip[j]) < min){
                min = calculateD(strip[i], strip[j]);
                dmin = closestPoint(strip[i],strip[j], min);
            }      
        }
    }
        return min;
}

float closestPair(Point Px[], Point Py[], int n)
{   int j = 0;
    int mid = n/2; 
    int m = 0;
    int k = 0; 
    Point strip[n];
    Point midPoint = Px[mid];
    Point Pyleft[mid+1];   
    Point Pyright[n-mid-1]; 
    if (n <= 3){
         return bruteForce(Px, n);
     } 
    for (int i = 0; i < n; i++)
    {
      if (Py[i].x <= midPoint.x)
         Pyleft[m++] = Py[i];
      else
         Pyright[k++] = Py[i];
    }
    float left = closestPair(Px, Pyleft, mid);
    float right = closestPair(Px + mid, Pyright, n-mid);
    float d = min(left, right);
    for (int i = 0; i < n; i++){
        if (abs(Py[i].x - midPoint.x) < d){
            strip[j] = Py[i];
            j++;
        }
    }
    return stripClosest(strip, j, d, count++);
}
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
    return closestPair(Px, Py, n);
}

int main(){
    int N;
    struct Point *points;
    FILE* f = fopen("1000points.txt", "r");
    N = 0;
    points = (Point *)malloc(sizeof(Point)*1000);
     while (fscanf(f, "%d %d\n", &(points[N].x), &(points[N].y)) != EOF){
           N++;
    }
    fclose(f);
    dmin = FLT_MAX;
   // finals[0].x = 0, finals[0].y= 0,finals[0].m = 0, finals[0].n= 0,finals[0].d = 0, finals[0].count= 0;
   float result = closest(points, N);
   printf("closest pairs: %f (%d, %d) (%d, %d) \n", result, final1.x, final1.y,final2.x,final2.y);
    return 0;
}

