#ifndef __PISTIS__TESTING__ITERATORS_HPP__
#define __PISTIS__TESTING__ITERATORS_HPP__

/** @file Functions for testing iterator behavior */
#include <cstddef>
#include <iterator>
#include <type_traits>

#include <gtest/gtest.h>

namespace pistis {
  namespace testing {
    namespace iterators {

      // Unit tests written using Google Test
      // Iterator testing functions will return gtest's AssertionResult

      /** @brief Test dereferencing and reading from an iterator */
      template <typename Iterator, typename Value>
      void testDereferenceAndRead(Iterator it, Value truth) {
	ASSERT_EQ(*it, truth);
      }

      /** @brief Test dereferencing and writing to an iterator */
      template <typename Iterator, typename Value>
      void testDereferenceAndWrite(Iterator it, Value truth) {
	*it= truth;
	ASSERT_EQ(*it, truth);
      }

      /** @brief Test copy construction */
      template <typename Iterator>
      void testCopyConstruction(Iterator it) {
	Iterator copy(it);
	ASSERT_EQ(*copy, *it);
      }

      /** @brief Test copy assignment */
      template <typename Iterator>
      void testCopyAssignment(Iterator it) {
	Iterator copy(it);
	EXPECT_EQ(*copy, *it);
      }

      /** @brief Test equality comparison */
      template <typename Iterator>
      void testEqualityOp(Iterator it, Iterator same, Iterator different) {
	ASSERT_TRUE(it == same);
	ASSERT_FALSE(it == different);
      }

      /** @brief Test inequality comparison */
      template <typename Iterator>
      void testInequalityOp(Iterator it, Iterator same, Iterator different) {
	ASSERT_FALSE(it != same);
	ASSERT_TRUE(it != different);
      }

      /** @brief Test iteration with the pre-increment operator */
      template <typename Iterator, typename Sequence>
      void testPreincrementIteration(Iterator it, const Sequence& truth,
				     Iterator& end) {
	for (auto x : truth) {
	  ASSERT_EQ(*it, x);
	  ++it;
	}
	end = it;
      }

      /** @brief Test iteration with the post-increment operator */
      template <typename Iterator, typename Sequence>
      void testPostincrementIteration(Iterator it, const Sequence& truth,
				      Iterator& end) {
	for (auto x : truth) {
	  ASSERT_EQ(*it++, x);
	}
	end = it;
      }

      /** @brief Test iteration with the pre-decrement operator */
      template <typename Iterator, typename Sequence>
      void testPredecrementIteration(Iterator it, const Sequence& truth,
				     Iterator& end) {
	for (auto x : truth) {
	  --it;
	  ASSERT_EQ(*it, x);
	}
	end = it;
      }

      /** @brief Test iteration with the post-decrement operator */
      template <typename Iterator, typename Sequence>
      void testPostdecrementIteration(Iterator it, const Sequence& truth,
				      Iterator& end) {
	for (auto x : truth) {
	  ASSERT_EQ(*it--, x);
	}
	end = it;
      }

      /** @brief Test the '+' and '+=' operators */
      template <typename Iterator, typename Value>
      void testAdditionOperator(Iterator it,
				typename Iterator::difference_type offset,
				Value valueAtStart, Value valueAtOffset) {
	Iterator p= it + offset;
	ASSERT_EQ(*it, valueAtStart);
	ASSERT_EQ(*p, valueAtOffset);
	
	it += offset;
	ASSERT_EQ(*it, valueAtOffset);
      }

      /** @brief Test the '-' and '-=' operators */
      template <typename Iterator, typename Value>
      void testSubtractionOperator(Iterator it,
				   typename Iterator::difference_type offset,
				   Value valueAtStart, Value valueAtOffset) {
	Iterator p= it - offset;
	ASSERT_EQ(*it, valueAtStart);
	ASSERT_EQ(*it, valueAtOffset);
	
	it -= offset;
	ASSERT_EQ(*it, valueAtOffset);
      }

      /** @brief Test the difference operation */
      template <typename Iterator>
      void testDifferenceOperator(Iterator start, Iterator end,
				  typename Iterator::difference_type distance) {
	ASSERT_EQ(end - start, distance);
      }

