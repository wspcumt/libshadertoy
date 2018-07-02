#ifndef _SHADERTOY_INPUTS_BUFFER_INPUT_HPP_
#define _SHADERTOY_INPUTS_BUFFER_INPUT_HPP_

#include "shadertoy/pre.hpp"

#include "shadertoy/inputs/basic_input.hpp"

namespace shadertoy
{
namespace inputs
{

/**
 * @brief Represents an input that uses a swap chain output as its source.
 *
 * Note that setting min_filter to GL_*_MIPMAP_* will trigger automatic
 * generation of mipmaps on every update to the source member of this input,
 * which can impact performance of the resulting chain.
 *
 * This class only holds a \c weak_ptr to the referenced input to prevent
 * cyclic references. This means the target member must be owned by another
 * object for as long as this input object exists.
 */
class shadertoy_EXPORT buffer_input : public basic_input
{
	/// Reference to the member for this input
	std::weak_ptr<members::basic_member> member_;

protected:
	/// unused
	void load_input() override;

	/// unused
	void reset_input() override;

	/**
	 * @brief Obtain this input's texture object.
	 *
	 * In the case of a member input, it is the source texture
	 * of the associated member, or a null texture if there is
	 * no associated member.
	 *
	 * The member must have been initialized first so its textures
	 * exist.
	 *
	 * @return Pointer to the texture object for this input
	 */
	std::shared_ptr<gl::texture> use_input() override;

public:
	/**
	 * @brief Initialize a new instance of the buffer_input class with no associated buffer.
	 */
	buffer_input();

	/**
	 * @brief Initialize a new instance of the buffer_input class with \p
	 * member as an associated member.
	 *
	 * @param member Buffer to use as a source
	 */
	buffer_input(std::weak_ptr<members::basic_member> member);

	/**
	 * @brief Obtain the source member for this input
	 *
	 * @return Pointer to the source member for this input
	 */
	inline const std::weak_ptr<members::basic_member> &member() const { return member_; }

	/**
	 * @brief Set the source member for this input
	 *
	 * As a buffer input is stateless, the reset method does not
	 * need to be called after changing the source member.
	 *
	 * @param new_member New source member
	 */
	inline void member(std::weak_ptr<members::basic_member> new_member) { member_ = new_member; }
};
}
}

#endif /* _SHADERTOY_INPUTS_BUFFER_INPUT_HPP_ */
