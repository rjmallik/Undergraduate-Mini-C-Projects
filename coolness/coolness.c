#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_wind_coolness(double V, double T) {
    double result = 35.74 + 0.6215 * T - 35.75 * pow(V, 0.16) + 0.4275 * T * pow(V, 0.16);
    return result;
}

int main(int argc, char *argv[]) {
    double V, T, result;
    if (argc == 1) {
        printf("Temp\tWind\tCoolness\n");
  
        for (int i = -10; i <= 40; i += 10) {
            for (int j = 5; j <= 15; j += 5) {
                T = i;
                V = j;
                result = calculate_wind_coolness(V, T);
                printf("%.1lf\t%.1lf\t%.1lf\n", T, V, round(result * 10) / 10);
                
            }
        printf("\n");
        }
    } else if (argc == 2) {
        T = atof(argv[1]);
        if (T < -99 || T > 50) {
            printf("Error: Coolness. Acceptable input values are -99<=T<=50 and 0.5<=V.\n");
            return 1;
        }
        printf("Temp\tWind\tCoolness\n");
        for (int i = 5; i <= 15; i += 5) {
            V = i;
            if (V < 0.5) {
                printf("Error: Coolness. Acceptable input values are -99<=T<=50 and 0.5<=V.\n");
                return 1;
            }
            result = calculate_wind_coolness(V, T);
            printf("%.1lf\t%.1lf\t%.1lf\n", T, V, round(result * 10) / 10);
        }
    } else if (argc == 3) {
        T = atof(argv[1]);
        V = atof(argv[2]);
        if (T < -99 || T > 50) {
            printf("Error: Coolness. Acceptable input values are -99<=T<=50 and 0.5<=V.\n");
            return 1;
        }
        if (V < 0.5) {
            printf("Error: Coolness. Acceptable input values are -99<=T<=50 and 0.5<=V.\n");
            return 1;
        }
        
        printf("Temp\tWind\tCoolness\n");
        result = calculate_wind_coolness(V, T);
        printf("%.1lf\t%.1lf\t%.1lf\n", T, V, round(result * 10) / 10);
    }else{
        printf("Error: Incorrect number of arguments\n");
        return 1;
    }
    return 0;
}