      /** @brief Test the relational ('<', '<=', '>=', '>') operators */
      template <typename Iterator>
      void testRelationalOperators(Iterator it, Iterator same, Iterator after) {
	ASSERT_TRUE(it < after);
	ASSERT_FALSE(it < same);
	ASSERT_FALSE(after < it);

	ASSERT_TRUE(it <= after);
	ASSERT_TRUE(it <= same);
	ASSERT_FALSE(after <= it);

	ASSERT_FALSE(it > after);
	ASSERT_FALSE(it > same);
	ASSERT_TRUE(after > it);

	ASSERT_FALSE(it >= after);
	ASSERT_TRUE(it >= same);
	ASSERT_TRUE(after >= it);
      }

      template <typename MutableIterator, typename ConstIterator>
      void testConstructConstIteratorFromMutable(MutableIterator mutableIterator,
						 ConstIterator truth) {
	ConstIterator it(mutableIterator);
	ASSERT_EQ(truth, it);
      }

      template <typename MutableIterator, typename ConstIterator>
      void testAssignMutableIteratorToConst(MutableIterator mutableIterator,
					    ConstIterator truth) {
	ConstIterator constIterator(truth);
	++constIterator;

	ASSERT_NE(truth, constIterator);
	ASSERT_NE(constIterator, mutableIterator);
	constIterator = mutableIterator;
	ASSERT_EQ(truth, constIterator);
      }

      template <typename ConstIterator, typename MutableIterator>
      void testCompareMutableAndConstIterators(ConstIterator constIterator,
					       MutableIterator mutableIterator) {
	MutableIterator nextMutable(mutableIterator);

	++nextMutable;
	
	ASSERT_TRUE(constIterator == mutableIterator);
	ASSERT_TRUE(mutableIterator == constIterator);
	ASSERT_FALSE(constIterator == nextMutable);
	ASSERT_FALSE(nextMutable == constIterator);

	ASSERT_FALSE(constIterator != mutableIterator);
	ASSERT_FALSE(mutableIterator != constIterator);
	ASSERT_TRUE(constIterator != nextMutable);
	ASSERT_TRUE(nextMutable != constIterator);
      }

      template <typename ConstIterator, typename MutableIterator>
      void testRelationalOpsBetweenConstAndMutable(ConstIterator constIterator,
						   MutableIterator mutableIterator) {
	ConstIterator nextConst(constIterator);
	MutableIterator nextMutable(mutableIterator);

	++nextConst;
	++nextMutable;

	ASSERT_TRUE(constIterator < nextMutable);
	ASSERT_TRUE(mutableIterator < nextConst);
	ASSERT_FALSE(constIterator < mutableIterator);
	ASSERT_FALSE(mutableIterator < constIterator);
	ASSERT_FALSE(nextConst < mutableIterator);
	ASSERT_FALSE(nextMutable < constIterator);

	ASSERT_TRUE(constIterator <= nextMutable);
	ASSERT_TRUE(mutableIterator <= nextConst);
	ASSERT_TRUE(constIterator <= mutableIterator);
	ASSERT_TRUE(mutableIterator <= constIterator);
	ASSERT_FALSE(nextConst <= mutableIterator);
	ASSERT_FALSE(nextMutable <= constIterator);

	ASSERT_FALSE(constIterator >= nextMutable);
	ASSERT_FALSE(mutableIterator >= nextConst);
	ASSERT_TRUE(constIterator >= mutableIterator);
	ASSERT_TRUE(mutableIterator >= constIterator);
	ASSERT_TRUE(nextConst >= mutableIterator);
	ASSERT_TRUE(nextMutable >= constIterator);

	ASSERT_FALSE(constIterator > nextMutable);
	ASSERT_FALSE(mutableIterator > nextConst);
	ASSERT_FALSE(constIterator > mutableIterator);
	ASSERT_FALSE(mutableIterator > constIterator);
	ASSERT_TRUE(nextConst > mutableIterator);
	ASSERT_TRUE(nextMutable > constIterator);
      }

      template <typename ConstIterator, typename MutableIterator>
      void testRelationalOpsBetweenConstAndMutableIfNeeded(
        ConstIterator constIterator,
	MutableIterator mutableIterator,
	typename std::enable_if< std::is_same<typename ConstIterator::iterator_category,
	                                      std::random_access_iterator_tag>::value,
	                         int>::type = 0) {
	static_assert(std::is_same<typename MutableIterator::iterator_category,
		                   std::random_access_iterator_tag>::value,
		      "Const and mutable iterators do not belong to the same category");
	testRelationalOpsBetweenConstAndMutable(constIterator, mutableIterator);
      }

