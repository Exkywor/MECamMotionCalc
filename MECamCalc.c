#include <stdio.h>
#include <math.h>

void *promptValues(float *arr, char *name);
float relativize(float lengths[], float startTime, float endTime, float point[]);
float calculateVals(float res[2][3], float targetTime, float timelineLength,
                    float posS[], float posE[], float rotS[], float rotE[]);
float calculateVal(float x, float x2, float y2, float y1);
void printVals(float vals[3]); 

int main() {
	int span;
	printf("How many InterpDatas does the camera movement span? ");
	if ((scanf("%d", &span) != 1) || (span <= 1)) {
		printf("Error: Span must be a number bigger than 1\n");
		return 0;
	}
	
	float lengths[span];
	float timelineLength;
	// NEED TO VALIDATE THAT THEY ARE NOT OUTSIDE INTERPDATA BOUNDS
	float startTime;
	float endTime;
	for (int i = 0; i < span; i++) {
		printf("InterpData %d length in seconds: ", i+1);
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
	
	// Starting values
	float posS[3];
	float rotS[3];
	// Ending values
	float posE[3];
	float rotE[3];
	// Prompt for values
	promptValues(posS, "Starting position");
	promptValues(rotS, "Starting rotation");
	promptValues(posE, "Ending position");
	promptValues(rotE, "Ending rotation");
	
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
		calculateVals(resPoints[i],
                      relativize(lengths, startTime, endTime, pointsToFind[i]),
					  timelineLength,
					  posS, posE,
					  rotS, rotE);
	}

	// Print resulting information
	printf("\nSTARTING POINT\n--------------\n");
	printf("Position: ");
	printVals(posS);
	printf("Rotation: ");
	printVals(rotS);
	printf("\n");
	// printf("REQUESTED POINTS\n----------------\n");
	for (int i = 0; i < nToFind; i++) {
		printf("POINT %d:\n--------\n", i+1);
		printf("Position: ");
		printVals(resPoints[i][0]);
		printf("Rotation: ");
		printVals(resPoints[i][1]);
		printf("\n");
	}
	printf("ENDING POINT\n------------\n");
	printf("Position: ");
	printVals(posE);
	printf("Rotation: ");
	printVals(rotE);

	return 0;
}	
	
	
// Prompts user for positional and rotational values
void *promptValues(float *arr, char *name) {
	printf("%s as comma separated values (x,y,z): ", name);
	scanf("%f,%f,%f", &arr[0], &arr[1], &arr[2]);
}

// PARAMS: The lengths of the InterpDatas, the startTime and endTime in InterpDatas 0 and n,
// and the point to convert to relative time [interp, time in interp]
float relativize(float lengths[], float startTime, float endTime, float point[]) {
	float realTime;
	for (int i = 0; i <= point[0]; i++) {
		if (i == 0) {
			if (round(point[0]) == 0) { // Target interp is the first interp
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

// PARAMS: The array in which to store the resulting values [pos[x,y,z], rot[x,y,z]], the target time, the length of the timeline
// and the starting and ending values
float calculateVals(float res[2][3], float targetTime, float timelineLength,
                    float posS[], float posE[], float rotS[], float rotE[]) {
    // Calculate position values
	for (int i = 0; i < 3; i++) {
		res[0][i] = calculateVal(targetTime, timelineLength, posE[i], posS[i]);
	}
	// Calculate rotation values
	for (int i = 0; i < 3; i++) {
		res[1][i] = calculateVal(targetTime, timelineLength, rotE[i], rotS[i]);
	}
}

float calculateVal(float x, float x2, float y2, float y1) {
	return (((y2 - y1) / x2) * x) + y1;
}

void printVals(float vals[3]) {
	for (int i = 0; i < 3; i++) {
		printf("%.2f ", vals[i]);
	}
	printf("\n");
}