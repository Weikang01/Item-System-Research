#pragma once
#include "pch.h"
#include "bimap.h"
/**** Equipment Layers:
	headwear:			0
	0: head				[1]
	0: eyes				[1]
	0: mask				[1]
	neckwear:			1
	0: neck				[1]
	tops:				2
	0: short underwear	[1]
	1: long underwear	[2]
	2: tops				[2]
	3: outerwear		[1]
	4: cloak			[1]
	5: sheath\quiver	[2]
	5: backpack			[1]
	trousers:			3
	0: short underwear	[1]
	1: long underwear	[2]
	2: paints			[2]
	3: outerwear		[1]		// typically plate armor
	footwear:			4
	0: shoes			[1]
	wrist:				5
	0: wrist			[1]
	hands:				6
	0: gloves			[1]
	0: rings			[2]
	1: outerwear		[1]		// typically plate armor
	2: brass knuckles	[1]
	3: weapon			[2]
	accessory:			7
	0: accessory		[2]
*/
/*
	****** Greate Sword ******
	* part:					hand
	* layer:				3
	* length:				1500 mm
	* weight:				2000000 mg
	* byte_size:					[5,2]
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

	{ 
		"Greate Sword" :
		{
			"part"		:	"hand"	,
			"layer"		:	3		,
			"length"	:	1500	,
		}
	
	}

	****** Tactical Pants ******
	* part:					trousers
	* layer:				2
	* weight:				400000 mg
	* byte_size:					[2,3]
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
	* byte_size:					[1,1]
	* max stack:			99
	* -----------------------------------
	* recovery:				4/sec

	****** Pork ******
	* weight:				100000 mg
	* byte_size:					[1,1]
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

using ItemID			= std::size_t;
using AttributeTypeID	= std::size_t;
using AttributeGroupID	= char;
using AttributeOrderID	= char;

//constexpr size_t MAX_ATTRIBUTES = 512;

struct GeneralDenseArray
{
private:
	constexpr static std::size_t INITIAL_SIZE = 8;
	std::size_t max_bsize;
	std::size_t cur_bsize;
	char* m_data;
public:
	GeneralDenseArray()
		:m_data((char*)malloc(INITIAL_SIZE)), max_bsize(INITIAL_SIZE), cur_bsize(0) {}

	template<typename T>
	GeneralDenseArray(T const * data, const std::size_t array_size)
		:m_data((char*)malloc(sizeof(T) * array_size)), max_bsize(sizeof(T) * array_size), cur_bsize(sizeof(T) * array_size)
	{
		memcpy_s(m_data, array_size * sizeof(T), data, array_size * sizeof(T));
	}

	template<typename T>
	GeneralDenseArray(std::initializer_list<T> data_list)
		: m_data((char*)malloc(sizeof(T)* data_list.size())), max_bsize(data_list.size() * sizeof(T)), cur_bsize(data_list.size() * sizeof(T))
	{
		std::uninitialized_copy(data_list.begin(), data_list.end(), (T*)m_data);
	}

	~GeneralDenseArray() { delete[] m_data; }

	template<typename T>
	T& operator[](const std::size_t offset)
	{
		if (cur_bsize <= offset)
			std::_Xout_of_range("invalid dense array subscript");
		return *((T*)(m_data + offset));
	}

	template<typename T>
	T& at(const std::size_t offset)
	{
		if (cur_bsize <= offset)
			std::_Xout_of_range("invalid dense array subscript");
		return *((T*)(m_data + offset));
	}

	void resize(const std::size_t byte_size)
	{
		if (byte_size != max_bsize)
		{
			char* temp = (char*)malloc(byte_size);
			memcpy_s(temp, byte_size, m_data, max_bsize);
			max_bsize = byte_size;
			m_data = temp;
		}
	}

	template<typename T>
	void emplace_back(const T* data_array, const std::size_t array_size)
	{
		if (cur_bsize + array_size * sizeof(T) > max_bsize)
			resize(cur_bsize + array_size * sizeof(T) + max_bsize);

		memcpy_s((T*)(m_data + cur_bsize), array_size * sizeof(T), data_array, array_size * sizeof(T));
		cur_bsize += array_size * sizeof(T);
	}

	template<typename T>
	void emplace_back()
	{
		if (cur_bsize + sizeof(T) > max_bsize)
			resize(cur_bsize + sizeof(T) + max_bsize);

		T temp{};
		memcpy_s((T*)(m_data + cur_bsize), sizeof(T), &(temp), sizeof(T));
		cur_bsize += sizeof(T);
	}

	template<typename T>
	void emplace_back(const T& data)
	{
		if (cur_bsize + sizeof(T) > max_bsize)
			resize(cur_bsize + sizeof(T) + max_bsize);

		memcpy_s((T*)(m_data + cur_bsize), sizeof(T), &(data), sizeof(T));
		cur_bsize += sizeof(T);
	}

	template<typename T>
	void emplace_back(std::initializer_list<T> data_list)
	{
		if (cur_bsize + data_list.size() * sizeof(T) > max_bsize)
			resize(cur_bsize + data_list.size() * sizeof(T) + max_bsize);

		std::uninitialized_copy(data_list.begin(), data_list.end(), (T*)(m_data + cur_bsize));

		cur_bsize += data_list.size() * sizeof(T);
	}

	template<typename T>
	void overwrite(const T* data_array, const std::size_t array_size, const std::size_t start_byte)
	{
		if (start_byte > cur_bsize)
			std::_Xout_of_range("start byte greater than current byte size!");

		cur_bsize = (cur_bsize > start_byte + array_size * sizeof(T)) ? cur_bsize : (start_byte + array_size * sizeof(T));
		if (cur_bsize > max_bsize)
			resize(cur_bsize + max_bsize);
		memcpy_s((T*)(m_data + start_byte), array_size * sizeof(T), data_array, array_size * sizeof(T));
	}

	template<typename T>
	void overwrite(const T& data, const std::size_t start_byte)
	{
		if (start_byte > cur_bsize)
			std::_Xout_of_range("start byte greater than current byte size!");

		cur_bsize = (cur_bsize > start_byte + sizeof(T)) ? cur_bsize : (start_byte + sizeof(T));
		if (cur_bsize > max_bsize)
			resize(cur_bsize + max_bsize);
		memcpy_s(m_data + start_byte, sizeof(T), &(data), sizeof(T));
	}

	template<typename T>
	void overwrite(std::initializer_list<T> data_list, const std::size_t start_byte)
	{
		if (start_byte > cur_bsize)
			std::_Xout_of_range("start byte greater than current byte size!");

		cur_bsize = (cur_bsize > start_byte + data_list.size() * sizeof(T)) ? cur_bsize : (start_byte + data_list.size() * sizeof(T));
		if (cur_bsize > max_bsize)
			resize(cur_bsize + max_bsize);

		std::uninitialized_copy(data_list.begin(), data_list.end(), (T*)(m_data + start_byte));
	}
};

template<typename T>
struct DenseArray
{
private:
	constexpr static std::size_t INITIAL_SIZE = 8;
	std::size_t max_size;
	std::size_t cur_size;
	char* m_data;
public:
	DenseArray()
		:m_data((char*)malloc(sizeof(T) * INITIAL_SIZE)), max_size(INITIAL_SIZE), cur_size(0) {}

	DenseArray(T const * data, const std::size_t array_size)
		:m_data((char*)malloc(sizeof(T) * array_size)), max_size(array_size), cur_size(array_size)
	{
		memcpy_s(m_data, array_size * sizeof(T), data, array_size * sizeof(T));
	}

	DenseArray(std::initializer_list<T> data_list)
		:m_data((char*)malloc(sizeof(T)* data_list.size())), max_size(data_list.size()), cur_size(data_list.size())
	{
		std::uninitialized_copy(data_list.begin(), data_list.end(), (T*)m_data);
	}

	~DenseArray() { delete[] m_data; }

	T& operator[](const std::size_t index)
	{
		if (cur_size <= index)
			std::_Xout_of_range("invalid dense array subscript");
		return *((T*)(m_data + index * sizeof(T)));
	}

	T& at(const std::size_t index)
	{
		if (cur_size <= index)
			std::_Xout_of_range("invalid dense array subscript");
		return *((T*)(m_data + index * sizeof(T)));
	}

	T& back() { return *((T*)(m_data + cur_size * sizeof(T))); }

	void resize(const std::size_t array_size)
	{
		if (array_size != max_size)
		{
			char* temp = (char*)malloc(sizeof(T) * array_size);
			memcpy_s(temp, array_size * sizeof(T), m_data, max_size * sizeof(T));
			max_size = array_size;
			m_data = temp;
		}
	}

	void emplace_back(const T* data_array, const std::size_t array_size)
	{
		if (cur_size + array_size > max_size)
			resize(cur_size + array_size + max_size);

		memcpy_s((T*)(m_data + cur_size * sizeof(T)), (max_size - cur_size) * sizeof(T), data_array, array_size * sizeof(T));
		cur_size = cur_size + array_size;
	}

	void emplace_back(const T& data)
	{
		if (cur_size == max_size)
			resize(cur_size + max_size);

		memcpy_s((T*)(m_data + cur_size * sizeof(T)), sizeof(T), &(data), sizeof(T));
		cur_size++;
	}

	void emplace_back()
	{
		if (cur_size == max_size)
			resize(cur_size + max_size);

		T temp = {};
		memcpy_s((T*)(m_data + cur_size * sizeof(T)), sizeof(T), &(temp), sizeof(T));
		cur_size++;
	}

	void emplace_back(std::initializer_list<T> data_list)
	{
		if (cur_size + data_list.size() > max_size)
			resize(cur_size + data_list.size() + max_size);

		std::uninitialized_copy(data_list.begin(), data_list.end(), (T*)(m_data + cur_size * sizeof(T)));

		cur_size += data_list.size();
	}

	void overwrite(const T* data_array, const std::size_t array_size, const std::size_t start_index)
	{
		if (start_index > cur_size)
			std::_Xout_of_range("start index greater than current size!");

		cur_size = (cur_size > start_index + array_size + 1) ? cur_size : (start_index + array_size + 1);
		if (cur_size > max_size)
			resize(cur_size + max_size);
		memcpy_s((T*)(m_data + start_index * sizeof(T)), array_size * sizeof(T), data_array, array_size * sizeof(T));
	}

	void overwrite(const T& data, const std::size_t index)
	{
		if (index > cur_size)
			std::_Xout_of_range("index greater than current size!");

		if (cur_size == max_size)
			resize(cur_size + max_size);
		cur_size++;
		memcpy_s(m_data + index * sizeof(T), sizeof(T), &(data), sizeof(T));
	}

	void overwrite(std::initializer_list<T> data_list, const std::size_t start_index)
	{
		if (start_index > cur_size)
			std::_Xout_of_range("index greater than current size!");

		cur_size = (cur_size > start_index + data_list.size() + 1) ? cur_size : (start_index + data_list.size() + 1);
		if (cur_size > max_size)
			resize(cur_size + max_size);

		std::uninitialized_copy(data_list.begin(), data_list.end(), (T*)(m_data + start_index * sizeof(T)));
	}
};

enum AttributeGroup
{
	/*
	weight				int
	byte_size (in bag)		vec2
	max stack			int
	*/
	GeneralDescription = 0,
	/*
	part				char
	layer				char
	*/
	GeneralEquipment = 1,
	/*
	water				int
	energy				int
	fat					int
	protein				int
	iron				int
	phosphorus			int
	potassium			int
	sodium				int
	calcium				int
	zinc				int
	omega_3				int
	*/
	Nutrience = 2,
};

