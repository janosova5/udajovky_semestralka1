#include <stdexcept>
#include <string>


#include "DSRoutines.h"

using namespace DS;

DSRoutines::DSRoutines()
{
}

StructureADT DSRoutines::convertADStoADT(const StructureADS& ads)
{
	switch (ads)
	{
	case adsVECTOR:
		return adtVECTOR;

	case adsARRAY:
		return adtARRAY;

	case adsLIST_ARRAY:
	case adsLIST_LINKED:
	case adsLIST_DOUBLE_LINKED:
	case adsLIST_CYCLICAL:
		return adtLIST;

	case adsQUEUE_ARRAY:
	case adsQUEUE_LIST:
		return adtQUEUE;

	case adsSTACK_ARRAY:
	case adsSTACK_LIST:
		return adtSTACK;

	case adsPRIORITY_QUEUE_ARRAY:
	case adsPRIORITY_QUEUE_LIST:
	case adsPRIORITY_QUEUE_TWO_LISTS:
	case adsPRIORITY_QUEUE_DOUBLE_LAYER:
	case adsPRIORITY_QUEUE_HEAP:
		return adtPRIORITY_QUEUE;

	case adsTREE:
		return adtTREE;

	case adsGRAPH_MATRIX:
	case adsGRAPH_STAR:
		return adtGRAPH;

	case adsTABLE_SEQUENCE_SORTED:
	case adsTABLE_SEQUENCE_NONSORTED:
	case adsTABLE_LINKED:
	case adsTABLE_DIAMOND:
	case adsTABLE_HASH:
	case adsTABLE_BST:
	case adsTABLE_TREAP:
		return adtTABLE;

	default:
		throw std::invalid_argument("Can not convert ADS to ADT");
	}
}

bool DSRoutines::rangeCheck(const int index, const size_t size, bool throwException, const std::string* message)
{
	if (index >= 0 && (size_t)index < size)
		return true;
	else if (throwException)
		throw std::out_of_range(*message);
	else
		return false;
}
