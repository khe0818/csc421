
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
typedef struct Point {
    int x, y;
} Point;

Point *result1, *result2;
float shortestDistance;

float calDistance(Point a, Point b)  {
    int X = a.x - b.x, Y = a.y - b.y;
    printf("calDistance\n");
    return (float)sqrt(X*X + Y*Y);
}



int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

float min(float x, float y){
	return(x < y)?x:y;
}
float findClosest(Point* temp, int N, float d){
	float min = d;
	temp = (Point*) malloc(sizeof(Point)*1000);
	qsort(temp, N, sizeof(Point), cmpfunc);
	int i;
	int j;	
	for(i = 0; i < N; ++i){
		for(j = i + 1; (j < N && (temp[j].y - temp[i].y) < min); ++j){
			 if (calDistance(temp[i],temp[j]) < min){
			 	min = calDistance(temp[i], temp[j]);
			 }
         }
	}
	*result1 = temp[i];
	*result2 = temp[j];
	return min;
}

float closestPair(Point* points, int N)   {
    points = (Point *)malloc(sizeof(Point)*1000);
    int mid = N/2;
    Point midPoint = points[mid];
    float left = closestPair(points, mid);
    float right = closestPair(points + mid, N - mid);
    float d = min(left,right);
    Point temp[N];
    int j = 0;
    for(int i = 0;i < N; i++){
    	if(abs(points[i].x - midPoint.x) < d){
    		temp[j] = points[i];
    		j++;
    	}
    }

    return min(d, findClosest(temp,j,d));
}


int main()  {
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
    	//	 printf("121313 %d\n", N);
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
	            if (calDistance(points[i], points[j]) < min){
	                min = calDistance(points[i], points[j]);
	            }	
	        }
	    }
	    printf("the minimum distance is : \n");
	    printf("%lf: (%ld, %ld) <---> (%ld, %ld)\n", min, &points[i].x, &points[i].y, &points[j].x, &points[j].y);
    }
  //  printf("sdsdsds\n");

   // qsort(points, N, sizeof(Point), cmpfunc);
   // printf("enddd\n");
    for(i=0; i<N; i++)
        pointsByY[i] = points[i];

  //  printf("sdsdsd\n");
    closestPair(points, N);
  //  printf("dsdsdsdsdsd\n");
    // print the closest pair of points and their euclidean distance
    printf("%lf %lf\n", result1->x, result1->y);
    printf("%lf %lf\n", result2->x, result2->y);
    printf("%lf\n", shortestDistance);

    return 0;
}