#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	double weight;
	double value;
	char *name;
	bool packed;
	bool optimal;
} Item;

Item bag[11] = {
	{ 1, 1, "pizza", false, false},
	{ 1.5, 2, "doener", false, false},
	{ 0.5, 0.75, "knife", false, false},
	{ 4, 3, "phone", false, false},
	{ 1, 1.2, "charger", false, false},
	{ 1, 2, "pet", false, false},
	{ 2, 2, "cactus", false, false},
	{ 0.4, 0.5, "clock", false, false},
	{ 1.2, 1.1, "glasses", false, false},
	{ 1.4, 1.4, "pen", false, false},
	{ 0.2, 0.3, "paper", false, false}
};

int length = 11;
double max_value = 0;

void set_if_best(double value) {
	if (value > max_value) {
		max_value = value;
		for (int i = 0; i < length; i++) {
			bag[i].optimal = bag[i].packed;
		}
	}
}

void try(int index, double free, double value) {
	if (index >= length) {
		set_if_best(value);
		return;
	}
	if (free >= bag[index].weight) {
		bag[index].packed = true;
		try(index + 1, free - bag[index].weight, value + bag[index].value);
	}
	bag[index].packed = false;
	try(index + 1, free, value);
}
/*
int main(int argc; const char *argv[]) {
                 ^
*/
int main(int argc, const char *argv[]) {
	try(0, atof(argv[1]), 0);
	double weight = 0;
	double value = 0;
	for (int i = 0; i < length; i++) {
		if (!bag[i].optimal) {
/*
            break;
            ^
*/
			continue;
		}
		printf("%s\n", bag[i].name);
		weight += bag[i].weight;
		value += bag[i].value;
	}
/*
	printf("weight: %f, value: %f");
                                  ^
*/
    printf("weight: %f, value: %f", weight, value);
}