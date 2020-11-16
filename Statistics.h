#pragma once

/* Stores the various statistical data for the terms to be conveniently stored
and passed between classes */
struct Statistics {
	int min;
	int max;
	int range;
	float mean;
	float median;
	int mode;
};