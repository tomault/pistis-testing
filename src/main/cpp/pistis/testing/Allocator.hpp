#ifndef __PISTIS__TESTING__ALLOCATOR_HPP__
#define __PISTIS__TESTING__ALLOCATOR_HPP__

#include <string>
#include <memory>

/** @file Allocator.hpp
 *
 *  Allocator for unit testing
 */
namespace pistis {
  namespace testing {

    template <typename T>
    class Allocator : public std::allocator<T> {
    public:
      Allocator() :
	  std::allocator<T>(), name_(), movedFrom_(false), movedInto_(false) {
      }
      Allocator(const std::string& name):
	  std::allocator<T>(), name_(name), movedFrom_(false),
	  movedInto_(false) {
      }
      template <typename U>
      Allocator(const Allocator<U>& other) :
	  std::allocator<T>(other), name_(other.name()), movedFrom_(false),
	  movedInto_(false) {
      }
      Allocator(const Allocator& other) :
	  std::allocator<T>(other), name_(other.name()), movedFrom_(false),
	  movedInto_(false) {
      }
      Allocator(Allocator&& other) :
	  std::allocator<T>(std::move(other)), name_(std::move(other.name_)),
	  movedFrom_(false), movedInto_(true) {
	other.movedFrom_ = true;
      }

      const std::string& name() const { return name_; }
      bool movedFrom() const { return movedFrom_; }
      bool moved() const { return movedInto_; }

      template <typename U>
      Allocator& operator=(const Allocator<U>& other) {
	std::allocator<T>::operator=(other);
	name_ = other.name();
	movedFrom_ = false;
	movedInto_ = false;
	return *this;
      }

      Allocator& operator=(const Allocator& other) {
	std::allocator<T>::operator=(other);
	name_ = other.name();
	movedFrom_ = false;
	movedInto_ = false;
	return *this;
      }

      Allocator& operator=(Allocator&& other) {
	std::allocator<T>::operator=(std::move(other));
	name_ = std::move(other.name_);
	movedFrom_ = false;
	movedInto_ = true;
	other.movedFrom_ = true;
	return *this;
      }

    private:
      std::string name_;
      bool movedFrom_;
      bool movedInto_;
    };

  }
}
#endif
