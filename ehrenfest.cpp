#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

double eps = 0.3;
int nBalls = 25;
int nIters = 2000;
int mIters = 50000;

vector<int> genBalls (int n) 
{
    vector<int> vec(n);

    for (int i = 0; i < n; ++i)
    {
        vec[i] = rand() % 2;
    }

    return vec;
}

void chooseBall(vector<int>& balls)
{
    int n = balls.size();
    if ((double) rand() / RAND_MAX >= eps)
    {
        int i = rand() % n;

        balls[i] = 1 - balls[i];
    }
}

template <typename T>
void showVec(const vector<T>& vec)
{
    for_each( vec.begin(), vec.end(), [](const T& b) { cout << b << endl; } );
    cout << endl;
}

int countWhite (const vector<int>& balls)
{
    int nWhite = 0;

    for_each ( balls.begin(), balls.end(), [&nWhite](const int& b) {
            nWhite += b;
         });

    return nWhite;
}

int nThIter (vector<int>& balls, int n)
{
    for (int i = 0; i < n; ++i)
    {
        chooseBall (balls);
    }

    return countWhite (balls);
}

vector<int> repeatMTimes (vector<int>& balls, int m)
{
    vector<int> vec(nBalls + 1);

    for (int i = 0; i < m; ++i)
    {
        vec[nThIter (balls, nIters)]++;
    }

    return vec;
}

vector<double> findProbs(vector<int>& vec, int m)
{
    vector<double> probs(vec.size() + 1);

    for (int i = 0; i < vec.size() + 1; ++i)
    {
        probs[i] = vec[i] / (double) m;
    }

    return probs;
}

long factorial (int n)
{
    long res = 1;

    for (int i = 1; i <= n; ++i)
    {
        res *= i;
    }

    return res;
}

long nChooseK (int n, int k)
{
    double res = 1;

    for (int i = 1; i <= k; ++i)
    {
        res *= (n - i + 1) / (double) i;
    }
    
    return res;
}

vector<double> predictedProbs(int n)
{
    vector<double> probs(n + 1);

    for (int i = 0; i < n + 1; ++i)
    {
        probs[i] = 1 / pow(2, n) * nChooseK(n, i);
    }

    return probs;
}

template <typename T, typename K>
void showAlong(const vector<T>& vec1, const vector<K>& vec2)
{
    int n = min (vec1.size(), vec2.size());

    for (int i = 0; i < n; ++i)
    {
        cout << vec1[i] << '\t' << vec2[i] << endl;
    }
}

int main ()
{
    vector<int> balls = genBalls(nBalls);

    auto counts = repeatMTimes (balls, mIters);
    auto res = findProbs (counts, mIters);
    auto predProbs = predictedProbs (nBalls);

    showAlong(res, predProbs);
    
    return 0;
}
