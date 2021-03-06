// onGPU.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "onGPU.h"

void testCalculator(matrix& data)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        for (size_t j = 0; j < data[i].size(); j++)
        {
            data[i][j] *= 2.0;
        }
    }
}



void calculateWithOutAccelerate(matrix* in_data, matrix* out_data, int count)
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
            for (size_t j = 0; j < j_count; j++)
            {
                (*out_data)[i][j] = (*in_data)[i][j] * 2.0;
            }
        }
        temp = out_data;
        out_data = in_data;
        in_data = temp;
    }
    out_data = temp;
}

void onGPU::calculate(matrix& data)
{
    //testCalculator(data);
    matrix out_data(data);
    calculateWithOutAccelerate(&data, &out_data, 3);
    std::move(out_data.begin(), out_data.end(), data.begin());
}


