// Console.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <ppl.h>
#include <concurrent_vector.h>
#include <algorithm>
#include "../Accelerate_Py/Maths.h"

#define matrix std::vector<std::vector<double>>

//void calculateWithOutAccelerate(matrix* in_data, matrix* out_data, int count)
//{
//    matrix* temp = nullptr;
//    size_t i_count = in_data->size();
//    if (i_count == 0)
//        return;
//    size_t j_count = (*in_data)[0].size();
//    for (int k = 0; k < count; k++)
//    {
//        for (size_t i = 0; i < i_count; i++)
//        {
//            for (size_t j = 1; j < j_count-1; j++)
//            {
//                auto value_c = (*in_data)[i][j];
//                auto value_p = (*in_data)[i][j-1];
//                auto value_n = (*in_data)[i][j+1];
//                (*out_data)[i][j] = value_c + (value_c - value_p)/sqrtf(1 + powf((value_c - value_p)/lambda[i], 2.0));
//            }
//        }
//        temp = out_data;
//        out_data = in_data;
//        in_data = temp;
//    }
//    out_data = temp;
//}
//
//void calculateWithPPL1(matrix* in_data, matrix* out_data, int count)
//{
//    matrix* temp = nullptr;
//    int i_count = in_data->size();
//    if (i_count == 0)
//        return;
//    int j_count = (*in_data)[0].size();
//    for (int k = 0; k < count; k++)
//    {
//        concurrency::parallel_for(0, i_count, [&out_data, j_count, &in_data](int i) 
//        {
//            for (size_t j = 1; j < j_count - 1; j++)
//            {
//                auto value_c = (*in_data)[i][j];
//                auto value_p = (*in_data)[i][j - 1];
//                auto value_n = (*in_data)[i][j + 1];
//                (*out_data)[i][j] = value_c + (value_c - value_p) / sqrtf(1 + powf((value_c - value_p) / lambda[i], 2.0));
//            }
//        });
//        temp = out_data;
//        out_data = in_data;
//        in_data = temp;
//    }
//    out_data = temp;
//}
//
//void calculateWithPPL2(matrix* in_data, matrix* out_data, int count)
//{
//    matrix* temp = nullptr;
//    int i_count = in_data->size();
//    if (i_count == 0)
//        return;
//    int j_count = (*in_data)[0].size();
//    for (int k = 0; k < count; k++)
//    {
//        for (size_t i = 0; i < i_count; i++)
//        {
//            //for (size_t j = 0; j < j_count; j++)
//            concurrency::parallel_for(1, j_count-1, [&out_data, i, &in_data](int j)
//            {
//                auto value_c = (*in_data)[i][j];
//                auto value_p = (*in_data)[i][j - 1];
//                auto value_n = (*in_data)[i][j + 1];
//                (*out_data)[i][j] = value_c + (value_c - value_p) / sqrtf(1 + powf((value_c - value_p) / lambda[i], 2.0));
//            });
//        }
//
//        temp = out_data;
//        out_data = in_data;
//        in_data = temp;
//    }
//    out_data = temp;
//}
//
//void calculateWithPPL12(matrix* in_data, matrix* out_data, int count)
//{
//    matrix* temp = nullptr;
//    int i_count = in_data->size();
//    if (i_count == 0)
//        return;
//    int j_count = (*in_data)[0].size();
//    for (int k = 0; k < count; k++)
//    {
//        concurrency::parallel_for(0, i_count, [&out_data, j_count, &in_data](int i)
//        {
//            concurrency::parallel_for(1, j_count-1, [&out_data, i, &in_data](int j)
//            {
//                auto value_c = (*in_data)[i][j];
//                auto value_p = (*in_data)[i][j - 1];
//                auto value_n = (*in_data)[i][j + 1];
//                (*out_data)[i][j] = value_c + (value_c - value_p) / sqrtf(1 + powf((value_c - value_p) / lambda[i], 2.0));
//            });
//        });
//        temp = out_data;
//        out_data = in_data;
//        in_data = temp;
//    }
//    out_data = temp;
//}

void calculateWithOut(matrix& data)
{
    //testCalculator(data);
    matrix out_data(data);
    calculateWithOutAccelerate(data, it);
    std::move(out_data.begin(), out_data.end(), data.begin());
}

void calculateWithPPL1(matrix& data)
{
    //testCalculator(data);
    matrix out_data(data);
    calculateWithPPL1(&data, it);
    std::move(out_data.begin(), out_data.end(), data.begin());
}
//
//void calculateWithPPL2(matrix& data)
//{
//    //testCalculator(data);
//    matrix out_data(data);
//    calculateWithPPL2(&data, &out_data, it);
//    std::move(out_data.begin(), out_data.end(), data.begin());
//}
//
//void calculateWithPPL12(matrix& data)
//{
//    //testCalculator(data);
//    matrix out_data(data);
//    calculateWithPPL12(&data, &out_data, it);
//    std::move(out_data.begin(), out_data.end(), data.begin());
//}

matrix genarateMatrix(size_t i, size_t j)
{
    matrix result(i, std::vector<double>(j));
    for (size_t t = 0; t < i; t++)
    {
        std::vector<float> v(j);
        std::generate(v.begin(), v.end(), std::rand);
        std::copy(v.begin(), v.end(), result[t].begin());
    }
    return result;
}

int main()
{
    int i = 30;
    int j = 20000;
    lambda.resize(i);
    std::generate(lambda.begin(), lambda.end(), std::rand);
    
    {
        std::vector<std::vector<double>> values = genarateMatrix(i, j);// { { 1, 1 }, { 2, 2 } };
        auto start_t = GetTickCount64();
        calculateWithOut(values);
        auto end_t = GetTickCount64();
        std::cout << "without:" << end_t - start_t << std::endl;
    }

    {
        std::vector<std::vector<double>> values = genarateMatrix(i, j);//{ { 1,1 },{ 2, 2 } };
        auto start_t = GetTickCount64();
        calculateWithPPL1(values);
        auto end_t = GetTickCount64();
        std::cout << "withPPL1:" << end_t - start_t << std::endl;
    }

    //{
    //    std::vector<std::vector<float>> values = genarateMatrix(i, j);//{ { 1,1 },{ 2, 2 } };
    //    auto start_t = GetTickCount64();
    //    calculateWithPPL1(values);
    //    auto end_t = GetTickCount64();
    //    std::cout << "withPPL2:" << end_t - start_t << std::endl;
    //}

    //{
    //    std::vector<std::vector<float>> values = genarateMatrix(i, j);//{ { 1,1 },{ 2, 2 } };
    //    auto start_t = GetTickCount64();
    //    calculateWithPPL12(values);
    //    auto end_t = GetTickCount64();
    //    std::cout << "withPPL12:" << end_t - start_t << std::endl;
    //}
    //system("pause");
    return 0;
}

