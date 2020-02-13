#ifndef _Tokens_h_
#define _Tokens_h_

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define TOKEN_SEQ_1                             \
    (Abs)                                       \
    (AccountingLabel)                           \
    (Activation)                                \
    (AddedBefore)                               \
    (AddedSince)                                \
    (AddSpecial)                                \
    (AddStarlanes)                              \
    (Adequate)                                  \
    (Affiliation)                               \
    (Age)                                       \
    (Aggressive)                                \
    (All)                                       \
    (Allowed)                                   \
    (AllyOf)                                    \
    (And)                                       \
    (AnyEmpire)                                 \
    (Armed)                                     \
    (Armour)                                    \
    (ArrivedOnTurn)                             \
    (Article)                                   \
    (Application)                               \
    (Asteroids)                                 \
    (Attack)                                    \
    (Barren)                                    \
    (Basic)                                     \
    (BlackHole)                                 \
    (Blue)                                      \
    (Bombard)                                   \
    (Bomber)                                    \
    (BuildCost)

#define TOKEN_SEQ_2                             \
    (Building)                                  \
    (BuildingTypesOwned)                        \
    (BuildingType)                              \
    (BuildingTypesProduced)                     \
    (BuildingTypesScrapped)                     \
    (BuildTime)                                 \
    (CanAddStarlanesTo)                         \
    (CanColonize)                               \
    (CanProduceShips)                           \
    (CanSee)                                    \
    (Capacity)                                  \
    (Capital)                                   \
    (Capture)                                   \
    (CaptureResult)                             \
    (Category)                                  \
    (Ceil)                                      \
    (Class)                                     \
    (ClockwiseNextPlanetType)                   \
    (Colony)                                    \
    (Colour)                                    \
    (CombatBout)                                \
    (CombatTargets)                             \
    (Condition)                                 \
    (Construction)                              \
    (Consumption)                               \
    (ContainedBy)                               \
    (Contains)                                  \
    (Core)                                      \
    (Cos)                                       \
    (Count)                                     \
    (CountUnique)                               \
    (CounterClockwiseNextPlanetType)            \
    (CreateBuilding)                            \
    (CreatedOnTurn)                             \
    (CreateField)                               \
    (CreatePlanet)                              \
    (CreateShip)                                \
    (CreateSystem)                              \
    (CreationTurn)                              \
    (CurrentContent)                            \
    (CurrentTurn)

#define TOKEN_SEQ_3                             \
    (Damage)                                    \
    (Data)                                      \
    (Default)                                   \
    (Defense)                                   \
    (Described)                                 \
    (Description)                               \
    (Desert)                                    \
    (Design)                                    \
    (DesignHasHull)                             \
    (DesignHasPart)                             \
    (DesignHasPartClass)                        \
    (DesignID)                                  \
    (DesignName)                                \
    (Destination)                               \
    (Destroy)                                   \
    (Detection)                                 \
    (DirectDistanceBetween)                     \
    (Disabled)                                  \
    (Distance)                                  \
    (DistanceFromOriginalType)                  \
    (Effects)                                   \
    (EffectsGroup)                              \
    (EffectsGroups)                             \
    (Else)                                      \
    (Empire)                                    \
    (EmpireHasBuildingAvailable)                \
    (EmpireHasShipDesignAvailable)              \
    (EmpireHasShipPartAvailable)                \
    (EmpireHasTechResearched)                   \
    (EmpireMeter)                               \
    (EmpireMeterValue)                          \
    (EmpireObjectVisibility)                    \
    (EmpireShipsDestroyed)                      \
    (EmpireStockpile)                           \
    (Enabled)                                   \
    (Endpoint)                                  \
    (EnemyOf)                                   \
    (Enqueued)                                  \
    (EnqueueLocation)                           \
    (Environment)                               \
    (Environments)                              \
    (ETA)                                       \
    (ExploredByEmpire)                          \
    (Exclusions)                                \
    (External)

#define TOKEN_SEQ_4                             \
    (Field)                                     \
    (FieldType)                                 \
    (Fighter)                                   \
    (FighterBay)                                \
    (FighterHangar)                             \
    (FighterWeapon)                             \
    (FinalDestinationID)                        \
    (Fleet)                                     \
    (FleetID)                                   \
    (FleetSupplyableByEmpire)                   \
    (Floor)                                     \
    (Foci)                                      \
    (Focus)                                     \
    (FocusType)                                 \
    (Fuel)                                      \
    (Full)                                      \
    (GalaxyAge)                                 \
    (GalaxyMaxAIAggression)                     \
    (GalaxyMonsterFrequency)                    \
    (GalaxyNativeFrequency)                     \
    (GalaxyPlanetDensity)                       \
    (GalaxySeed)                                \
    (GalaxyShape)                               \
    (GalaxySize)                                \
    (GalaxySpecialFrequency)                    \
    (GalaxyStarlaneFrequency)                   \
    (Gameplay_Description)                      \
    (GameRule)                                  \
    (GasGiant)                                  \
    (General)

