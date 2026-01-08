# Additional notes for any future developers
### Version 1 from Goatzy

<hr>

# 1. Source code and Player

## Player code is mostly in *`BuildToSurviveCharacter`* cpp class, not in any of the variant specifics and from the content browser, all character related stuff you'll find there, such as the gamemode and the player character blueprint, which is called *`BP_Character`*, where you can also access the cpp functions from.

# 2. Wave System

## I made a pretty easy to use cpp system to manage waves of enemies. All BP classes needed are in *`/WaveSystem_BP/`*, where there is only *`SpawnPoint_BP`* and *`WaveManager_BP`*. When you open up WaveManager_BP, under class defaults you can set all the data for how the system should behave. First of all, it will spawn the enemies on top of *`SpawnPoint_BP`* blueprints that are placed onto the level, and you can also set the behaviour for each wave, like what enemy blueprint it'll spawn, how many enemies that you'll have to kill and spawn interval in seconds, meaning how long from last spawn to spawn another enemy until all the enemies are spawned. That's mostly it though.

# 3. Inventory System

## All items will have to be defined as Data Asset blueprints and as the Data Asset parent being *`Item Defintion`* and you can just use all the functions provided on the Actor Component on the BP_Character, it has a lot of helper functions that you can use. Make sure to update the invetory UI after each time you add an item.


<hr>

# Current Issues

## 1. **Enemies** -- Enemies won't move or anything else when spawned from the WaveManager_BP. I know the usual suspect is that it's set to only be placed into the world, because that's the only way it works at the moment, but I tried setting it to *`Placed or Spawned`* on ShooterNPC blueprint, but won't work.

<hr>
