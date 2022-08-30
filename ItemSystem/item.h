#pragma once
#include "pch.h"
/**** Equipment Layers:
	headwear:
	0: head				[1]
	0: eyes				[1]
	0: mask				[1]
	neckwear:
	0: neck				[1]
	tops:
	0: short underwear	[1]
	1: long underwear	[2]
	2: tops				[2]
	3: outerwear		[1]
	4: cloak			[1]
	5: sheath\quiver	[2]
	5: backpack			[1]
	trousers:
	0: short underwear	[1]
	1: long underwear	[2]
	2: paints			[2]
	3: outerwear		[1]		// typically plate armor
	footwear:
	0: shoes			[1]
	wrist:
	0: wrist			[1]
	hands:
	0: gloves			[1]
	0: rings			[2]
	1: outerwear		[1]		// typically plate armor
	2: brass knuckles	[1]
	3: weapon			[2]
	accessory:
	0: accessory		[2]
*/
/*
	****** Greate Sword ******
	* part:					hand
	* layer:				3
	* length:				1500 mm
	* weight:				2000000 mg
	* size:					[5,2]
	* max stack:			1
	* -----------------------------------
	* structure:			double-handed double-edged straight sword
	* attack mode:			cut forward/cut backward/thrust/throw
	* center of mass:		<100, 0, 0>
	* sharpness:			3000/3000 - 1000/1000 - 1000/1000
	* -----------------------------------
	* blade length:			1000 mm
	* blade width:			40 mm
	* blade thickness:		5 mm
	* blade material:		steel
	* density:				8 mg/mm^3
	* hardness:				600/600
	* ductility:			0/100
	* -----------------------------------

	****** Tactical Pants ******
	* part:					trousers
	* layer:				2
	* weight:				400000 mg
	* size:					[2,3]
	* max stack:			1
	* -----------------------------------
	* strap:				belt[1,2]
	* mounts:				slot[2,1], slot[2,1]
	* pockets:				fleft[1,2], fright[1,2], bleft[1,2], bright[1,2]
	* material:				polyester
	* hardness:				30/30
	* thermal insulation:	20/20
	* -----------------------------------

	****** Adhesive Bandage ******
	* weight:				1000 mg
	* size:					[1,1]
	* max stack:			99
	* -----------------------------------
	* recovery:				4/sec

	****** Pork ******
	* weight:				100000 mg
	* size:					[1,1]
	* max stack:			5
	* freshness:			100/100
	* -----------------------------------
	* energy:				1000 / 100
	* water:				50 / 100
	* fat:					30 / 100
	* protein:				15 / 100
	* phosphorus:			250 / 100000
	* potassium:			400 / 100000
	* sodium:				60 / 100000
	* calcium:				20 / 100000
	* zinc:					3 / 100000
	* -----------------------------------
*/