#define TOKEN_SEQ_5                             \
    (GenerateSitrepMessage)                     \
    (GiveEmpireTech)                            \
    (Good)                                      \
    (Graphic)                                   \
    (HabitableSize)                             \
    (Happiness)                                 \
    (HasSpecial)                                \
    (HasSpecialCapacity)                        \
    (HasSpecialSinceTurn)                       \
    (HasTag)                                    \
    (High)                                      \
    (HighestCostEnqueuedTech)                   \
    (HighestCostResearchableTech)               \
    (HighestCostTransferrableTech)              \
    (Homeworld)                                 \
    (Hostile)                                   \
    (Huge)                                      \
    (Hull)                                      \
    (HullFuel)                                  \
    (HullSpeed)                                 \
    (HullStealth)                               \
    (HullStructure)                             \
    (HullType)                                  \
    (Human)                                     \
    (Icon)                                      \
    (ID)                                        \
    (If)                                        \
    (Industry)                                  \
    (Inferno)                                   \
    (InSystem)                                  \
    (Interceptor)                               \
    (Integer)                                   \
    (Internal)                                  \
    (Invisible)                                 \
    (Item)                                      \
    (Jumps)                                     \
    (JumpsBetween)                              \
    (Keymap)                                    \
    (Keys)

#define TOKEN_SEQ_6                             \
    (Label)                                     \
    (Large)                                     \
    (LastTurnActiveInBattle)                    \
    (LastTurnAttackedByShip)                    \
    (LastTurnBattleHere)                        \
    (LastTurnConquered)                         \
    (LastTurnResupplied)                        \
    (LaunchedFrom)                              \
    (LeastHappySpecies)                         \
    (LocalCandidate)                            \
    (Location)                                  \
    (Log)                                       \
    (Low)                                       \
    (LowestCostEnqueuedTech)                    \
    (LowestCostResearchableTech)                \
    (LowestCostTransferrableTech)               \
    (Max)                                       \
    (MaxCapacity)                               \
    (MaxDamage)                                 \
    (MaxDefense)                                \
    (MaxFuel)                                   \
    (MaximumNumberOf)                           \
    (MaxSecondaryStat)                          \
    (MaxShield)                                 \
    (MaxStockpile)                              \
    (MaxStructure)                              \
    (MaxSupply)                                 \
    (MaxTroops)                                 \
    (Mean)                                      \
    (Medium)                                    \
    (Message)                                   \
    (Meter)                                     \
    (Min)                                       \
    (MinimumNumberOf)                           \
    (Missiles)

#define TOKEN_SEQ_7                             \
    (Mode)                                      \
    (Model)                                     \
    (ModeNumberOf)                              \
    (Monster)                                   \
    (MonsterFleet)                              \
    (MostHappySpecies)                          \
    (MostPopulousSpecies)                       \
    (MostSpentEnqueuedTech)                     \
    (MostSpentResearchableTech)                 \
    (MostSpentTransferrableTech)                \
    (MountableSlotTypes)                        \
    (MoveInOrbit)                               \
    (MoveTo)                                    \
    (MoveTowards)                               \
    (Name)                                      \
    (Native)                                    \
    (NearestSystemID)                           \
    (Neutron)                                   \
    (NextBetterPlanetType)                      \
    (NextCloserToOriginalPlanetType)            \
    (NextLargerPlanetSize)                      \
    (NextSmallerPlanetSize)                     \
    (NextOlderStarType)                         \
    (NextSystemID)                              \
    (NextTurnPopGrowth)                         \
    (NextYoungerStarType)                       \
    (NoDefaultCapacityEffect)                   \
    (None)                                      \
    (NoOp)                                      \
    (NoStar)                                    \
    (NoStringtableLookup)                       \
    (Not)                                       \
    (Number)                                    \
    (NumberOf)                                  \
    (NumShips)                                  \
    (NumStarlanes)                              \

