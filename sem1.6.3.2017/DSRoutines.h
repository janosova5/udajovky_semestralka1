#pragma once

#include <string>
#include "StructureID.h"

namespace DS
{
	class DSRoutines
	{
	public:
		static StructureADT convertADStoADT(const StructureADS& ads);

		static bool rangeCheck(const int index, const size_t size, const bool throwException = false, const std::string* message = nullptr);
		template<typename T>
		static void swap(T& a, T& b);
	private:
		DSRoutines();

	};

	template<typename T>
	inline void DSRoutines::swap(T & a, T & b)
	{
		T pom = a;
		a = b;
		b = pom;
	}

}


