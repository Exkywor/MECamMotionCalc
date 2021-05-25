#include <stdio.h>

void *promptValues(float *arr, char *name);
float relativize(float lenghts[], float startTime, float endTime, float point[]);

int main() {
	int span;
	printf("How many InterpDatas does the camera movement span? ");
	if ((scanf("%d", &span) != 1) || (span <= 1)) {
		printf("Error: Span must be a number bigger than 1\n");
		return 0;
	}
	
	float lengths[span];
	float timelineLength;
	// NEED TO VALIDATE THAT THEY ARE NOT OUTISDE INTERPDATA BOUNDS
	float startTime;
	float endTime;
	for (int i = 0; i < span; i++) {
		printf("Input InterpData %d length in seconds: ", i+1);
		if ((scanf("%f", &lengths[i])) != 1) {
			printf("Error: InterpData length must be a number\n");
			return 0;
		}
		if (i == 0) {
			printf("At what time (in this InterpData) does the movement begin? ");
			scanf("%f", &startTime); 
			timelineLength += (lengths[i] - startTime);
		} else if (i == span-1) {
			printf("At what time (in this InterpData) does the movement end? ");
			scanf("%f", &endTime); 
			timelineLength += endTime;
		} else {
			timelineLength += lengths[i];
		}
	}
	printf("Your timeline length is: %f seconds\n", timelineLength);
	
	// Starting values
	float posS[3];
	float rotS[3];
	// Ending values
	float posE[3];
	float rotE[3];
	// Prompt for values
	promptValues(posS, "starting position");
	// promptValues(rotS, "starting rotation");
	// promptValues(posE, "ending position");
	// promptValues(rotE, "ending rotation");
	
	// Prompt for how many points the user wants to find
	int nToFind;
	printf("How many points do you want to find? ");
	scanf("%d", &nToFind);
	float pointsToFind[nToFind][2];
	// NEED TO VALIDATE THAT THEY ARE NOT OUTSIDE INTERPDATA BOUNDS
	for (int i = 0; i < nToFind; i++) {
		int s;
		float t;
		printf("In which InterpData does point %d happen? ", i+1);
		scanf("%d", &s);
		printf("At what time of it does point %d happen? ", i+1);
		scanf("%f", &t);
		pointsToFind[i][0] = (float)(s-1);
		pointsToFind[i][1] = t;
	}
	
	// [Point1>[Pos>[x,y,z],Rot>[x,y,z]]]
	float resPoints[nToFind][2][3];
	for (int i = 0; i < nToFind; i++) {
		printf("%f\n", relativize(lengths, startTime, endTime, pointsToFind[i]));
	}
	
	return 0;
}

// DOES NOT HAVE VALIDATION
// Request user for positional and rotational values
void *promptValues(float *arr, char *name) {
	printf("Input %s as comma separated values (x,y,z): ", name);
	scanf("%f,%f,%f", &arr[0], &arr[1], &arr[2]);
	printf("%f %f %f\n", arr[0], arr[1], arr[2]);
}

// The lengths of the InterpDatas, the startTime and endTime in InterpDatas 0 and n,
// and the point to convert to relative time [interp, time in interp]
float relativize(float lengths[], float startTime, float endTime, float point[]) {
	float realTime;
	for (int i = 0; i <= point[0]; i++) {
		if (i == 0) {
			if ((int)point[0] == 0) { // Target interp is the first interp
				 realTime = ((lengths[0] - startTime) - (lengths[0] - point[1]));
				 break;
			} else {
				realTime = lengths[0] - startTime;
			}
		} else if (i == point[0]) { // Reached target Interp. We automatically stop here, but the math is different
			realTime += point[1];
		} else { // Add intermidiate interp length
			realTime += lengths[i];
		}
	}
	return realTime;
}