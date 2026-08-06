#include <stdio.h>

int main()
{
    int n, t; //n - row, t - time
    int sTmp, vTmp;
    double s[1000];
    double v[1000];

    double maxK = 2000;
    double minK = -1000;

    scanf("%d %d", &n, &t);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &sTmp, &vTmp);

        s[i] = sTmp;
        v[i] = vTmp;

        if (minK < -v[i])
            minK = -v[i];
    }
    double k;
    while (1)
    {
        k = (minK + maxK) / 2;
        //double kPosledne = k;

        // s1/(k + v1) + s2/(k + v2) + s3/(k + v3) = t
        double tVypocitane = 0;
        for (int i = 0; i < n; i++)
        {
            tVypocitane += (s[i] / (k + v[i]));
        }

        double tRozdiel = t - tVypocitane;
        //if (tRozdiel > -0.000001 && tRozdiel < 0.000001)
        //    break;

        long long presnost = 10000000;
        if (tRozdiel > 0)
        {
            if ((long long)(maxK * presnost) == (long long)(k * presnost))
                break;
            maxK = k;
        }
        else
        {
            if ((long long)(minK * presnost) == (long long)(k * presnost))
                break;
            minK = k;
        }
    }

    printf("%.9f\n", k);

    return 0;
}
