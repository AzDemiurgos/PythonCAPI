#include "stdafx.h"
#include "CppUnitTest.h"
#include "../onGPU/onGPU.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace onGPU_Test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
            std::vector<std::vector<float>> values{ { 1,1 },{2, 2} };
            std::vector<std::vector<float>> test{ { 2,2 },{ 4, 4 } };
            onGPU::calculate(values);
            Assert::AreEqual(test[0][0], values[0][0]);
		}

	};
}