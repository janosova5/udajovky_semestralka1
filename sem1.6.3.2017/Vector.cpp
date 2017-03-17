#include "Vector.h"

using namespace DS;
#include <cstdlib>
#include <cstring>
#include "DSRoutines.h"
Vector::Vector(size_t size)
{
	size_ = size;
	memory_ = calloc(size, 1);
}

Vector::Vector(const Vector& other) : Vector(other.size())
{

	memcpy(memory_, other.memory_, other.size_);
}

Vector::~Vector()
{
	free(memory_);
	memory_ = nullptr;
	size_ = 0;
}

Structure* Vector::clone() const
{
	return	new Vector(*this);
}

Structure & Vector::operator=(const Structure & other)
{
	*this = dynamic_cast<const Vector&>(other);
	return *this;
}

Vector& Vector::operator=(const Vector& other)
{
	if (this != &other) {
		size_ = other.size_;
		memory_ = realloc(memory_, other.size_);
		memcpy(memory_, other.memory_, other.size_);
		return *this;
	}
	else {
		return *this;
	}

}

bool Vector::operator==(const Vector& other) const
{
	return  size_ == other.size_ && memcmp(memory_, other.memory_, size_) == 0;
}

size_t Vector::size() const
{
	return size_;
}

byte& Vector::operator[](const int index)
{
	DSRoutines::rangeCheck(index, size_, true);
	return *(reinterpret_cast<byte*>(memory_) + index);
}

byte Vector::operator[](const int index) const
{
	DSRoutines::rangeCheck(index, size_, true);
	return *(reinterpret_cast<byte*>(memory_) + index);
}

bool Vector::byteNthBitGet(int B, int n)
{
	DSRoutines::rangeCheck(B, size_, true);
	DSRoutines::rangeCheck(n, 8, true);
	return  ((*this)[B] >> n) & 1;
}

byte Vector::byteNthBitTo0(int B, int n)
{
	DSRoutines::rangeCheck(B, size_, true);
	DSRoutines::rangeCheck(n, 8, true);
	return (*this)[B] &= ~(1 << n);
}

byte Vector::byteNthBitTo1(int B, int n)
{
	DSRoutines::rangeCheck(B, size_, true);
	DSRoutines::rangeCheck(n, 8, true);
	return (*this)[B] |= (1 << n);
}

byte Vector::byteNthBitToggle(int B, int n)
{
	DSRoutines::rangeCheck(B, size_, true);
	DSRoutines::rangeCheck(n, 8, true);
	return (*this)[B] ^= (1 << n);
}

byte& Vector::readBytes(const int index, const int count, byte& dest)
{
	DSRoutines::rangeCheck(index, size_, true);
	DSRoutines::rangeCheck(count, size_ + 1, true);
	DSRoutines::rangeCheck(index + count - 1, size_, true);
	memcpy(&dest, reinterpret_cast<byte*>(memory_) + index, count);
	return dest;
}

void DS::Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
{
	if (length == 0)
		return;
	DSRoutines::rangeCheck(srcStartIndex, src.size_, true);
	DSRoutines::rangeCheck(destStartIndex, dest.size_, true);
	DSRoutines::rangeCheck(length, dest.size_ + 1, true);
	DSRoutines::rangeCheck(destStartIndex + length, dest.size_ + 1, true);
	DSRoutines::rangeCheck(srcStartIndex + length, src.size_ + 1, true);
	if (&src != &dest) {

		memcpy(reinterpret_cast<byte*> (dest.memory_) + destStartIndex, reinterpret_cast<byte*>(src.memory_) + srcStartIndex, length);
	}
	else {
		memmove(reinterpret_cast<byte*> (dest.memory_) + destStartIndex, reinterpret_cast<byte*>(src.memory_) + srcStartIndex, length);
	}
}

byte* DS::Vector::getByteAddress(const int index)
{
	DSRoutines::rangeCheck(index, size_, true);
	return reinterpret_cast<byte*> (memory_) + index;
}