#define TOKEN_SEQ_8                             \
    (Object)                                    \
    (ObjectType)                                \
    (Ocean)                                     \
    (Off)                                       \
    (On)                                        \
    (OneOf)                                     \
    (Opinion)                                   \
    (Or)                                        \
    (Orange)                                    \
    (Orbit)                                     \
    (OrderedBombardedBy)                        \
    (OriginalType)                              \
    (OutpostsOwned)                             \
    (OwnedBy)                                   \
    (Owner)                                     \
    (OwnerHasShipPartAvailable)                 \
    (OwnerHasTech)                              \
    (Parameters)                                \
    (Part)                                      \
    (PartCapacity)                              \
    (PartClass)                                 \
    (PartDamage)                                \
    (Partial)                                   \
    (PartName)                                  \
    (PartSecondaryStat)

#define TOKEN_SEQ_9                             \
    (Parts)                                     \
    (PartOfClassInShipDesign)                   \
    (PartsInShipDesign)                         \
    (PartType)                                  \
    (Passive)                                   \
    (PeaceWith)                                 \
    (Planet)                                    \
    (Planetbound)                               \
    (PlanetEnvironment)                         \
    (PlanetID)                                  \
    (PlanetSize)                                \
    (PlanetType)                                \
    (Playable)                                  \
    (PointDefense)                              \
    (Poor)                                      \
    (Population)                                \
    (PopulationCenter)                          \
    (Position)                                  \
    (PreferredFocus)                            \
    (Prerequisites)                             \
    (PreviousSystemID)                          \
    (Priority)                                  \
    (Probability)                               \
    (ProducedByEmpire)                          \
    (ProducedByEmpireID)                        \
    (Producible)                                \
    (Product)                                   \
    (ProductionCenter)                          \
    (ProductionLocation)                        \
    (PropagatedSupplyRange)                     \
    (Property)                                  \
    (Progress)

#define TOKEN_SEQ_10                            \
    (Radiated)                                  \
    (Radius)                                    \
    (Random)                                    \
    (RandomColonizableSpecies)                  \
    (RandomCompleteTech)                        \
    (RandomControlledSpecies)                   \
    (RandomEnqueuedTech)                        \
    (RandomResearchableTech)                    \
    (RandomTransferrableTech)                   \
    (RandomNumber)                              \
    (Range)                                     \
    (Real)                                      \
    (Reason)                                    \
    (RebelTroops)                               \
    (Red)                                       \
    (Refinement)                                \
    (RemoveSpecial)                             \
    (RemoveStarlanes)                           \
    (Research)                                  \
    (Researchable)                              \
    (ResearchCost)                              \
    (ResearchTurns)                             \
    (ResourceSupplyConnected)                   \
    (ResupplyableBy)                            \
    (Retain)                                    \
    (RMS)                                       \
    (RootCandidate)                             \
    (Round)                                     \
    (Scope)                                     \
    (SecondaryStat)

#define TOKEN_SEQ_11                            \
    (SetAggressive)                             \
    (SetCapacity)                               \
    (SetConstruction)                           \
    (SetDamage)                                 \
    (SetDefense)                                \
    (SetDestination)                            \
    (SetDetection)                              \
    (SetEmpireCapital)                          \
    (SetEmpireMeter)                            \
    (SetEmpireTechProgress)                     \
    (SetEmpireStockpile)                        \
    (SetFuel)                                   \
    (SetHappiness)                              \
    (SetIndustry)                               \
    (SetMaxCapacity)                            \
    (SetMaxDamage)                              \
    (SetMaxDefense)                             \
    (SetMaxFuel)                                \
    (SetMaxSecondaryStat)                       \
    (SetMaxShield)                              \
    (SetMaxStockpile)                           \
    (SetMaxStructure)                           \
    (SetMaxSupply)                              \
    (SetMaxTroops)                              \
    (SetOverlayTexture)                         \
    (SetOwner)                                  \
    (SetPassive)                                \
    (SetPlanetSize)                             \
    (SetPlanetType)                             \
    (SetPopulation)

#define TOKEN_SEQ_12                            \
    (SetRange)                                  \
    (SetRebelTroops)                            \
    (SetResearch)                               \
    (SetSecondaryStat)                          \
    (SetShield)                                 \
    (SetSize)                                   \
    (SetSpecialCapacity)                        \
    (SetSpecies)                                \
    (SetSpeciesOpinion)                         \
    (SetSpeed)                                  \
    (SetStarType)                               \
    (SetStealth)                                \
    (SetStockpile)                              \
    (SetStructure)                              \
    (SetSupply)                                 \
    (SetTargetConstruction)                     \
    (SetTargetHappiness)                        \
    (SetTargetIndustry)                         \
    (SetTargetPopulation)                       \
    (SetTargetResearch)                         \
    (SetTargetTrade)                            \
    (SetTexture)                                \
    (SetTrade)                                  \
    (SetTroops)                                 \
    (SetVisibility)

