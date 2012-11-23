// Copyright �2012 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in "bss_util.h"

#ifndef __C_MAP_H__BSS__
#define __C_MAP_H__BSS__

#include "cArraySort.h"
#include <utility>

namespace bss_util {
  // A map class implemented as an associative sorted array
  template<class Key, class Data, char (*CFunc)(const Key&,const Key&)=CompT<Key>, typename SizeType=unsigned int, typename ArrayType=cArraySimple<std::pair<Key,Data>,SizeType>>
  class BSS_COMPILER_DLLEXPORT cMap : protected cArraySort<std::pair<Key,Data>, CompTFirst<std::pair<Key,Data>, CFunc>, SizeType, ArrayType>
  {
  protected:
    typedef SizeType ST_;
    typedef std::pair<Key,Data> pair_t;
    typedef cArraySort<pair_t, CompTFirst<pair_t, CFunc>, ST_, ArrayType> cArraySort_t;
    typedef const Data& constref;
    typedef Data&& moveref;
    typedef const Key& CKEYREF;

    inline static char mapComp(const Key& a, const pair_t& b) { return CFunc(a,b.first); }

  public:
    explicit cMap(ST_ init=1) : cArraySort_t(init) {}
    cMap(const cMap& copy) : cArraySort_t(copy) {}
    cMap(cMap&& mov) : cArraySort_t(std::move(mov)) {}
    //~cMap() {}
    inline void BSS_FASTCALL Clear() { cArraySort_t::Clear(); }
    inline BSS_FORCEINLINE void BSS_FASTCALL Discard(unsigned int num) { cArraySort_t::Discard(num); }
    inline BSS_FORCEINLINE ST_ BSS_FASTCALL Insert(CKEYREF key, constref data) { return cArraySort_t::Insert(pair_t(key,data)); }
    inline BSS_FORCEINLINE ST_ BSS_FASTCALL Insert(CKEYREF key, moveref data) { return cArraySort_t::Insert(pair_t(key,std::move(data))); }
    inline ST_ BSS_FASTCALL Get(CKEYREF key) const {  ST_ retval=GetNear(key,true); return (retval!=(ST_)(-1)&&!CompT(_array[retval].first,key))?retval:(ST_)(-1); }
    inline BSS_FORCEINLINE constref BSS_FASTCALL GetData(CKEYREF key) const { return cArraySort_t::operator [](GetNear(key,true)).second; } //this has no checking
    inline ST_ BSS_FASTCALL Remove(CKEYREF key) {  ST_ retval=Get(key); cArraySort_t::Remove(retval); return retval; }
    inline BSS_FORCEINLINE ST_ BSS_FASTCALL RemoveIndex(ST_ index) { return cArraySort_t::Remove(index); }
    inline BSS_FORCEINLINE ST_ BSS_FASTCALL Replace(ST_ index, CKEYREF key, constref data) { return cArraySort_t::ReplaceData(index, pair_t(key,data)); }
    inline BSS_FORCEINLINE ST_ BSS_FASTCALL Replace(ST_ index, CKEYREF key, moveref data) { return cArraySort_t::ReplaceData(index, pair_t(key,std::move(data))); }
    inline ST_ BSS_FASTCALL ReplaceKey(ST_ index, CKEYREF key) { if(index<0 || index >= _length) return (ST_)(-1); return cArraySort_t::ReplaceData(index, pair_t(key,_array[index].second)); }
    inline BSS_FORCEINLINE CKEYREF BSS_FASTCALL KeyIndex(ST_ index) const { return cArraySort_t::operator [](index).first; }
    inline BSS_FORCEINLINE Data& BSS_FASTCALL DataIndex(ST_ index) const { return cArraySort_t::operator [](index).second; }
    inline ST_ BSS_FASTCALL Length() const { return _length; }
    inline BSS_FORCEINLINE void BSS_FASTCALL Expand(ST_ size) { cArraySort_t::Expand(size); }
    inline ST_ BSS_FASTCALL Set(CKEYREF key, constref data)
    {
      ST_ retval=GetNear(key,true);
      if(retval==(ST_)(-1) || CompT(_array[retval].first,key)!=0) return (ST_)(-1);

      _array[retval].second=data;
      return retval;
    }
    inline ST_ BSS_FASTCALL GetNear(CKEYREF key, bool before) const {
      ST_ retval=before?(binsearch_near<pair_t,Key,ST_,mapComp,CompT_NEQ<char>,-1>(_array,key,0,_length)-1):binsearch_near<pair_t,Key,ST_,mapComp,CompT_EQ<char>,1>(_array,key,0,_length);
      return (retval<_length)?retval:(ST_)(-1); // This is only needed for before=false in case it returns a value outside the range.
    }

    inline cMap& operator =(const cMap& right) { cArraySort_t::operator =(right); /*_lastindex=right._lastindex;*/ return *this; }
    inline cMap& operator =(cMap&& right) { cArraySort_t::operator =(std::move(right)); /*_lastindex=right._lastindex;*/ return *this; }
    inline constref operator [](ST_ index) const { return cArraySort_t::operator [](index).second; }
    inline Data& operator [](ST_ index) { return cArraySort_t::operator [](index).second; }
  };
}

#endif

/*    {
      if(!_length) return (ST_)(-1);
      ST_ last=_length;
      ST_ first=0;
      ST_ retval=last>>1;
      char compres;
      while((compres=CompT(key,_array[retval].first))!=0)
      {
        if(compres<0)
        {
          last=retval;
          retval=first+((last-first)>>1); //R = F+((L-F)/2)
          if(last==retval)
            return before?--retval:retval; //interestingly, if retval is 0, we end up with -1 which is exactly what we'd want anyway
        }
        else
        {
          first=retval;
          retval+=(last-first)>>1;
          if(first==retval)
            return before?retval:(((++retval)<_length)?retval:(ST_)(-1));
        }
      }
      return retval;
    }*/