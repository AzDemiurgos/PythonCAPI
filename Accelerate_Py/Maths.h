#pragma once
#include <vector>
#include <ppl.h>
#include <concurrent_vector.h>

#define matrix std::vector<std::vector<double>>
int it = 300;
std::vector<double> lambda;

void calculateWithOutAccelerate(matrix* in_data, int count)
{
    matrix* temp = nullptr;
    size_t i_count = in_data->size();
    if (i_count == 0)
        return;
    size_t j_count = (*in_data)[0].size();
    for (int k = 0; k < count; k++)
    {
        for (size_t i = 0; i < i_count; i++)
        {
            for (size_t j = 1; j < j_count - 1; j++)
            {
                auto value_c = (*in_data)[i][j];
                auto value_p = (*in_data)[i][j - 1];
                auto value_n = (*in_data)[i][j + 1];
                auto value_prev = value_p - value_c;
                auto value_next = value_n - value_c;
                (*in_data)[i][j] = value_c + value_prev / sqrtf(1 + powf(value_prev / lambda[i], 2.0)) +
                    value_next / sqrtf(1 + powf(value_next / lambda[i], 2.0));
            }
        }
    }
}

void calculateWithPPL1(matrix* in_data,int count)
{
    matrix* temp = nullptr;
    int i_count = in_data->size();
    if (i_count == 0)
        return;
    int j_count = (*in_data)[0].size();
    for (int k = 0; k < count; k++)
    {
        concurrency::parallel_for(0, i_count, [j_count, &in_data](int i)
        {
            for (size_t j = 1; j < j_count - 1; j++)
            {
                auto value_c = (*in_data)[i][j];
                auto value_p = (*in_data)[i][j - 1];
                auto value_n = (*in_data)[i][j + 1];
                auto value_prev = value_p - value_c;
                auto value_next = value_n - value_c;
                (*in_data)[i][j] = value_c + value_prev / sqrtf(1 + powf(value_prev / lambda[i], 2.0)) +
                    value_next / sqrtf(1 + powf(value_next / lambda[i], 2.0));
            }
        });
    }
}


void calculateWithOut(matrix& data, std::vector<double> lambdas, int it_count)
{
    it = it_count;
    lambda = lambdas;
    calculateWithOutAccelerate(&data, it);
}

void calculateWithPPL1(matrix& data, std::vector<double> lambdas, int it_count)
{
    it = it_count;
    lambda = lambdas;
    calculateWithPPL1(&data, it);
}

