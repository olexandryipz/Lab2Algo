#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 4294967296
#define N 250
#define K 40000

unsigned long long seed = 0;

unsigned long long congruentialGenerator(unsigned long long a, unsigned long long c, unsigned long long m) {
    seed = (a * seed + c) % m;
    return seed;
}

void calculateFrequency(unsigned long long* randomValues, int* frequency, int n) {
    for (int i = 0; i < K; i++) {
        int interval = randomValues[i] % n;
        frequency[interval]++;
    }
}

void calculateProbability(int* frequency, double* probability, int length) {
    for (int i = 0; i < N; i++) {
        probability[i] = (double)frequency[i] / length;
    }
}

double calculateMean(unsigned long long* randomValues) {
    double sum = 0;
    for (int i = 0; i < K; i++) {
        sum += randomValues[i];
    }
    return sum / K;
}

double calculateVariance(unsigned long long* randomValues, double mean) {
    double sum = 0;
    for (int i = 0; i < K; i++) {
        sum += pow(randomValues[i] - mean, 2);
    }
    return sum / K;
}

double calculateStandardDeviation(double variance) {
    return sqrt(variance);
}

int main() {
    unsigned long long a = 1664525;
    unsigned long long c = 1013904223;
    int frequency[N] = { 0 };
    double probability[N];
    unsigned long long randomValues[K];

    for (int i = 0; i < K; i++) {
        randomValues[i] = congruentialGenerator(a, c, M);
    }

    calculateFrequency(randomValues, frequency, N);

    calculateProbability(frequency, probability, K);

    double mean = calculateMean(randomValues);

    double variance = calculateVariance(randomValues, mean);

    double standardDeviation = calculateStandardDeviation(variance);

    printf("Частота інтервалів появи випадкових величин: \n");
    for (int i = 0; i < N; i++) {
        printf("%d: %d\n", i, frequency[i]);
    }
    printf("\nСтатистична імовірність появи випадкових величин: \n");
    for (int i = 0; i < N; i++) {
        printf("%d: %lf\n", i, probability[i]);
    }
    printf("\nМатематичне сподівання випадкових величин: %lf\n", mean);
    printf("\nДисперсія випадкових величин: %lf\n", variance);
    printf("\nCередньоквадратичне відхилення випадкових величин: %lf\n", standardDeviation);

    return 0;
}