      template <typename ConstIterator, typename MutableIterator>
      void testRelationalOpsBetweenConstAndMutableIfNeeded(
        ConstIterator constIterator,
	MutableIterator mutableIterator,
	typename std::enable_if< !std::is_same<typename ConstIterator::iterator_category,
	                                       std::random_access_iterator_tag>::value,
	                         int>::type = 0) {
	// Do nothing -- these are not random access iterators
	static_assert(!std::is_same<typename MutableIterator::iterator_category,
		                    std::random_access_iterator_tag>::value,
		      "Const and mutable iterators do not belong to the same category");
      }

      template <typename SimpleIterator, typename Sequence>
      void testSimpleIteratorPreincrement(SimpleIterator it,
					  const Sequence& truth) {
	auto i = truth.begin();
	while (it) {
	  ASSERT_NE(i, truth.end());
	  ASSERT_EQ(*i, *it);
	  ++it; ++i;
	}
	ASSERT_EQ(i, truth.end());
      }

      template <typename SimpleIterator, typename Sequence>
      void testSimpleIteratorPostincrement(SimpleIterator it,
					   const Sequence& truth) {
	auto i = truth.begin();
	while (it) {
	  ASSERT_NE(i, truth.end());
	  ASSERT_EQ(*i, *it++);
	  ++i;
	}
	ASSERT_EQ(i, truth.end());
      }

      template <typename SimpleIterator, typename Sequence>
      void testWriteThroughSimpleIterator(SimpleIterator it,
					  const Sequence& truth) {
	for (auto x : truth) {
	  ASSERT_TRUE(bool(it));
	  *it = x;
	  ASSERT_EQ(x, *it);
	  ++it;
	}
	ASSERT_FALSE(bool(it));
      }

      template <typename StartIteratorFactory,
		typename EndIteratorFactory,
		typename Sequence>
      void testInputIterator(StartIteratorFactory createIteratorAtStart,
			     EndIteratorFactory createIteratorAtEnd,
			     const Sequence& truth) {
	SCOPED_TRACE("testInputIterator");
	testCopyConstruction(createIteratorAtStart());
	testCopyAssignment(createIteratorAtStart());
	testDereferenceAndRead(createIteratorAtStart(), *truth.begin());
	testEqualityOp(createIteratorAtEnd(), createIteratorAtEnd(),
		       createIteratorAtStart());
	testInequalityOp(createIteratorAtEnd(), createIteratorAtEnd(),
			 createIteratorAtStart());

	auto it = createIteratorAtStart();
	testPreincrementIteration(it, truth, it);
	EXPECT_EQ(it, createIteratorAtEnd());

	it = createIteratorAtStart();
	it= testPostincrementIteration(it, truth, it);
	EXPECT_EQ(it, createIteratorAtEnd());
      }

      template <typename StartIteratorFactory, typename EndIteratorFactory,
		typename Sequence>
      void testForwardIterator(StartIteratorFactory createIteratorAtStart,
			       EndIteratorFactory createIteratorAtEnd,
			       const Sequence& truth) {
	SCOPED_TRACE("testForwardIterator");
	testCopyConstruction(createIteratorAtStart());
	testCopyAssignment(createIteratorAtStart());
	testDereferenceAndRead(createIteratorAtStart(), *truth.begin());
	testEqualityOp(createIteratorAtEnd(), createIteratorAtEnd(),
		       createIteratorAtStart());
	testInequalityOp(createIteratorAtEnd(), createIteratorAtEnd(),
			 createIteratorAtStart());
	
	auto it = createIteratorAtStart();
	testPreincrementIteration(it, truth, it);
	EXPECT_EQ(it, createIteratorAtEnd());

	it = createIteratorAtStart();
	testPostincrementIteration(it, truth, it);
	EXPECT_EQ(it, createIteratorAtEnd());
      }

      template <typename StartIteratorFactory, typename EndIteratorFactory,
		typename Sequence, typename SequenceValue>
      void testMutableForwardIterator(StartIteratorFactory createIteratorAtStart,
				      EndIteratorFactory createIteratorAtEnd,
				      const Sequence& truth,
				      const SequenceValue& valueToWrite) {
	testForwardIterator(createIteratorAtStart, createIteratorAtEnd, truth);
	SCOPED_TRACE("testMutableForwardIterator");
	testDereferenceAndWrite(createIteratorAtStart(), valueToWrite);
      }

