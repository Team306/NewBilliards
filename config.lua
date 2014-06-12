-- Copyright (C) 2014 Team306
-- config file using Lua

configTable = {
	-- eight ball
	{
		["ballRadius"] = 21,
		cueBall = { 240, 360, 195, 195, 195 },
		
		-- ["ballsNumber"] = 15,
		-- ballsList = {
		-- 	-- each line is X Y and R G B and ballname
		-- 	{ 880, 340, 243, 199, 1, "one" },
		-- 	{ 989.5, 361.5, 52, 46, 227, "two" },
		-- 	{ 1026, 426, 220, 7, 7, "three" },
		-- 	{ 1026, 340, 156, 67, 179, "four" },
		-- 	{ 1026, 255, 250, 146, 8, "five" },
		-- 	{ 953, 297, 36, 118, 5, "six" },
		-- 	{ 916.5, 361.5, 133, 65, 37, "seven" },
		-- 	{ 953, 340, 0, 0, 0, "eight" },
		-- 	{ 916.5, 318.5, 255, 252, 180, "nine" },
		-- 	{ 953, 383, 255, 252, 200, "ten" },
		-- 	{ 1026, 383, 255, 252, 210, "eleven" },
		-- 	{ 989.5, 404.5, 255, 252, 220, "twelve" },
		-- 	{ 989.5, 276.5, 255, 252, 230, "thirteen" },
		-- 	{ 989.5, 318.5, 255, 252, 240, "fourteen" },
		-- 	{ 1026, 297, 255, 252, 250, "fifteen" },
		-- },

		-- using in test
		["ballsNumber"] = 4,
		ballsList = {
			-- each line is X Y and R G B and ballname
			{ 90, 90, 243, 199, 1, "one" },
			{ 1190, 590, 52, 46, 227, "two" },
			{ 90, 590, 0, 0, 0, "eight" },
			{ 1190, 90, 255, 252, 250, "fifteen" },
		},
	},
	-- nine ball
	{
		["ballRadius"] = 21, 
		cueBall = { 240, 360, 195, 195, 195 },
		["ballsNumber"] = 9,
		ballsList = {
			-- each line is X Y and R G B and ballname
			{ 880, 340, 243, 199, 1, "one" },
			{ 989.5, 361.5, 52, 46, 227, "two" },
			{ 953, 383, 220, 7, 7, "three" },
			{ 916.5, 318.5, 156, 67, 179, "four" },
			{ 989.5, 318.5, 250, 146, 8, "five" },
			{ 953, 297, 36, 118, 5, "six" },
			{ 916.5, 361.5, 133, 65, 37, "seven" },
			{ 1026, 340, 0, 0, 0, "eight" },
			{ 953, 340, 255, 252, 180, "nine" },
		},
	},
	-- snooker
	{
		["ballRadius"] = 23.44,
		cueBall = { 240, 360, 195, 195, 195 },
		["ballsNumber"] = 12,
		ballsList = {
			-- each line is X Y and R G B and ballname
			{ 900, 360, 243, 199, 1, "one" },
			{ 940.6, 383.5, 36, 118, 5, "two" },
			{ 940.6, 336.5, 52, 46, 227, "three" },
			{ 981.2, 407, 156, 67, 179, "four" },
			{ 1021.8, 383.5, 220, 7, 7, "five" },
			{ 981.2, 313, 250, 146, 8, "six" },
			{ 1021.8, 430.5, 133, 65, 37, "seven" },
			{ 981.2, 360, 0, 0, 0, "eight" },
			{ 1021.8, 336.5, 255, 252, 180, "nine" },
			{ 1021.8, 289.5, 255, 252, 200, "ten" },
			{ 1062.4, 454, 255, 252, 210, "eleven" },
			{ 1062.4, 407, 255, 252, 220, "twelve" },
		},
	},
}

function getConfigData( gameRule, key, index )
	if gameRule >= 1 or gameRule <= 3 then
		if key == "ballRadius" or key == "ballsNumber" then
			return configTable[gameRule][key]
		end
		if key == "cueBall" then
			return configTable[gameRule][key][1], configTable[gameRule][key][2], configTable[gameRule][key][3], configTable[gameRule][key][4], configTable[gameRule][key][5]
		end
		if key == "ballsList" then
			return configTable[gameRule]["ballsList"][index][1], configTable[gameRule]["ballsList"][index][2], configTable[gameRule]["ballsList"][index][3], configTable[gameRule]["ballsList"][index][4], configTable[gameRule]["ballsList"][index][5], configTable[gameRule]["ballsList"][index][6]
		end
	end
end
