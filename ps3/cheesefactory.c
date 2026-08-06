#include <stdio.h>
#include <math.h>

# define M_PI 3.14159265358979323846

struct gula
{
    double R;
    double X;
    double Y;
    double Z;
};

double min(double a, double b)
{
    if (a < b)
        return a;
    return b;
}

/*double max(double a, double b)
{
    if (a > b)
        return a;
    return b;
}*/
int main()
{
    int S, M; //M - pocet dier v syre, S - pocet platov
    int R, X, Y, Z;
    struct gula diery[10000];

    scanf("%d %d", &M, &S);

    double objemSyraBezDier = 100 * 100 * 100;
    //double objemPlatkuBezDier = objemSyraBezDier / S;
    double objemSyraSDierami = objemSyraBezDier;

    for (int i = 0; i < M; i++)
    {
        scanf("%d %d %d %d", &R, &X, &Y, &Z);
        diery[i].R = R / 1000.0;
        diery[i].X = X / 1000.0;
        diery[i].Y = Y / 1000.0;
        diery[i].Z = Z / 1000.0;

        double objemGule = (4.0 / 3.0) * M_PI * pow(diery[i].R, 3);
        objemSyraSDierami -= objemGule;
    }

    double objemPlatkuSDierami = objemSyraSDierami / S;
    //double koeficient = 100 * 100 * 100 / objemSyraSDierami;
    //double hrubkaPlatku = (objemPlatkuSDierami / (100 * 100)) * koeficient;
    double zPredosle = 0;

    for (int i = 0; i < S - 1; i++)
    {
        double zMin = zPredosle;
        double zMax = 100;
        double zVypocitane;
        while (1)
        {
            zVypocitane = (zMin + zMax) / 2;

            double objemAktualnehoPlatku = 100 * 100 * (zVypocitane - zPredosle);

            for (int iDiera = 0; iDiera < M; iDiera++)
            {
                double zZaciatokDiery = diery[iDiera].Z - diery[iDiera].R;
                double zKoniecDiery = diery[iDiera].Z + diery[iDiera].R;

                // ak je cela gula v platku
                if (zZaciatokDiery >= zPredosle && zKoniecDiery <= zVypocitane)
                {
                    double objemGule = (4.0 / 3.0) * M_PI * pow(diery[iDiera].R, 3);
                    objemAktualnehoPlatku -= objemGule;
                }
                // ak ma gula prienik s platkom
                else if (zZaciatokDiery < zVypocitane && zKoniecDiery > zPredosle)
                {
                    double h;
                    double objemGulePredPlatkom = 0;
                    double objemGuleVnutriPlatku = 0;

                    if (zZaciatokDiery < zPredosle)
                    {
                        h = zPredosle - zZaciatokDiery;
                        objemGulePredPlatkom = M_PI * ((pow(h, 2) * diery[iDiera].R) - (pow(h, 3) / 3.0));
                    }

                    h = min(zKoniecDiery, zVypocitane) - zZaciatokDiery;
                   objemGuleVnutriPlatku = M_PI * ((pow(h, 2) * diery[iDiera].R) - (pow(h, 3) / 3.0));
                    objemGuleVnutriPlatku -= objemGulePredPlatkom;

                    objemAktualnehoPlatku -= objemGuleVnutriPlatku;
                }
            }

            double rozdiel = objemPlatkuSDierami - objemAktualnehoPlatku;
            if (rozdiel > -0.000001 && rozdiel < 0.000001)

                break;

            if (rozdiel > 0)
                zMin = zVypocitane;
            else
                zMax = zVypocitane;
        }

        printf("%.9f\n", zVypocitane - zPredosle);
        zPredosle = zVypocitane;
    }

    printf("%.9f\n", 100 - zPredosle);

    return 0;
}