      template <typename StartIteratorFactory, typename EndIteratorFactory,
		typename Sequence>
      void testBidirectionalIterator(StartIteratorFactory createIteratorAtStart,
				     EndIteratorFactory createIteratorAtEnd,
				     const Sequence& truth) {
	typedef typename std::remove_cv<typename std::remove_reference<decltype(truth[0])>::type>::type ValueType;
	std::vector<ValueType> reversedTruth(truth.rbegin(), truth.rend());

	testForwardIterator(createIteratorAtStart, createIteratorAtEnd, truth);
	SCOPED_TRACE("testBidirectionalIterator");

	auto it = createIteratorAtEnd();
	testPredecrementIteration(it, reversedTruth, it);
	EXPECT_EQ(createIteratorAtStart(), it);

	it = createIteratorAtEnd();
	--it;
	testPostdecrementIteration(it, reversedTruth, it);
	++it;
	EXPECT_EQ(createIteratorAtStart(), it);
      }

      template <typename StartIteratorFactory, typename EndIteratorFactory,
		typename Sequence, typename SequenceValue>
      void testMutableBidirectionalIterator(StartIteratorFactory createIteratorAtStart,
					    EndIteratorFactory createIteratorAtEnd,
					    const Sequence& truth,
					    const SequenceValue& valueToWrite) {
	testBidirectionalIterator(createIteratorAtStart, createIteratorAtEnd, truth);
	SCOPED_TRACE("testMutableBidirectionalIterator");
	testDereferenceAndWrite(createIteratorAtStart(), valueToWrite);
      }

      template <typename StartIteratorFactory,
		typename EndIteratorFactory,
		typename Sequence>
      void testRandomAccessIterator(StartIteratorFactory createIteratorAtStart,
				    EndIteratorFactory createIteratorAtEnd,
				    const Sequence& truth) {
	testBidirectionalIterator(createIteratorAtStart, createIteratorAtEnd, truth);
	
	SCOPED_TRACE("testRandomAccessIterator");
	testAdditionOperator(createIteratorAtStart(), 2, truth[0], truth[2]);

	auto it= createIteratorAtEnd();
	--it;
	testSubtractionOperator(it, 2, truth[truth.size()-1], truth[truth.size()-3]);

	testDifferenceOperator(createIteratorAtStart(), createIteratorAtEnd(),
			       truth.size());
	testRelationalOperators(createIteratorAtStart(),
				createIteratorAtStart(),
				createIteratorAtEnd());

	it= createIteratorAtStart();
	ASSERT_EQ(it[2], truth[2]);
      }
      
      template <typename ConstIteratorFactory, typename MutableIteratorFactory>
      void testConstAndMutableIteratorCompatibility(ConstIteratorFactory constIteratorFactory,
						    MutableIteratorFactory mutableIteratorFactory) {
	SCOPED_TRACE("testConstAndMutableIteratorCompatibility");
	
	testConstructConstIteratorFromMutable(mutableIteratorFactory(),
					      constIteratorFactory());
	testAssignMutableIteratorToConst(mutableIteratorFactory(),
					 constIteratorFactory());
	testCompareMutableAndConstIterators(constIteratorFactory(),
					    mutableIteratorFactory());
	testRelationalOpsBetweenConstAndMutableIfNeeded(constIteratorFactory(),
							mutableIteratorFactory());
      }

      template <typename SimpleIteratorFactory,
		typename Sequence>
      void testSimpleIterator(SimpleIteratorFactory createSimpleIterator,
			      const Sequence& truth) {
	SCOPED_TRACE("testSimpleIterator");
	testCopyConstruction(createSimpleIterator());
	testCopyAssignment(createSimpleIterator());
	testDereferenceAndRead(createSimpleIterator(), *truth.begin());
	testEqualityOp(createSimpleIterator(), createSimpleIterator(),
		       ++createSimpleIterator());
	testInequalityOp(++createSimpleIterator(), ++createSimpleIterator(),
			 createSimpleIterator());

	testSimpleIteratorPreincrement(createSimpleIterator(), truth);
	testSimpleIteratorPostincrement(createSimpleIterator(), truth);
      }

      template <typename SimpleIteratorFactory,
		typename Sequence>
      void testMutableSimpleIterator(SimpleIteratorFactory createSimpleIterator,
				     const Sequence& truth,
				     const Sequence& valuesToWrite) {
	testSimpleIterator(createSimpleIterator, truth);
	testWriteThroughSimpleIterator(createSimpleIterator(), valuesToWrite);
      }
      
    }
  }
}
#endif