struct AttributeID
{
private:
	short attr_id;
public:
	AttributeID() :attr_id() {}

	AttributeID(AttributeID const& o) :attr_id(o.attr_id) {}

	AttributeID(AttributeGroupID groupID, AttributeOrderID orderID)
		:attr_id(0)
	{
		*((char*)(&attr_id)) = orderID;
		*((char*)(&attr_id) + 1) = groupID;
	}

	bool operator==(AttributeID const& o) { return this->attr_id == o.attr_id; }

	bool operator==(AttributeID && o) { return this->attr_id == std::move(o).attr_id; }

	bool operator!=(AttributeID const& o) { return this->attr_id != o.attr_id; }

	bool operator!=(AttributeID&& o) { return this->attr_id != std::move(o).attr_id; }

	AttributeOrderID orderID()
	{
		return *((char*)(&attr_id));
	}

	void orderID(AttributeOrderID orderID)
	{
		*((char*)(&attr_id)) = orderID;
	}

	AttributeGroupID groupID()
	{
		return *((char*)(&attr_id) + 1);
	}

	void groupID(AttributeGroupID groupID)
	{
		*((char*)(&attr_id) + 1) = groupID;
	}

	operator std::string()
	{
		int gid = 0, oid = 0;
		gid |= groupID(); oid |= orderID();
		return std::to_string(gid) + "-" + std::to_string(oid);
	}
};

