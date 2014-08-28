

#ifndef __YOKOYAMA51_PROPERTYNODE_HPP__
#define __YOKOYAMA51_PROPERTYNODE_HPP__


#include <string>
#include <unordered_map>
#include <boost/any.hpp>


/**
 * @brief	プロパティ情報ノードクラス
 *
 * @tparam	Char	扱う文字型(char or wchar_t)
 */
template <typename Char>
class CPropertyNode
{
	typedef std::basic_string<Char, std::char_traits<Char>, std::allocator<Char> > String; ///< マップキーの文字列型
	typedef std::unordered_map<String, boost::any> PropMap; ///< プロパティ情報保存コンテナ型

public: // 構築/破棄
	///< @brief コンストラクタ
	CPropertyNode(){}
		
	///< @brief デストラクタ
	virtual ~CPropertyNode(){}

public:

	/**
	 * @brief	指定名称プロパティを保持するかチェックする
	 *
	 * @param	propname	チェック対象名称
	 *
	 * @return	true:プロパティは存在する	false:存在しない
	 */
	bool IsExists(const Char * propname) const
		{
			PropMap::const_iterator it = m_property_map.find(propname);
			return (it != m_property_map.end());
		}


	/**
	 * @brief	指定名称プロパティを追加する
	 *
	 * @param	propname	追加プロパティ名称
	 * @param	val			プロパティ値
	 *
	 * @return	true:処理成功	false:失敗
	 *
	 * @note	同一名称プロパティがある場合は追加に失敗する
	 */
	bool Add(const Char * propname, boost::any val)
		{
			if(!IsExists(propname)) { return false; } // 同一名称プロパティがすでにある。

			m_property_map.insert(std::make_pair(propname, val));
			return true;
		}


	/**
	 * @brief	指定名称プロパティを削除する
	 *
	 * @param	propname	削除対象プロパティ名称
	 *
	 * @return	true:処理成功	false:失敗
	 *
	 * @note	delete処理等は行わないので、呼び出し側で解放処理は実装すること
	 */
	bool Erase(const Char * propname)
		{
			PropMap::iterator it = m_property_map.find(propname);
			if(it != m_property_map.end()){
				m_property_map.erase(it);
				return true;
			}
			return false; // 指定名称プロパティは存在しない
		}
	

	/**
	 * @brief	指定名称プロパティの値を取得する
	 *
	 * @param	propname	取得対象プロパティ名称
	 *
	 * @return	プロパティ値<br>
	 *			プロパティが存在しない場合は戻り値型の初期値を返す。
	 *
	 * @warning	保持している値と戻り値の型が異なる場合は例外となる。
	 */
	template <typename T>
	T Find(const Char * propname) const
		{
			PropMap::const_iterator it = m_property_map.find(propname);
			if(it != m_property_map.end()){
				const boost::any &val = (*it).second;
				return boost::any_cast<T>(val);
			}
			return T();
		}

private:
	PropMap m_property_map; ///< プロパティ情報を保持するコンテナ
}; /* class CPropertyNode */

#endif /* __YOKOYAMA51_PROPERTYNODE_HPP__ */