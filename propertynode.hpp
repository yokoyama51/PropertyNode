

#ifndef __YOKOYAMA51_PROPERTYNODE_HPP__
#define __YOKOYAMA51_PROPERTYNODE_HPP__


#include <string>
#include <unordered_map>
#include <boost/any.hpp>


/**
 * @brief	�v���p�e�B���m�[�h�N���X
 *
 * @tparam	Char	���������^(char or wchar_t)
 */
template <typename Char>
class CPropertyNode
{
	typedef std::basic_string<Char, std::char_traits<Char>, std::allocator<Char> > String; ///< �}�b�v�L�[�̕�����^
	typedef std::unordered_map<String, boost::any> PropMap; ///< �v���p�e�B���ۑ��R���e�i�^

public: // �\�z/�j��
	///< @brief �R���X�g���N�^
	CPropertyNode(){}
		
	///< @brief �f�X�g���N�^
	virtual ~CPropertyNode(){}

public:

	/**
	 * @brief	�w�薼�̃v���p�e�B��ێ����邩�`�F�b�N����
	 *
	 * @param	propname	�`�F�b�N�Ώۖ���
	 *
	 * @return	true:�v���p�e�B�͑��݂���	false:���݂��Ȃ�
	 */
	bool IsExists(const Char * propname) const
		{
			PropMap::const_iterator it = m_property_map.find(propname);
			return (it != m_property_map.end());
		}


	/**
	 * @brief	�w�薼�̃v���p�e�B��ǉ�����
	 *
	 * @param	propname	�ǉ��v���p�e�B����
	 * @param	val			�v���p�e�B�l
	 *
	 * @return	true:��������	false:���s
	 *
	 * @note	���ꖼ�̃v���p�e�B������ꍇ�͒ǉ��Ɏ��s����
	 */
	bool Add(const Char * propname, boost::any val)
		{
			if(!IsExists(propname)) { return false; } // ���ꖼ�̃v���p�e�B�����łɂ���B

			m_property_map.insert(std::make_pair(propname, val));
			return true;
		}


	/**
	 * @brief	�w�薼�̃v���p�e�B���폜����
	 *
	 * @param	propname	�폜�Ώۃv���p�e�B����
	 *
	 * @return	true:��������	false:���s
	 *
	 * @note	delete�������͍s��Ȃ��̂ŁA�Ăяo�����ŉ�������͎������邱��
	 */
	bool Erase(const Char * propname)
		{
			PropMap::iterator it = m_property_map.find(propname);
			if(it != m_property_map.end()){
				m_property_map.erase(it);
				return true;
			}
			return false; // �w�薼�̃v���p�e�B�͑��݂��Ȃ�
		}
	

	/**
	 * @brief	�w�薼�̃v���p�e�B�̒l���擾����
	 *
	 * @param	propname	�擾�Ώۃv���p�e�B����
	 *
	 * @return	�v���p�e�B�l<br>
	 *			�v���p�e�B�����݂��Ȃ��ꍇ�͖߂�l�^�̏����l��Ԃ��B
	 *
	 * @warning	�ێ����Ă���l�Ɩ߂�l�̌^���قȂ�ꍇ�͗�O�ƂȂ�B
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
	PropMap m_property_map; ///< �v���p�e�B����ێ�����R���e�i
}; /* class CPropertyNode */

#endif /* __YOKOYAMA51_PROPERTYNODE_HPP__ */