template<typename _DataType>
struct AttributeInstance
{
	_DataType data;
	AttributeID attr_id;

	template<typename... TArgs>
	AttributeInstance(AttributeID const attrID, TArgs && ... args)
		: attr_id(attrID), data({std::forward<TArgs>(args)...})
	{}

};

class IAttribute
{
protected:
	class AttributeHierarchy
	{
		std::vector<std::vector<IAttribute*>> attrGroupOrderList;
		std::map<AttributeGroupID, std::vector<AttributeOrderID>> removedAttrs;

		const AttributeGroupID MAX_GROUP_SIZE = 16;

		AttributeHierarchy() {}
	public:
		static AttributeHierarchy& getInstance() { static AttributeHierarchy inst{}; return inst; }

		void setGroupOrderList(IAttribute* attr, AttributeGroupID groupID)
		{
			if (groupID >= MAX_GROUP_SIZE)
				assert(0, "Too many attribute group has been created!");

			attr->m_id.groupID(groupID);
			if (removedAttrs.count(groupID))
			{
				attr->m_id.orderID(removedAttrs.at(groupID).back());
				attrGroupOrderList[groupID][attr->m_id.orderID()] = attr;

				removedAttrs.at(groupID).pop_back();
				if (removedAttrs.at(groupID).empty())
					removedAttrs.erase(groupID);
			}
			else
			{
				while (attrGroupOrderList.size() <= groupID)
					attrGroupOrderList.push_back({});

				attr->m_id.orderID(attrGroupOrderList[groupID].size());
				attrGroupOrderList[groupID].emplace_back(attr);
			}
		}

