#ifndef _System_h_
#define _System_h_

#ifndef _UniverseObject_h_
#include "UniverseObject.h"
#endif

#include <map>

/** contains UniverseObjects and connections to other systems (starlanes and wormholes).  All systems are UniversObjects
   contained within the universe, and (nearly) all systems also contain UniverseObjects.  Systems are searchable using
   arbirary predicates, much in the same way that the Client- and ServerUniverses are.  Each System consists of a star
   and 0 or more orbits.  UniversObjects can be placed in the system "at large" or in a particular orbit.  No checking
   is done to determine whether an object is orbit-bound (like a Planet) or not (like a Fleet) when placing them with 
   the Insert() functions.  Iteration is available over all starlanes and wormholes (together), all system objects, 
   all free system objects (those not in an orbit), and all objects in a paricular orbit.*/
class System : public UniverseObject
{
private:
   typedef std::multimap<int, UniverseObject*>  ObjectMultimap;
   typedef std::map<int, bool>                  StarlaneMap;

public:
   /** types of stars in FreeOrion*/
   enum StarType {INVALID_STARTYPE = -1,  ///< the highest illegal StarType value
                  RED_DWARF, 
                  RED_GIANT, 
                  YELLOW,
                  NUM_STARTYPES           ///< the lowest illegal StarType value
                 }; // others TBD
      
   typedef std::vector<UniverseObject*>         ObjectVec;        ///< the return type of FindObjects()
   typedef std::vector<int>                     ObjectIDVec;      ///< the return type of FindObjectIDs()

   typedef ObjectMultimap::iterator       orbit_iterator;         ///< iterator for system objects
   typedef ObjectMultimap::const_iterator const_orbit_iterator;   ///< const_iterator for system objects
   typedef StarlaneMap::iterator          lane_iterator;          ///< iterator for starlanes and wormholes
   typedef StarlaneMap::const_iterator    const_lane_iterator;    ///< const_iterator for starlanes and wormholes

   /** \name Structors */ //@{
   System();    ///< default ctor

   /** general ctor.  \throw std::invalid_arugment May throw std::invalid_arugment if \a star is out of the range 
      of StarType, \a orbits is negative, or either x or y coordinate is outside the map area.*/
   System(StarType star, int orbits, const std::string& name, double x, double y, 
          const std::set<int>& owners = std::set<int>());

   /** general ctor.  \throw std::invalid_arugment May throw std::invalid_arugment if \a star is out of the range 
      of StarType, \a orbits is negative, or either x or y coordinate is outside the map area.*/
   System(StarType star, int orbits, const StarlaneMap& lanes_and_holes, 
          const std::string& name, double x, double y, const std::set<int>& owners = std::set<int>());
          
   System(const GG::XMLElement& elem); ///< ctor that constructs a System object from an XMLElement. \throw std::invalid_argument May throw std::invalid_argument if \a elem does not encode a System object
   ~System();   ///< dtor
   //@}

   /** \name Accessors */ //@{
   StarType Star() const   {return m_star;}  ///< returns the type of star for this system
   int      Orbits() const {return m_orbits;}///< returns the number of orbits in this system
   
   bool HasStarlaneTo(int id) const;         ///< returns true if there is a starlane from this system to the system with ID number \a id
   bool HasWormholeTo(int id) const;         ///< returns true if there is a wormhole from this system to the system with ID number \a id

   /** returns the IDs of all the objects that match \a pred.  Predicates used with this function must take a single const 
      UniverseObject* parameter and must return a bool or a type for which there is a conversion to bool.*/
   template <class Pred>
   ObjectIDVec FindObjectIDs(Pred pred)
   {
      ObjectIDVec retval;
      for (ObjectMultimap::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
         const UniverseObject* o = it->second;
         if (pred(o))
            retval.push_back(it->first);
      }
      return retval;
   }

   const_orbit_iterator begin() const  {return m_objects.begin();}   ///< begin iterator for all system objects
   const_orbit_iterator end() const    {return m_objects.end();}     ///< end iterator for all system objects

   /** returns begin and end iterators for all system objects in orbit \a o*/  
   std::pair<const_orbit_iterator, const_orbit_iterator> orbit_range(int o) const {return m_objects.equal_range(o);}

   /** returns begin and end iterators for all system objects not in an orbit*/  
   std::pair<const_orbit_iterator, const_orbit_iterator> non_orbit_range() const {return m_objects.equal_range(-1);}

