#include <type_traits>
#include <utility>

#ifndef __LGZSTD_TUPLE_H__
#define __LGZSTD_TUPLE_H__


namespace lgz {

	template<int... Args>
	struct IndexSequence {
		using type = IndexSequence<Args...>;
	};

	template<int N, typename T>
	struct MakeIndexSequence;

	template<int N, int... others>
	struct MakeIndexSequence<N, IndexSequence<others...>> :MakeIndexSequence<N - 1, IndexSequence<N - 1, others...>> {
	};

	template<int... indexes>
	struct MakeIndexSequence<0, IndexSequence<indexes...>> {
		using type = IndexSequence<indexes...>;
	};

	template<int pos, typename Head, typename... Tails>
	struct TuplePosType :TuplePosType<pos - 1, Tails...> {
		static_assert(pos <= sizeof...(Tails), "index overflow!");
	};

	template<typename Head, typename... Args>
	struct TuplePosType<0, Head, Args...> {
		using type = Head;
	};


	template<int idx, typename T>
	class MyTupleElement {
	public:
		T value;
	public:
		MyTupleElement(const T& v) :value(v) {
		}
		MyTupleElement(T&& v) :value(std::move(v)) {
		}
	};

	template<typename T1, typename... Args> class MyTupleImpl;

	template<int... Indexes, typename... Args>
	class MyTupleImpl<IndexSequence<Indexes...>, Args...> :public MyTupleElement<Indexes, Args>...{
	public:
		MyTupleImpl(Args&&... args) :MyTupleElement<Indexes, Args>(std::forward<Args>(args))...{
		}

		template<int pos, typename T>
		const T& getValue() const {
			return ((MyTupleElement<pos, T>*)this)->value;
		}

	};


	template<typename... Args>
	class MyTuple : public MyTupleImpl<typename MakeIndexSequence<sizeof...(Args), IndexSequence<>>::type, Args...> {
		
		static_assert(sizeof...(Args)>1, "MyTuple does not support single data");

		using BaseTupleType = MyTupleImpl<typename MakeIndexSequence<sizeof...(Args), IndexSequence<>>::type, Args...>;
	public:
		MyTuple(Args&&... args) :BaseTupleType(std::forward<Args>(args)...) {
		}

		template<int pos>
		const typename TuplePosType<pos, Args...>::type& get() const {
			return this->template getValue<pos, typename TuplePosType<pos, Args...>::type>();
		}
	};


	template<int pos, typename... Args>
	const typename TuplePosType<pos, Args...>::type& get(const MyTuple<Args...>& t) {
		return ((const MyTupleElement<pos, typename TuplePosType<pos, Args...>::type>&)t).value;
	}

}

#endif