		void setGroupOrderList(IAttribute* attr, AttributeGroupID groupID, AttributeOrderID orderID)
		{
			if (groupID >= MAX_GROUP_SIZE)
				assert(0, "Too many attribute group has been created!");

			attr->m_id.groupID(groupID);
			if (removedAttrs.count(groupID))
			{
				std::vector<AttributeOrderID>::iterator ptr = std::find(removedAttrs[groupID].begin(), removedAttrs[groupID].end(), orderID);
				if (ptr != removedAttrs[groupID].end())
				{
					attr->m_id.orderID(orderID);
					attrGroupOrderList[groupID][orderID] = attr;
					ptr = removedAttrs[groupID].erase(ptr);
				}
			}
			else
			{
				if (attrGroupOrderList.size() > groupID)
				{
					if (attrGroupOrderList[groupID].size() > orderID && attrGroupOrderList[groupID][orderID] != nullptr)
						assert(0, "the group order id has been taken!");

					if (attrGroupOrderList[groupID].size() == orderID)
					{
						attr->m_id.orderID(orderID);
						attrGroupOrderList[groupID].emplace_back(attr);
						return;
					}

					if ((attrGroupOrderList[groupID].size() > orderID && attrGroupOrderList[groupID][orderID] == nullptr))
					{
						attr->m_id.orderID(orderID);
						attrGroupOrderList[groupID][orderID] = attr;
						return;
					}
				}

				while (attrGroupOrderList.size() <= groupID)
					attrGroupOrderList.push_back({});

				while (attrGroupOrderList[groupID].size() <= orderID)
					attrGroupOrderList[groupID].push_back({});

				attr->m_id.orderID(orderID);
				attrGroupOrderList[groupID][orderID] = attr;
			}
		}

		void removeAttribute(AttributeGroupID groupID, AttributeOrderID orderID)
		{
			if (attrGroupOrderList.size() > groupID && attrGroupOrderList[groupID].size() > orderID && attrGroupOrderList[groupID][orderID] != nullptr)
			{
				removedAttrs[groupID].push_back(orderID);
				attrGroupOrderList[groupID][orderID] = nullptr;
			}
		}

		IAttribute* getAttribute(AttributeGroupID groupID, AttributeOrderID orderID)
		{
			if (attrGroupOrderList.size() > groupID && attrGroupOrderList[groupID].size() > orderID)
				return attrGroupOrderList[groupID][orderID];
		}

