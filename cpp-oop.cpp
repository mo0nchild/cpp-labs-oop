﻿#include <iostream>
#include <locale>

#include "labs/lab1/lab1.h"
#include "labs/lab2/lab2.h"
#include "labs/lab3/lab3.h"

int main(void)
{
	setlocale(LC_ALL, "rus");

	lab3::run();

	return 0;
}
