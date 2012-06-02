-- fix buycount of honour goods
UPDATE `item_template` SET `BuyCount`=20 WHERE (`entry`=52185);
UPDATE `item_template` SET `BuyCount`=20 WHERE (`entry`=53010);
UPDATE `item_template` SET `BuyCount`=5 WHERE (`entry`=52976);