   const_lane_iterator  begin_lanes() const  {return m_starlanes_wormholes.begin();}   ///< begin iterator for all starlanes and wormholes terminating in this system
   const_lane_iterator  end_lanes() const    {return m_starlanes_wormholes.end();}     ///< end iterator for all starlanes and wormholes terminating in this system
   
   virtual UniverseObject::Visibility Visible(int empire_id) const; ///< returns the visibility status of this universe object relative to the input empire.
   virtual GG::XMLElement XMLEncode() const; ///< constructs an XMLElement from a System object
   virtual GG::XMLElement XMLEncode(int empire_id) const; ///< constructs an XMLElement from a System object with visibility limited relative to the input empire
   //@}

   /** \name Mutators */ //@{
   /** inserts a UniversObject into the system, though not in any particular orbit.  Only objects free of any 
      particular orbit, such as ships, should be inserted using this function.  This function calls obj->SetSystem(this).*/
   int Insert(UniverseObject* obj);

   /** inserts an object into a specific orbit position.  Only orbit-bound objects, such as Planets, and planet-bound 
      objects should be inserted with this function.  This function calls obj->SetSystem(this).  \throw 
      std::invalid_arugment May throw std::invalid_arugment if \a orbit is out of the range [0, Orbits()].*/
   int Insert(UniverseObject* obj, int orbit);

   /** removes the object with ID number \a id from the system, and returns it; returns 0 if theree is no such object*/
   UniverseObject*   Remove(int id);

   /** removes the object with ID number \a id; returns true if such an object was found, false otherwise*/
   bool              Delete(int id);

   UniverseObject*   Object(int id); ///< returns a pointer to the system object with ID number \a id, or 0 if none exists

   void AddStarlane(int id);     ///< adds a starlane between this system and the system with ID number \a id.  \note Adding a starlane to a system to which there is already a wormhole reases the wormhole; you may want to check for a wormhole before calling this function.
   void AddWormhole(int id);     ///< adds a wormhole between this system and the system with ID number \a id  \note Adding a wormhole to a system to which there is already a starlane reases the starlane; you may want to check for a starlane before calling this function.
   bool RemoveStarlane(int id);  ///< removes a starlane between this system and the system with ID number \a id.  Returns false if there was no starlane from this system to system \a id.
   bool RemoveWormhole(int id);  ///< removes a wormhole between this system and the system with ID number \a id.  Returns false if there was no wormhole from this system to system \a id.

   /** returns all the objects that match \a pred.  Predicates used with this function must take a single UniverseObject* 
      parameter and must return a bool or a type for which there is a conversion to bool.*/
   template <class Pred>
   ObjectVec FindObjects(Pred pred)
   {
      ObjectVec retval;
      for (ObjectMultimap::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
         UniverseObject* o = it->second;
         if (pred(o))
            retval.push_back(o);
      }
      return retval;
   }

   virtual void MovementPhase(std::vector<SitRepEntry>& sit_reps);
   virtual void PopGrowthProductionResearchPhase(std::vector<SitRepEntry>& sit_reps);

   orbit_iterator begin()  {return m_objects.begin();}   ///< begin iterator for all system objects
   orbit_iterator end()    {return m_objects.end();}     ///< end iterator for all system objects

   /** returns begin and end iterators for all system objects in orbit \a o*/
   std::pair<orbit_iterator, orbit_iterator> orbit_range(int o) {return m_objects.equal_range(o);}

   /** returns begin and end iterators for all system objects not in an orbit*/  
   std::pair<orbit_iterator, orbit_iterator> non_orbit_range() {return m_objects.equal_range(-1);}

   lane_iterator  begin_lanes()  {return m_starlanes_wormholes.begin();}   ///< begin iterator for all starlanes and wormholes terminating in this system
   lane_iterator  end_lanes()    {return m_starlanes_wormholes.end();}     ///< end iterator for all starlanes and wormholes terminating in this system

  	virtual void XMLMerge(const GG::XMLElement& elem); ///< updates the System object from an XMLElement object that represents the updates
   //@}

private:
   StarType       m_star;
   int            m_orbits;
   ObjectMultimap m_objects;              ///< each key value represents an orbit (-1 represents general system contents not in any orbit); there may be many or no objects at each orbit (including -1)
   StarlaneMap    m_starlanes_wormholes;  ///< the ints represent the IDs of other connected systems; the bools indicate whether the connection is a wormhole (true) or a starlane (false)
};

#endif // _System_h_
