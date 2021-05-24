#include <stdio.h>

int main() {
	int span;
	printf("How many InterpDatas does the camera movement span? ");
	if ((scanf("%d", &span) != 1) || (span <= 1)) {
		printf("Error: Span must be a number bigger than 1");
		return 0;
	}
	float lengths[span];
	float timeline_length;
	for (int i = 0; i < span; i++) {
		printf("Input InterpData %d length in seconds: ", i+1);
		if ((scanf("%f", &lengths[i])) != 1) {
			printf("Error: InterpData length must be a number");
			return 0;
		}
		timeline_length += lengths[i];
	}
	printf("Your timeline length is: %f\n seconds", timeline_length);
	// Starting values
	float posS[3];
	float rotS[3];
	// Ending values
	float posE[3];
	float rotE[3];
	float test2;
	float test3;
	
	// printf("How many InterpDatas does the camera movement span? ");
	// scanf("%f, %f, %f", &posS[0], &posS[1], &posS[2]);
	// printf("%f %f %f\n", posS[0], posS[1], posS[2]);
	return 0;
}
