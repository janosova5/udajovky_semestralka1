#pragma once

namespace DS {

	enum StructureADT {
		adtVECTOR,
		adtARRAY,
		adtLIST,
		adtQUEUE,
		adtSTACK,
		adtPRIORITY_QUEUE,
		adtTREE,
		adtGRAPH,
		adtTABLE,
		adtCount,
	};

	/*
	Kazdu dalsiu konstantu treba pridat do DSRoutines (konverzia na ADT) a do Routines (Meno)
	*/
	enum StructureADS {
		adsVECTOR,
		adsARRAY,

		adsLIST_ARRAY,
		adsLIST_LINKED,
		adsLIST_DOUBLE_LINKED,
		adsLIST_CYCLICAL,

		adsQUEUE_ARRAY,
		adsQUEUE_LIST,

		adsSTACK_ARRAY,
		adsSTACK_LIST,

		adsPRIORITY_QUEUE_ARRAY,
		adsPRIORITY_QUEUE_LIST,
		adsPRIORITY_QUEUE_TWO_LISTS,
		adsPRIORITY_QUEUE_DOUBLE_LAYER,
		adsPRIORITY_QUEUE_HEAP,

		adsTREE,

		adsGRAPH_MATRIX,
		adsGRAPH_STAR,

		adsTABLE_SEQUENCE_SORTED,
		adsTABLE_SEQUENCE_NONSORTED,
		adsTABLE_LINKED,
		adsTABLE_DIAMOND,
		adsTABLE_HASH,
		adsTABLE_BST,
		adsTABLE_TREAP,

		adsCount
	};

}
