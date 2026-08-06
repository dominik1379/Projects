int unsigned long sum_squared(const int line) {
	int* pole1 = (int*)malloc((line + 1) * sizeof(int));
	int* pole2 = (int*)malloc((line + 1) * sizeof(int));

	for (int i = 0; i < line; i++)
	{
		pole1[i] = 0;
		pole2[i] = 0;
	}

	for (int i = 1; i <= line + 1; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (pole1[0] == 0) {
				pole1[0] = 1;
				pole2[0] = 1;
				continue;
			}
			if (pole1[j + 1] != 0)
			{
				pole2[j + 1] = pole1[j] + pole1[j + 1];
			}

			if (i == j + 1) {
				pole2[j] = 1;
			}
		}
		for (int k = 0; k < i; k++)
		{
			pole1[k] = pole2[k];
		}
	}
	free(pole1);
	free(pole2);
}