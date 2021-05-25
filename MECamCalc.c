#include <stdio.h>

void *promptValues(float *arr, char *name);

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
	promptValues(rotS, "starting rotation");
	promptValues(posE, "ending position");
	promptValues(rotE, "ending rotation");
	
	// Prompt for how many points the user wants to find
	int nToFind;
	printf("How many points do you want to find? ");
	scanf("%d", &nToFind);
	float pointsToFind[nToFind][2];
	// NEED TO VALIDATE THAT THEY ARE NOT OUTISDE INTERPDATA BOUNDS
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
	
	
	return 0;
}

// DOES NOT HAVE VALIDATION
// Request Starting position and rotation
void *promptValues(float *arr, char *name) {
	printf("Input %s as comma separated values (x,y,z): ", name);
	scanf("%f,%f,%f", &arr[0], &arr[1], &arr[2]);
	printf("%f %f %f\n", arr[0], arr[1], arr[2]);
}
