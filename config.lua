-- Copyright (C) 2014 Team306
-- config file using Lua

configTable = {
	-- eight ball
	{
		["ballRadius"] = 19.2,
		cueBall = { 300, 300, 195, 195, 195 },
		
		["ballsNumber"] = 15,
		ballsList = {
			-- each line is X Y and R G B and ballname
			{ 820, 300, 243, 199, 1, "one" },
			{ 921.4, 319.5, 52, 46, 227, "two" },
			{ 955.2, 378, 220, 7, 7, "three" },
			{ 955.2, 300, 156, 67, 179, "four" },
			{ 955.2, 222, 250, 146, 8, "five" },
			{ 887.6, 261, 36, 118, 5, "six" },
			{ 853.8, 319.5, 133, 65, 37, "seven" },
			{ 887.6, 300, 0, 0, 0, "eight" },
			{ 853.8, 280.5, 255, 252, 180, "nine" },
			{ 887.6, 339, 255, 252, 200, "ten" },
			{ 955.2, 339, 255, 252, 210, "eleven" },
			{ 921.4, 358.5, 255, 252, 220, "twelve" },
			{ 921.4, 241.5, 255, 252, 230, "thirteen" },
			{ 921.4, 280.5, 255, 252, 240, "fourteen" },
			{ 955.2, 261, 255, 252, 250, "fifteen" },
		},

		-- using in test
		-- ["ballsNumber"] = 4,
		-- ballsList = {
		-- 	-- each line is X Y and R G B and ballname
		-- 	{ 90, 90, 243, 199, 1, "one" },
		-- 	{ 1030, 510, 52, 46, 227, "two" },
		-- 	{ 90, 510, 0, 0, 0, "eight" },
		-- 	{ 1030, 90, 255, 252, 250, "fifteen" },
		-- },
	},
	-- nine ball
	{
		["ballRadius"] = 19.2, 
		cueBall = { 300, 300, 195, 195, 195 },
		-- use 20 distance in calculating the position
		["ballsNumber"] = 9,
		ballsList = {
			-- each line is X Y and R G B and ballname
			{ 820, 300, 243, 199, 1, "one" },
			{ 921.4, 319.5, 52, 46, 227, "two" },
			{ 887.6, 339, 220, 7, 7, "three" },
			{ 853.8, 280.5, 156, 67, 179, "four" },
			{ 921.4, 280.5, 250, 146, 8, "five" },
			{ 887.6, 261, 36, 118, 5, "six" },
			{ 853.8, 319.5, 133, 65, 37, "seven" },
			{ 955.2, 300, 0, 0, 0, "eight" },
			{ 887.6, 300, 255, 252, 180, "nine" },
		},
		
		-- using in test
		-- ["ballsNumber"] = 4,
		-- ballsList = {
		-- 	-- each line is X Y and R G B and ballname
		-- 	{ 90, 90, 243, 199, 1, "one" },
		-- 	{ 820, 310, 52, 46, 227, "two" },
		-- 	{ 850, 290, 0, 0, 0, "eight" },
		-- 	{ 1030, 90, 255, 252, 250, "nine" },
		-- },
	},
	-- snooker, just use in test
	{
		["ballRadius"] = 20.3,
		cueBall = { 300, 300, 195, 195, 195 },
		
		-- ["ballsNumber"] = 12,
		-- ballsList = {
		-- 	-- each line is X Y and R G B and ballname
		-- 	{ 900, 360, 243, 199, 1, "one" },
		-- 	{ 940.6, 383.5, 36, 118, 5, "two" },
		-- 	{ 940.6, 336.5, 52, 46, 227, "three" },
		-- 	{ 981.2, 407, 156, 67, 179, "four" },
		-- 	{ 1021.8, 383.5, 220, 7, 7, "five" },
		-- 	{ 981.2, 313, 250, 146, 8, "six" },
		-- 	{ 1021.8, 430.5, 133, 65, 37, "seven" },
		-- 	{ 981.2, 360, 0, 0, 0, "eight" },
		-- 	{ 1021.8, 336.5, 255, 252, 180, "nine" },
		-- 	{ 1021.8, 289.5, 255, 252, 200, "ten" },
		-- 	{ 1062.4, 454, 255, 252, 210, "eleven" },
		-- 	{ 1062.4, 407, 255, 252, 220, "twelve" },
		-- },

		-- using in test
		["ballsNumber"] = 4,
		ballsList = {
			-- each line is X Y and R G B and ballname
			{ 90, 90, 243, 199, 1, "one" },
			{ 1030, 510, 52, 46, 227, "two" },
			{ 90, 510, 0, 0, 0, "eight" },
			{ 1030, 90, 255, 252, 250, "fifteen" },
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