		AttributeHierarchy(AttributeHierarchy const&) = delete;
		void operator=(AttributeHierarchy const&) = delete;


	};

	AttributeID m_id;
	std::string m_name;

	IAttribute(const char* name = "", AttributeGroupID groupID = 0)
		: m_name(std::move(name))
	{
		AttributeHierarchy::getInstance().setGroupOrderList(this, groupID);
	}

	IAttribute(const char const* name, AttributeGroupID groupID, AttributeOrderID orderID)
		: m_name(name)
	{
		AttributeHierarchy::getInstance().setGroupOrderList(this, groupID, orderID);
	}

	virtual std::size_t getClassCode() = 0;
public:

	IAttribute* getAttribute(AttributeGroupID groupID, AttributeOrderID orderID)
	{
		return AttributeHierarchy::getInstance().getAttribute(groupID, orderID);
	}

	AttributeID getID() { return m_id; }
};

template<typename _DataType>
std::string default_description(_DataType const& attrInst);

template<typename _DataType>
class Attribute : public IAttribute
{
	Attribute(const char* name = "", std::string(* get_description)(_DataType const&) = default_description, AttributeGroupID groupID = 0)
		: IAttribute(name, groupID), get_description(get_description) {}

	Attribute(const char const* name, std::string(* get_description)(_DataType const&), AttributeGroupID groupID, AttributeOrderID orderID)
		: IAttribute(name, groupID, orderID), get_description(get_description) {}
public:
	static Attribute& getInstance(const char* name = "", std::string(*get_description)(_DataType const&) = default_description, AttributeGroupID groupID = 0)
	{
		static std::unique_ptr<Attribute> inst{ new Attribute(name, get_description, groupID) };
		return *inst;
	}

	template<typename... TArgs>
	_DataType instantiate(TArgs && ... args)
	{
		return _DataType(std::forward<TArgs>(args)...);
	}

	static unsigned int sizeofAttr()
	{
		return sizeof(_DataType);
	}
	
	std::string(*get_description)(_DataType const&);

	std::size_t getClassCode() override { return typeid(Attribute).hash_code(); }

	std::string& getName() { return m_name; }

	AttributeID& getID() { return m_id; }

	Attribute(Attribute<_DataType> const&) = delete;
	void operator = (Attribute<_DataType> const&) = delete;
};

template<typename _DataType>
std::string default_description(_DataType const& dataInst)
{
	return "name:\t" + Attribute<_DataType>::getInstance().getName() + "\nid:\t" + static_cast<std::string>(Attribute<_DataType>::getInstance().getID());
}

struct ItemInstance
{
};

class Item
{
	static constexpr std::size_t MAX_SIZE_T = (~(std::size_t)0);
	std::string name;
	std::string description;

	std::map<size_t, size_t> attrCodeOffsetMap;
	GeneralDenseArray attrDataList;
	ItemID id;
	AttributeTypeID offset;

	static ItemID getID()
	{
		static ItemID id = 0;
		return id++;
	}

	template<typename _AttrType>
	std::size_t getAttrCode()
	{
		return attrCodeOffsetMap[Attribute<_AttrType>::getInstance().getClassCode()];
	}

public:
	Item(std::string name = "", std::string const description = "")
		:id(getID()), offset(0), name(name), description(description), attrCodeOffsetMap(), attrDataList() {}

	void addAttribute() {}

	template<typename _AttrType, typename... _TArgs>
	void addAttribute(_TArgs&& ...args)
	{
		attrCodeOffsetMap[Attribute<_AttrType>::getInstance().getClassCode()] = offset;
		offset += sizeof(_AttrType);
		attrDataList.emplace_back<AttributeInstance<_AttrType>>(
			{ Attribute<_AttrType>::getInstance().getID(),
			std::forward<_TArgs>(args)... });
	}

	template<typename _AttrType>
	_AttrType& getAttribute()
	{
		return attrDataList.at<_AttrType>(getAttrCode<_AttrType>());
	}

	template<typename _AttrType, typename... _TArgs>
	void modifyAttribute(_TArgs&& ...args)
	{
		attrDataList.overwrite<_AttrType>(std::forward<_TArgs>(args)..., getAttrCode<_AttrType>());
	}
};