#define TOKEN_SEQ_13                            \
    (Shield)                                    \
    (ShipDesign)                                \
    (ShipDesignCost)                            \
    (ShipDesignOrdering)                        \
    (ShipDesignsDestroyed)                      \
    (ShipDesignsInProduction)                   \
    (ShipDesignsLost)                           \
    (ShipDesignsOwned)                          \
    (ShipDesignsProduced)                       \
    (ShipDesignsScrapped)                       \
    (Ship)                                      \
    (ShipHull)                                  \
    (ShipPart)                                  \
    (ShipPartMeter)                             \
    (ShipPartsOwned)                            \
    (Ships)                                     \
    (Short_Description)                         \
    (ShortestPath)                              \
    (ShortRange)                                \
    (Shots)                                     \
    (Sin)                                       \
    (Size)                                      \
    (SizeAsDouble)

#define TOKEN_SEQ_14                            \
    (Slot)                                      \
    (Slots)                                     \
    (SlotsInHull)                               \
    (SlotsInShipDesign)                         \
    (SlotType)                                  \
    (Small)                                     \
    (SortBy)                                    \
    (SortKey)                                   \
    (Source)                                    \
    (Spacebound)                                \
    (SpawnLimit)                                \
    (SpawnRate)                                 \
    (Special)                                   \
    (SpecialAddedOnTurn)                        \
    (SpecialCapacity)                           \
    (Species)                                   \
    (SpeciesID)                                 \
    (SpeciesCensusOrdering)                     \
    (SpeciesOpinion)                            \
    (SpeciesPlanetsBombed)                      \
    (SpeciesColoniesOwned)

#define TOKEN_SEQ_15                            \
    (SpeciesPlanetsDepoped)                     \
    (SpeciesPlanetsInvaded)                     \
    (SpeciesShipsDestroyed)                     \
    (SpeciesShipsLost)                          \
    (SpeciesShipsOwned)                         \
    (SpeciesShipsProduced)                      \
    (SpeciesShipsScrapped)                      \
    (Speed)                                     \
    (Spread)                                    \
    (StackingGroup)                             \
    (Star)                                      \
    (StarType)                                  \
    (Stationary)                                \
    (Statistic)                                 \
    (StDev)                                     \
    (Stealth)                                   \
    (Stockpile)                                 \
    (String)                                    \
    (StringList)                                \
    (Structure)                                 \
    (Sum)                                       \
    (Supply)                                    \
    (SupplyingEmpire)                           \
    (Swamp)                                     \
    (System)                                    \
    (SystemID)

#define TOKEN_SEQ_16                            \
    (Tag)                                       \
    (Tags)                                      \
    (Target)                                    \
    (TargetConstruction)                        \
    (TargetHappiness)                           \
    (TargetIndustry)                            \
    (TargetPopulation)                          \
    (TargetResearch)                            \
    (TargetTrade)                               \
    (Tech)                                      \
    (Terran)                                    \
    (TestValue)                                 \
    (TheEmpire)                                 \
    (Theory)                                    \
    (ThisBuilding)                              \
    (ThisField)                                 \
    (ThisHull)                                  \
    (ThisPart)                                  \
    (ThisTech)                                  \
    (ThisSpecies)                               \
    (ThisSpecial)                               \
    (Tiny)                                      \
    (Toggle)                                    \
    (TopPriorityEnqueuedTech)                   \
    (TopPriorityResearchableTech)               \
    (TopPriorityTransferrableTech)              \
    (OrderedAlternativesOf)                     \
    (Toxic)                                     \
    (Trade)

#define TOKEN_SEQ_17                            \
    (Troops)                                    \
    (Tundra)                                    \
    (Turn)                                      \
    (TurnsSinceFocusChange)                     \
    (TurnTechResearched)                        \
    (Type)                                      \
    (Uninhabitable)                             \
    (UniverseCentreX)                           \
    (UniverseCentreY)                           \
    (UniverseWidth)                             \
    (Unlock)                                    \
    (Unowned)                                   \
    (Unproducible)                              \
    (Unresearchable)                            \
    (UpgradeVisibility)                         \
    (UsedInDesignID)                            \
    (UserString)                                \
    (UUID)                                      \
    (Value)                                     \
    (Victory)                                   \
    (VisibleToEmpire)                           \
    (Visibility)                                \
    (White)                                     \
    (WithinDistance)                            \
    (WithinStarlaneJumps)                       \
    (X)                                         \
    (Y)                                         \
    (Yellow)

#endif
